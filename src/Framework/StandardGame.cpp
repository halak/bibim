#include <Bibim/Config.h>
#include <Bibim/StandardGame.h>
#include <Bibim/StandardGame.EmbeddedFont.h>
#include <Bibim/All.h>
#include <ctime>

namespace Bibim
{
    StandardGame::StandardGame()
        : fullscreen(false),
          clearColor(Color::Black),
          dashboard(nullptr),
          storage(nullptr),
          fontLibrary(nullptr),
          uiDomain(nullptr)
    {
        GetWindow()->AddResizeEventListener(this);
        GetGraphicsDevice()->AddRestoreEventListener(this);
    }

    StandardGame::StandardGame(Point2 windowSize)
        : GameFramework(windowSize.X, windowSize.Y),
          windowSize(windowSize),
          contentSize(0, 0),
          fullscreen(false),
          clearColor(Color::Black),
          dashboard(nullptr),
          storage(nullptr),
          fontLibrary(nullptr),
          uiDomain(nullptr)
    {
        GetWindow()->AddResizeEventListener(this);
        GetGraphicsDevice()->AddRestoreEventListener(this);

        dashboard = new Dashboard();
    }

    StandardGame::StandardGame(Point2 windowSize, Point2 contentSize)
        : GameFramework(windowSize.X, windowSize.Y),
          windowSize(windowSize),
          contentSize(contentSize),
          fullscreen(false),
          clearColor(Color::Black),
          storage(nullptr),
          uiDomain(nullptr)
    {
        GetWindow()->AddResizeEventListener(this);
        GetGraphicsDevice()->AddRestoreEventListener(this);

        dashboard = new Dashboard();
    }

    StandardGame::~StandardGame()
    {
        if (dashboard)
        {
            delete dashboard;
            dashboard = nullptr;
        }

        GetGraphicsDevice()->RemoveRestoreEventListener(this);
        GetWindow()->RemoveResizeEventListener(this);
    }
    
    void StandardGame::Initialize(const String& gameName,
                                  const String& version,
                                  StandardGame::LuaBase* lua,
                                  bool windowMoveToScreenCenter)
    {
        // Log::Add(this);

        if (windowMoveToScreenCenter)
            GetWindow()->MoveToScreenCenter();

        GameFramework::Initialize();

        //MOBILE MPQPtr mainMPQ = new MPQ("Game.mpq");

        preferences = new Preferences(gameName);
        GetModules()->GetRoot()->AttachChild(preferences);

        keyboard = new Keyboard(GetWindow());
        mouse = new Mouse(GetWindow());
        ime = new IME(GetWindow());
        GetModules()->GetRoot()->AttachChild(keyboard);
        GetModules()->GetRoot()->AttachChild(mouse);
        GetModules()->GetRoot()->AttachChild(ime);

        AudioDevice* audioDevice = new AudioDevice();
        //MOBILE audioDevice->AddArchive(mainMPQ);
        bgm = CreateBGM(audioDevice);
        sfx = new SoundFX(audioDevice);
        bgm->SetTimeline(GetMainTimeline());
        sfx->SetTimeline(GetMainTimeline());
        GetModules()->GetRoot()->AttachChild(audioDevice);
        GetModules()->GetRoot()->AttachChild(bgm);
        GetModules()->GetRoot()->AttachChild(sfx);

        fontLibrary = new FontLibrary(GetGraphicsDevice());
        GetModules()->GetRoot()->AttachChild(fontLibrary);

        storage = new GameAssetStorage(GetModules());
        GameModuleNode* storageNode = GetModules()->GetRoot()->AttachChild(storage);
        {
#           if (defined(BIBIM_PLATFORM_WINDOWS))
            storageNode->AttachChild(new NetworkAssetProvider(storage,
                                                              IPEndPoint(IPEndPoint::Localhost, NetworkAssetProvider::DefaultPort),
                                                              gameName));
#           endif

            //MOBILE MPQAssetProvider*   map = new MPQAssetProvider(storage, mainMPQ);
            //MOBILE storageNode->AttachChild(map);
            
            storageNode->AttachChild(new FileAssetProvider(storage));
        }

        fontLibrary->SetAssetStorage(storage);

        SparkParticleEngine* spk = new SparkParticleEngine();
        GetModules()->GetRoot()->AttachChild(spk);

        if (lua)
        {
            this->lua = lua;
            GetModules()->GetRoot()->AttachChild(lua);
        }

        alarmClock = new AlarmClock();
        alarmClock->SetTimeline(GetMainTimeline());
        GetModules()->GetRoot()->AttachChild(alarmClock);

        httpClient = new HttpClient();
        GetModules()->GetRoot()->AttachChild(httpClient);
        httpClient->SetUserAgent("Bibim/1.0;");
        httpClient->SetTimeline(GetMainTimeline());

        UIWindowPtr rootWindow = new UIWindow();
        rootWindow->SetXY(0.0f, 0.0f);
        rootWindow->SetXYMode(UIVisual::AbsolutePosition);
        rootWindow->SetSizeMode(UIVisual::AbsoluteSize);
        rootWindow->SetAnchorPoint(UIVisual::Center);
        rootWindow->SetOrigin(Vector2(0.5f, 0.5f));

        uiDomain = new UISimpleDomain(rootWindow);
        GameModuleNode* uiDomainNode = GetModules()->GetRoot()->AttachChild(uiDomain);
        {
            MatchContentToWindow();

            uiRenderer = new UIRenderer(GetGraphicsDevice(), storage, "Asset/Shader");
            UIKeyboardEventDispatcher* ked = new UIKeyboardEventDispatcher(uiDomain, keyboard);
            UIMouseEventDispatcher*    med = new UIMouseEventDispatcher(uiDomain, mouse, uiRenderer, true);
            asyncEventQueue = new UIAsyncEventQueue();
            uiDomainNode->AttachChild(uiRenderer);
            uiDomainNode->AttachChild(ked);
            uiDomainNode->AttachChild(med);
            uiDomainNode->AttachChild(asyncEventQueue);

            ked->SetTimeline(GetMainTimeline());
            med->SetTimeline(GetMainTimeline());
            asyncEventQueue->SetTimeline(GetMainTimeline());

            mouseEventDispatcher = med;
        }
        uiFunctions = new UIFunctionTable();
        uiFunctions->Add("OnKeyDown", &StandardGame::KeyDownHandler, this);
        uiDomainNode->AttachChild(uiFunctions);

        screenshotPrinter = new ScreenshotPrinter(GetGraphicsDevice());
        GetModules()->GetRoot()->AttachChild(screenshotPrinter);

        {
            UIPanel* uiRoot = uiDomain->GetRoot();
            UIFunctionEventHandler* handler = new UIFunctionEventHandler();
            handler->SetTable(uiFunctions);
            handler->SetFunctionName("OnKeyDown");
            if (uiRoot->GetEventMap() == nullptr)
                uiRoot->SetEventMap(new UIEventMap());
            uiRoot->GetEventMap()->AddHandler(UIEventID::KeyDown, handler);
        }

        clipboard = new Clipboard();
        GetModules()->GetRoot()->AttachChild(clipboard);

        dashboard->Initialize(this->GetModules());

        GameFramework::Initialize();
    }

    BGM* StandardGame::CreateBGM(AudioDevice* audioDevice)
    {
        return new BGM(audioDevice);
    }

    void StandardGame::Finalize()
    {
        dashboard->Finalize();
        bgm->SetMute(true);
        GetMainTimeline()->Clear();
        uiDomain->GetRoot()->RemoveAllChildren();
        GameFramework::Finalize();
    }

    void StandardGame::Update(float dt, int timestamp)
    {
        if (dashboard)
            dashboard->BeginFrame();

        BBPerfFunc();
        GameFramework::Update(dt, timestamp);
    }

    void StandardGame::Draw()
    {
        BBPerfFunc();

        if (clearColor.A > 0)
            GetGraphicsDevice()->Clear(clearColor);

        UIHandledDrawingContext context(uiRenderer, dashboard);
        context.Draw(uiDomain->GetRoot());

        GameFramework::Draw();
    }

    void StandardGame::EndDraw()
    {
        GameFramework::EndDraw();

        if (dashboard)
            dashboard->EndFrame();
    }

    void StandardGame::SetFullscreen(bool value)
    {
        if (GetFullscreen() != value)
        {
            fullscreen = value;

            GameWindow* window = GetWindow();

            if (GetFullscreen())
            {
                windowSize = window->GetSize();
                window->SetFullscreenStyle(true);
                window->SetPosition(Point2::Zero);
                window->SetSize(GetGraphicsDevice()->GetScreenSize());
            }
            else
            {
                window->SetFullscreenStyle(false);
                window->SetSize(windowSize);
                window->MoveToScreenCenter();
            }
        }
    }

    void StandardGame::Restart()
    {
        if (GetAssetStorage())
            GetAssetStorage()->Reset();

        ReloadUI();
    }

    void StandardGame::MatchContentToWindow()
    {
        if (GetUIDomain() == nullptr)
            return;

        UIWindow* rootWindow = GetUIDomain()->GetRoot();

        const Point2 windowSize = GetWindow()->GetSize();

        float scale = 1.0f;
        if (contentSize.X != 0 || contentSize.Y != 0)
        {
            float xScale = Float::Max;
            float yScale = Float::Max;
            if (contentSize.X != 0)
                xScale = static_cast<float>(windowSize.X) / static_cast<float>(contentSize.X);
            if (contentSize.Y != 0)
                yScale = static_cast<float>(windowSize.Y) / static_cast<float>(contentSize.Y);

            scale = Math::Min(xScale, yScale);
        }

        if (Math::Equals(scale, 1.0f) == false)
        {
            UITransform3DPtr transform = new UITransform3D();
            transform->SetScale(scale);
            rootWindow->SetTransform(transform);
        }
        else
        {
            rootWindow->SetTransform(nullptr);
            scale = 1.0f;
        }

        if (contentSize.X == 0)
            rootWindow->SetWidth(static_cast<float>(windowSize.X) / scale);
        else
            rootWindow->SetWidth(static_cast<float>(contentSize.X));

        if (contentSize.Y == 0)
            rootWindow->SetHeight(static_cast<float>(windowSize.Y) / scale);
        else
            rootWindow->SetHeight(static_cast<float>(contentSize.Y));

        if (GetFontLibrary())
            GetFontLibrary()->SetGlobalScale(scale);
    }

    void StandardGame::ReloadUI()
    {
        alarmClock->CancelAll();
        uiDomain->GetRoot()->RemoveAllChildren();
        uiDomain->SetFocus(uiDomain->GetRoot());

        GetModules()->FindModule<UIMouseEventDispatcher>()->Reset();

        if (lua)
            lua->GC();

        ReloadScripts();
    }

    void StandardGame::OnWindowResized(Window* window)
    {
        BBAssert(GetWindow() == window);
        MatchContentToWindow();
    }

    void StandardGame::OnGraphicsDeviceRestore(GraphicsDeviceBase* g)
    {
        BBAssert(GetGraphicsDevice() == g);
        if (GetAssetStorage())
            GetAssetStorage()->Restore();
    }

    bool StandardGame::KeyDownHandler(const UIEventArgs& args, void* userData)
    {
        if (userData)
            return reinterpret_cast<StandardGame*>(userData)->OnKeyDown(args);
        else
            return false;
    }

    bool StandardGame::OnKeyDown(const Bibim::UIEventArgs& args)
    {
        const UIKeyboardEventArgs& keyboard = static_cast<const UIKeyboardEventArgs&>(args);
        if (keyboard.Contains(Key::F2))
        {
            ReloadUI();
            return true;
        }
        else if (keyboard.Contains(Key::F3))
        {
            Log::Error("HELLO HELLO HELLO");
            return true;
        }
        else if (keyboard.Contains(Key::Alt) && keyboard.Contains(Key::Enter))
        {
            GetGraphicsDevice()->SetFullscreen(!GetGraphicsDevice()->GetFullscreen());
            return true;
        }
        else
            return false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    namespace
    {
        static StandardGame* GetGame(lua_State* L)
        {
            StandardGame::LuaBase* lua = nullptr;
            if (lua_getallocf(L, reinterpret_cast<void**>(&lua)))
                return lua->GetGame();
            else
                return nullptr;
        }

        static int GetPreferenceItem(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            Preferences* preferences = game->GetPreferences();
            if (preferences == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TSTRING);

            const String key = lua_tostring(L, 1);

            const Any& value = preferences->GetValue(key);
            switch (value.GetType())
            {
                case Any::VoidType:
                    return 0;
                case Any::BoolType:
                    lua_pushboolean(L, value.CastBool());
                    return 1;
                case Any::IntType:
                    lua_pushinteger(L, value.CastInt());
                    return 1;
                case Any::LongIntType:
                    lua_pushnumber(L, static_cast<lua_Number>(value.CastLongInt()));
                    return 1;
                case Any::FloatType:
                    lua_pushnumber(L, value.CastFloat());
                    return 1;
                case Any::StringType:
                    lua_pushstring(L, value.CastString().CStr());
                    return 1;
                default:
                    return 0;
            }
        }

        static int SetPreferenceItem(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            Preferences* preferences = game->GetPreferences();
            if (preferences == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TSTRING);

            const String key = lua_tostring(L, 1);
            switch (lua_type(L, 2))
            {
                case LUA_TNIL:
                    preferences->SetValue(key, Any::Void);
                    break;
                case LUA_TBOOLEAN:
                    preferences->SetValue(key, lua_toboolean(L, 2) != 0);
                    break;
                case LUA_TNUMBER:
                    preferences->SetValue(key, static_cast<int>(lua_tointeger(L, 2)));
                    break;
                case LUA_TSTRING:
                    preferences->SetValue(key, String(lua_tostring(L, 2)));
                    break;
            }

            return 0;
        }

        static int CommitPreferences(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            Preferences* preferences = game->GetPreferences();
            if (preferences == nullptr)
                return 0;

            preferences->Commit();

            return 0;
        }

        static int SetTitle(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TSTRING);

            const String title = lua_tostring(L, 1);
            game->GetWindow()->SetTitle(title);

            return 0;
        }

        static int RestartGame(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            game->Restart();

            return 0;
        }

        static int ExitGame(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            game->Exit();

            return 0;
        }

        class ScriptCallback : public AlarmClock::Callback
        {
            public:
                ScriptCallback(Lua* lua, int index)
                    : lua(lua),
                      tickIndex(-1),
                      alarmIndex(index),
                      cancelIndex(-1)
                {
                }

                ScriptCallback(Lua* lua, int tickIndex, int alarmIndex, int cancelIndex)
                    : lua(lua),
                      tickIndex(tickIndex),
                      alarmIndex(alarmIndex),
                      cancelIndex(cancelIndex)
                {
                }

                virtual ~ScriptCallback()
                {
                    lua->UnregisterCallback(tickIndex);
                    lua->UnregisterCallback(alarmIndex);
                    lua->UnregisterCallback(cancelIndex);
                }

            protected:
                virtual Result OnTick(AlarmClock* /*clock*/, float elapsedAlarmTime, float alarmTime)
                {
                    Invoke(tickIndex, elapsedAlarmTime / alarmTime, false);
                    return Continue;
                }

                virtual Result OnAlarm(AlarmClock* /*clock*/)
                {
                    Invoke(alarmIndex, -1.0f, true);
                    return Stop;
                }

                virtual void OnCancelled(AlarmClock* /*clock*/)
                {
                    Invoke(cancelIndex, -1.0f, true);
                }

                void Invoke(int index, float t, bool reset)
                {
                    if (index == -1)
                        return;

                    lua_State* L = lua->GetState();

                    lua_pushcclosure(L, &lua_tinker::on_error, 0);
                    int errfunc = lua_gettop(L);

                    // local f = _CALLBACKS[index]
                    lua_getglobal(L, "_CALLBACKS");
                    lua_rawgeti(L, -1, index);

                    // f();
                    BBAssert(lua_isfunction(L, -1));
                    int nargs = 0;
                    if (t >= 0.0f)
                    {
                        nargs = 1;
                        lua_pushnumber(L, t);
                    }
                    if (lua_pcall(L, nargs, 0, errfunc) != 0)
                        lua_pop(L, 1);

                    if (reset)
                    {
                        // _CALLBACKS[index] = nil
                        lua_pushnil(L);
                        lua_rawseti(L, -2, index);
                    }

                    // pop _CALLBACKS
                    // pop on_error
                    lua_pop(L, 2);
                }

            private:
                Lua* lua;
                int tickIndex;
                int alarmIndex;
                int cancelIndex;
        };

        static int LoadAsset(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            GameAssetStorage* assetStorage = game->GetAssetStorage();
            if (assetStorage == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TSTRING);

            const String path = lua_tostring(L, 1);
            GameAsset* asset = assetStorage->Load(path);
            if (asset)
            {
                lua_tinker::push(L, asset);
                return 1;
            }

            return 0;
        }

        static int PreloadAsset(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            GameAssetStorage* assetStorage = game->GetAssetStorage();
            if (assetStorage == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TSTRING);

            const String path = lua_tostring(L, 1);
            if (assetStorage->Preload(path))
                lua_tinker::push(L, true);
            else
                lua_tinker::push(L, false);

            return 1;
        }

        static int Store(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            GameAssetStorage* assetStorage = game->GetAssetStorage();
            if (assetStorage == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TSTRING);
            luaL_checktype(L, 2, LUA_TUSERDATA);

            const String path = lua_tostring(L, 1);
            if (GameAsset* asset = lua_tinker::read<GameAsset*>(L, 2))
                assetStorage->Store(path, asset);

            return 0;
        }

        static int Time(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            lua_pushnumber(L, Clock::GetCurrentMilliSeconds());
            return 1;
        }

        static int SystemTime(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            lua_pushnumber(L, time(NULL));
            return 1;
        }

        static int AddTimeout(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            AlarmClock* alarmClock = game->GetAlarmClock();
            if (alarmClock == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TNUMBER);

            int group = AlarmClock::DefaultGroup;
            int callbackIndex = -1;

            if (lua_isfunction(L, 2))
                callbackIndex = game->GetLua()->RegisterCallback(2);
            else if (lua_isfunction(L, 3))
            {
                if (lua_isnumber(L, 2))
                    group = static_cast<int>(lua_tointeger(L, 2));
                callbackIndex = game->GetLua()->RegisterCallback(3);
            }
            else
                return 0;

            float duration = static_cast<float>(Math::Max(lua_tonumber(L, 1), 0.0));

            // return newIndex
            lua_pushinteger(L, callbackIndex);

            alarmClock->Start(new ScriptCallback(game->GetLua(), callbackIndex), group, AlarmClock::InvalidTime, duration);

            return 1;
        }

        static int AddAlarm(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            AlarmClock* alarmClock = game->GetAlarmClock();
            if (alarmClock == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TNUMBER);
            luaL_checktype(L, 2, LUA_TNUMBER);

            float tickTime = static_cast<float>(Math::Max(lua_tonumber(L, 1), 0.0));
            float alarmTime = static_cast<float>(Math::Max(lua_tonumber(L, 2), 0.0));
            int group = AlarmClock::DefaultGroup;
            if (lua_isnumber(L, 3))
                group = static_cast<int>(lua_tointeger(L, 3));
            int tickCallbackIndex = game->GetLua()->RegisterCallback(4);
            int alarmCallbackIndex = game->GetLua()->RegisterCallback(5);
            int cancelCallbackIndex = game->GetLua()->RegisterCallback(6);

            alarmClock->Start(new ScriptCallback(game->GetLua(),
                                                 tickCallbackIndex,
                                                 alarmCallbackIndex,
                                                 cancelCallbackIndex), group, tickTime, alarmTime);

            return 0;
        }

        static int CancelAlarm(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            AlarmClock* alarmClock = game->GetAlarmClock();
            if (alarmClock == nullptr)
            {
                Log::Error("Lua haven't AlarmClock. AlarmClock required.");
                return 0;
            }

            int group = AlarmClock::DefaultGroup;
            if (lua_isnumber(L, 1))
                group = static_cast<int>(lua_tointeger(L, 1));

            alarmClock->Cancel(group);

            return 0;
        }

        static int GetLuaObject(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            lua_tinker::push(L, game->GetLua());

            return 1;
        }

        static int GetTimeline(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            AlarmClock* alarmClock = game->GetAlarmClock();
            if (alarmClock && alarmClock->GetTimeline())
                lua_tinker::push(L, alarmClock->GetTimeline());
            else
                lua_pushnil(L);

            return 1;
        }

        static int GetIMEObject(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            IME* ime = game->GetIME();
            if (ime)
                lua_tinker::push(L, ime);
            else
                lua_pushnil(L);

            return 1;
        }

        static int ResetLoadingStatus(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            if (GameAssetStorage* assetStorage = game->GetAssetStorage())
                assetStorage->ResetBackgroundLoadingStatus();

            return 0;
        }

        static int LoadingStatus(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;
            
            GameAssetStorage* assetStorage = game->GetAssetStorage();
            if (assetStorage == nullptr)
                return 0;

           const GameAssetStorage::LoadingStatus status = assetStorage->GetBackgroundLoadingStatus();
            lua_tinker::push(L, status.TotalBytes);
            lua_tinker::push(L, status.LoadedBytes);
            lua_tinker::push(L, status.CurrentTaskTotalBytes);
            lua_tinker::push(L, status.CurrentTaskLoadedBytes);
            return 4;
        }

        static int CommandLine(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            lua_pushstring(L, game->GetStartupArgs().CStr());
            return 1;
        }

        class UIEventArgsSerializer : public UIEventArgs::Serializer
        {
            public:
                UIEventArgsSerializer(lua_State* l)
                    : L(l),
                      Count(0)
                {
                }

                virtual ~UIEventArgsSerializer() { }

                virtual void Push(GameComponent* value)
                {
                    lua_tinker::push(L, value);
                    Count++;
                }

                virtual void Push(bool value)
                {
                    lua_tinker::push(L, value);
                    Count++;
                }

                virtual void Push(int value)
                {
                    lua_tinker::push(L, value);
                    Count++;
                }

                virtual void Push(float value)
                {
                    lua_tinker::push(L, value);
                    Count++;
                }

                virtual void Push(const char* value)
                {
                    lua_tinker::push(L, value);
                    Count++;
                }

            public:
                lua_State* L;
                int Count;
        };

        class UIScriptEventHandler : public UIEventHandler
        {
            BBComponentClass(UIScriptEventHandler, UIEventHandler, 'U', 'S', 'C', 'H');
            public:
                UIScriptEventHandler()
                    : lua(nullptr),
                      callbackIndex(0)
                {
                }

                UIScriptEventHandler(Lua* lua, int callbackIndex)
                    : lua(lua),
                      callbackIndex(callbackIndex)
                {
                }

                virtual ~UIScriptEventHandler()
                {
                    lua->UnregisterCallback(callbackIndex);
                }

                virtual bool Invoke(const UIEventArgs& args)
                {
                    lua_State* L = lua->GetState();

                    lua_pushcclosure(L, &lua_tinker::on_error, 0);
                    int errfunc = lua_gettop(L);

                    // local f = _CALLBACKS[index]
                    lua_getglobal(L, "_CALLBACKS");
                    lua_rawgeti(L, -1, callbackIndex);

                    // f();
                    BBAssert(lua_isfunction(L, -1));
                    UIEventArgsSerializer serializer(L);
                    args.Serialize(serializer);
                    if(lua_pcall(L, serializer.Count, 1, errfunc) != 0)
                        lua_pop(L, 1);

                    const bool result = lua_tinker::pop<bool>(L);

                    // pop _CALLBACKS
                    // pop on_error
                    lua_pop(L, 2);

                    return result;
                }

            private:
                Lua* lua;
                int callbackIndex;
        };

        BBImplementsComponent(UIScriptEventHandler);

        void UIScriptEventHandler::OnCopy(const GameComponent* original, CloningContext& context)
        {
            Base::OnCopy(original, context);
            const UIScriptEventHandler* o = static_cast<const UIScriptEventHandler*>(original);
            lua = o->lua;
            callbackIndex = o->callbackIndex;
        }

        void UIScriptEventHandler::OnRead(ComponentStreamReader& reader)
        {
            Base::OnRead(reader);
        }

        static int Select(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            UIDomain* uiDomain = game->GetUIDomain();
            if (uiDomain == nullptr)
                return 0;
     
            const int count = lua_gettop(L);
            UIVisual* current = uiDomain->GetRoot();
            for (int i = 2; i <= count; i++)
            {
                UIVisual* found = nullptr;
                switch (lua_type(L, i))
                {
                    case LUA_TSTRING:
                        {
                            if (current == nullptr)
                                return 0;

                            size_t length = 0;
                            const char* name = lua_tolstring(L, i, &length);
                            if (name == nullptr)
                                continue;

                            found = static_cast<UIPanel*>(current)->FindChildByChars(name, length, true);
                        }
                        break;
                    case LUA_TUSERDATA:
                        found = lua_tinker::read<UIVisual*>(L, i);
                        break;
                    case LUA_TNUMBER:
                        {
                            if (current == nullptr)
                                return 0;

                            const UIPanel* currentPanel = static_cast<UIPanel*>(current);
                            const int numberOfChildren = currentPanel->GetNumberOfChildren();
                            BBAssertDebug(numberOfChildren > 0);
                            int index = lua_tointeger(L, i);
                            if (index >= 0)
                                index %= numberOfChildren;
                            else
                                index = numberOfChildren + (index % numberOfChildren);
                            found = static_cast<UIPanel*>(current)->GetChildAt(index);
                        }
                        break;
                }

                if (found == nullptr)
                    return 0;

                if (found->IsPanel() && static_cast<UIPanel*>(found)->GetNumberOfChildren() > 0)
                    current = found;
                else
                {
                    if (i == count)
                    {
                        lua_tinker::push(L, found);
                        return 1;
                    }
                    else
                        return 0;
                }
            }

            lua_tinker::push(L, current);
            return 1;
        }

        static int Each(lua_State* L, UIPanel* current, int callbackIndex)
        {
            typedef UIPanel::VisualCollection VisualCollection;
            const VisualCollection& children = current->GetChildren();
            for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                BBAssert(lua_isfunction(L, -1));
                
                lua_pushvalue(L, callbackIndex);
                lua_tinker::push(L, static_cast<UIVisual*>(*it));
                lua_call(L, 1, 1);
                const bool childrenSkipped = (lua_toboolean(L, -1) != 0);
                
                lua_pop(L, 1);

                if (childrenSkipped == false && (*it)->IsPanel())
                    Each(L, StaticCast<UIPanel>(*it), callbackIndex);
            }

            return 0;
        }

        static int Each(lua_State* L, UIPanel* current, int callbackIndex, const int* findingClassID4)
        {
            typedef UIPanel::VisualCollection VisualCollection;
            const VisualCollection& children = current->GetChildren();
            for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                const int classID = (*it)->GetClassID();
                bool childrenSkipped = false;
                if (findingClassID4[0] == classID ||
                    findingClassID4[1] == classID ||
                    findingClassID4[2] == classID ||
                    findingClassID4[3] == classID)
                {
                    BBAssert(lua_isfunction(L, -1));

                    lua_pushvalue(L, callbackIndex);
                    lua_tinker::push(L, static_cast<UIVisual*>(*it));
                    lua_call(L, 1, 1);
                    childrenSkipped = (lua_toboolean(L, -1) != 0);
                    lua_pop(L, 1);
                }

                if (childrenSkipped == false && (*it)->IsPanel())
                    Each(L, StaticCast<UIPanel>(*it), callbackIndex, findingClassID4);
            }

            return 0;
        }

        static int All(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            UIDomain* uiDomain = game->GetUIDomain();
            if (uiDomain == nullptr)
                return 0;

            UIPanel* root = nullptr;
            const char* findingClassName = nullptr;
            int callbackIndex = -1;
            if (lua_type(L, 1) == LUA_TFUNCTION)
                callbackIndex = 1;
            else if (lua_type(L, 2) == LUA_TFUNCTION)
            {
                callbackIndex = 2;
                switch (lua_type(L, 1))
                {
                    case LUA_TSTRING:
                        findingClassName = lua_tostring(L, 1);
                        break;
                    case LUA_TUSERDATA:
                        root = lua_tinker::read<UIPanel*>(L, 1);
                        if (root->IsPanel() == false)
                            return 0;
                        break;
                    default:
                        break;
                }
            }
            else if (lua_type(L, 3) == LUA_TFUNCTION)
            {
                callbackIndex = 3;
                if (lua_isuserdata(L, 1))
                {
                    root = lua_tinker::read<UIPanel*>(L, 1);
                    if (root->IsPanel() == false)
                        return 0;
                }

                if (lua_isstring(L, 2))
                    findingClassName = lua_tostring(L, 2);
            }

            int findingClassIDs[4] = { 0, 0, 0, 0 };
            if (findingClassName)
            {
                static const String UIImageClassName = "UIImage";
                static const String UILabelClassName = "UILabel";
                static const String UIButtonClassName = "UIButton";
                static const String UIEditTextClassName = "UIEditText";
                static const String UIDocumentClassName = "UIDocument";

                if (UIImageClassName.EqualsIgnoreCase(findingClassName))
                    findingClassIDs[0] = UIImage::ClassID;
                else if (UILabelClassName.EqualsIgnoreCase(findingClassName))
                {
                    findingClassIDs[0] = UILabel::ClassID;
                    findingClassIDs[1] = UIEditText::ClassID;
                }
                else if (UIButtonClassName.EqualsIgnoreCase(findingClassName))
                {
                    findingClassIDs[0] = UIButton::ClassID;
                    findingClassIDs[1] = UICheckBox::ClassID;
                    findingClassIDs[2] = UIRadioButton::ClassID;
                }
                else if (UIEditTextClassName.EqualsIgnoreCase(findingClassName))
                {
                    findingClassIDs[0] = UIEditText::ClassID;
                }
                else if (UIDocumentClassName.EqualsIgnoreCase(findingClassName))
                {
                    findingClassIDs[0] = UIDocument::ClassID;
                }
            }

            if (root == nullptr)
                root = uiDomain->GetRoot();

            BBStaticAssert(sizeof(findingClassIDs) / sizeof(findingClassIDs[0]) == 4);

            if (findingClassName)
                Each(L, root, callbackIndex, findingClassIDs);
            else
                Each(L, root, callbackIndex);

            return 0;
        }

        static int Children(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            UIDomain* uiDomain = game->GetUIDomain();
            if (uiDomain == nullptr)
                return 0;

            luaL_checktype(L, 1, LUA_TUSERDATA);
            luaL_checktype(L, 2, LUA_TFUNCTION);

            UIVisual* visual = lua_tinker::read<UIVisual*>(L, 1);
            if (visual == nullptr ||
                visual->IsPanel() == false)
                return 0;

            UIPanel* target = static_cast<UIPanel*>(visual);

            typedef UIPanel::VisualCollection VisualCollection;
            const VisualCollection& children = target->GetChildren();
            for (VisualCollection::const_iterator it = children.begin(); it != children.end(); it++)
            {
                lua_pushvalue(L, 2);
                lua_tinker::push(L, static_cast<UIVisual*>(*it));
                lua_call(L, 1, 0);
            }

            return 0;
        }

        static int SelfDetach(lua_State* L)
        {
            if (UIVisual* target = lua_tinker::read<UIVisual*>(L, 1))
            {
                const bool removed = UIWindow::RemoveFromParent(target);
                lua_pushboolean(L, removed);
                return 1;
            }
            else
                return 0;
        }

        static int On(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            luaL_checktype(L, 2, LUA_TSTRING);
            luaL_checktype(L, 3, LUA_TFUNCTION);

            UIVisual* visual = lua_tinker::read<UIVisual*>(L, 1);
            if (visual == nullptr)
                return 0;

            UIEventID e = UIEventID(lua_tostring(L, 2));
            int callbackIndex = game->GetLua()->RegisterCallback(3);
            bool isDelayed = lua_toboolean(L, 4) != 0;

            if (visual->GetEventMap() == nullptr)
            {
                visual->SetEventMap(new UIEventMap());
                visual->GetEventMap()->SetAsyncEventQueue(game->GetAsyncEventQueue());
            }

            UIEventHandler* handler = new UIScriptEventHandler(game->GetLua(), callbackIndex);
            if (isDelayed)
                visual->GetEventMap()->AddDelayedHandler(e, handler);
            else
                visual->GetEventMap()->AddHandler(e, handler);

            return 0;
        }

        static int Off(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            luaL_checktype(L, 2, LUA_TSTRING);

            UIVisual* visual = lua_tinker::read<UIVisual*>(L, 1);
            if (visual == nullptr)
                return 0;

            UIEventID e = UIEventID(lua_tostring(L, 2));
            if (UIEventMap* eventMap = visual->GetEventMap())
            {
                eventMap->RemoveAllHandlers(e);
                eventMap->RemoveAllDelayedHandlers(e);
            }

            return 0;
        }

        static int GetRoot(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            if (UIDomain* uiDomain = game->GetUIDomain())
                lua_tinker::push(L, uiDomain->GetRoot());
            else
                lua_pushnil(L);

            return 1;
        }

        static int Bounds(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            if (UIVisual* v = lua_tinker::read<UIVisual*>(L, 1))
            {
                UIBoundsContext context;
                const RectF bounds = context.Compute(v);
                lua_tinker::push(L, bounds.X);
                lua_tinker::push(L, bounds.Y);
                lua_tinker::push(L, bounds.Width);
                lua_tinker::push(L, bounds.Height);
                return 4;
            }

            return 0;
        }

        static int Focus(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;
            
            UIDomain* uiDomain = game->GetUIDomain();
            if (uiDomain == nullptr)
                return 0;

            lua_State* state = L;

            if (lua_isuserdata(state, 1))
            {
                if (UIVisual* v = lua_tinker::read<UIVisual*>(state, 1))
                {
                    uiDomain->SetFocus(v);
                    return 0;
                }
            }

            lua_tinker::push(state, uiDomain->GetFocus());
            return 1;
        }

        static int NewFont(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            if (FontLibrary* fontLibrary = game->GetFontLibrary())
                lua_tinker::push(L, new Font(fontLibrary));
            else
                lua_pushnil(L);

            return 1;
        }

        static int Capture(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr || game->GetGraphicsDevice() == nullptr)
                return 0;

            UIRenderer* uiRenderer = game->GetModules()->FindModule<UIRenderer>();
            if (uiRenderer == nullptr)
                return 0;

            UIVisual* v = lua_tinker::read<UIVisual*>(L, 1);
            if (v == nullptr)
                return 0;
            
            UIBoundsContext context;
            const RectF bounds = context.Compute(v);

            GraphicsDevice* g = game->GetGraphicsDevice();
            const int w = static_cast<int>(bounds.Width);
            const int h = static_cast<int>(bounds.Height);
            RenderTargetTexture2DPtr renderTarget = new RenderTargetTexture2D(g, w, h);
            g->BeginDraw(renderTarget);
            UIDrawingContext drawingContext(uiRenderer);
            drawingContext.Draw(v);
            g->EndDraw(renderTarget);

            lua_tinker::push(L, new Image(renderTarget));

            return 1;
        }

        static int ChangeBGM(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            if (BGM* bgm = game->GetBGM())
            {
                const char* name = lua_tinker::read<const char*>(L, 1);

                if (lua_isnumber(L, 2))
                    bgm->Change(name, static_cast<float>(lua_tonumber(L, 2)));
                else
                    bgm->Change(name);
            }

            return 0;
        }

        static int DurationBGM(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr || game->GetGraphicsDevice() == nullptr)
                return 0;

            BGM* bgm = game->GetBGM();
            if (bgm == nullptr)
                return 0;

            AudioDevice* device = bgm->GetAudioDevice();
            if (device == nullptr)
                return 0;

            const char* uri = lua_tinker::read<const char*>(L, 1);
            const int duration = static_cast<int>(device->GetDurationByChars(uri));
     
            lua_pushinteger(L, duration);

            return 1;
        }

        static int CrossfadeTimeBGM(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr || game->GetGraphicsDevice() == nullptr)
                return 0;

            BGM* bgm = game->GetBGM();
            if (bgm == nullptr)
                return 0;

            if (lua_isnumber(L, 1))
            {
                bgm->SetCrossfadeTime(static_cast<float>(lua_tonumber(L, 1)));
                return 0;
            }
            else
            {
                lua_pushnumber(L, bgm->GetCrossfadeTime());
                return 1;
            }
        }

        static int Play(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr || game->GetGraphicsDevice() == nullptr)
                return 0;

            if (SoundFX* sfx = game->GetSFX())
            {
                const char* name = lua_tinker::read<const char*>(L, 1);
                const int group = lua_tinker::read<int>(L, 2);
                sfx->Play(name, group);
            }

            return 0;
        }

        static int Stop(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr || game->GetGraphicsDevice() == nullptr)
                return 0;

            if (SoundFX* sfx = game->GetSFX())
            {
                if (lua_isnil(L, 1))
                    sfx->Stop();
                else
                    sfx->Stop(lua_tinker::read<int>(L, 1));
            }

            return 0;
        }

        static int Pause(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr || game->GetGraphicsDevice() == nullptr)
                return 0;

            if (SoundFX* sfx = game->GetSFX())
            {
                if (lua_isnil(L, 1))
                    sfx->Pause();
                else
                    sfx->Pause(lua_tinker::read<int>(L, 1));
            }

            return 0;
        }

        static int Resume(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr || game->GetGraphicsDevice() == nullptr)
                return 0;

            if (SoundFX* sfx = game->GetSFX())
            {
                if (lua_isnil(L, 1))
                    sfx->Resume();
                else
                    sfx->Resume(lua_tinker::read<int>(L, 1));
            }

            return 0;
        }

        class ScriptHttpCallback : public HttpClient::Callback
        {
            public:
                ScriptHttpCallback()
                    : lua(nullptr),
                      callbackIndex(-1)
                {
                }

                ScriptHttpCallback(Lua* lua, int callbackIndex)
                    : lua(lua),
                      callbackIndex(callbackIndex)
                {
                }

                virtual ~ScriptHttpCallback()
                {
                    lua->UnregisterCallback(callbackIndex);
                }

            protected:
                virtual void OnProgress(const String& /*url*/, int /*current*/, int /*total*/) { }
                virtual void OnResponse(const String& /*url*/, HttpClient::StatusCode statusCode, Stream* outputStream, const String& contentType)
                {
                    if (callbackIndex == -1)
                        return;

                    MemoryStream* stream = static_cast<MemoryStream*>(outputStream);

                    lua_State* L = lua->GetState();

                    lua_pushcclosure(L, &lua_tinker::on_error, 0);
                    int errfunc = lua_gettop(L);

                    // local f = _CALLBACKS[index]
                    lua_getglobal(L, "_CALLBACKS");
                    lua_rawgeti(L, -1, callbackIndex);

                    // f();
                    const char* contentBuffer = reinterpret_cast<const char*>(stream->GetBuffer());
                    BBAssert(lua_isfunction(L, -1));
                    lua_pushnumber(L, statusCode);
                    lua_pushlstring(L, contentBuffer, stream->GetLength());
                    lua_pushlstring(L, contentType.CStr(), contentType.GetLength());
                    if (lua_pcall(L, 3, 0, errfunc) != 0)
                        lua_pop(L, 1);

                    // pop _CALLBACKS
                    // pop on_error
                    lua_pop(L, 2);
                }

            private:
                Lua* lua;
                int callbackIndex;
        };

        class ScriptDownloadCallback : public HttpClient::Callback
        {
            public:
                ScriptDownloadCallback(Lua* lua, int progressCallbackIndex, int completeCallbackIndex)
                    : lua(lua),
                      progressCallbackIndex(progressCallbackIndex),
                      completeCallbackIndex(completeCallbackIndex)
                {
                }

                virtual ~ScriptDownloadCallback()
                {
                    lua->UnregisterCallback(progressCallbackIndex);
                    lua->UnregisterCallback(completeCallbackIndex);
                }

            protected:
                virtual void OnProgress(const String& url, int current, int total)
                {
                    if (progressCallbackIndex == -1)
                        return;

                    lua_State* L = lua->GetState();

                    lua_pushcclosure(L, &lua_tinker::on_error, 0);
                    int errfunc = lua_gettop(L);

                    // local f = _CALLBACKS[index]
                    lua_getglobal(L, "_CALLBACKS");
                    lua_rawgeti(L, -1, progressCallbackIndex);

                    // f();
                    BBAssert(lua_isfunction(L, -1));
                    lua_pushlstring(L, url.CStr(), url.GetLength());
                    lua_pushinteger(L, current);
                    lua_pushinteger(L, total);
                    if (lua_pcall(L, 3, 0, errfunc) != 0)
                        lua_pop(L, 1);

                    // pop _CALLBACKS
                    // pop on_error
                    lua_pop(L, 2);
                }

                virtual void OnResponse(const String& url, HttpClient::StatusCode statusCode, Stream* /*outputStream*/, const String& /*contentType*/)
                {
                    if (completeCallbackIndex == -1)
                        return;

                    lua_State* L = lua->GetState();

                    lua_pushcclosure(L, &lua_tinker::on_error, 0);
                    int errfunc = lua_gettop(L);

                    // local f = _CALLBACKS[index]
                    lua_getglobal(L, "_CALLBACKS");
                    lua_rawgeti(L, -1, completeCallbackIndex);

                    // f();
                    BBAssert(lua_isfunction(L, -1));
                    lua_pushlstring(L, url.CStr(), url.GetLength());
                    lua_pushboolean(L, statusCode == HttpClient::Ok);
                    if (lua_pcall(L, 2, 0, errfunc) != 0)
                        lua_pop(L, 1);

                    // pop _CALLBACKS
                    // pop on_error
                    lua_pop(L, 2);
                }

            private:
                Lua* lua;
                int progressCallbackIndex;
                int completeCallbackIndex;
        };

        static int REQUEST(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            HttpClient* http = game->GetHttpClient();
            if (http == nullptr)
                return 0;

            luaL_checkstring(L, 1);
            luaL_checkstring(L, 2);

            const char* method = lua_tostring(L, 1);
            const char* url = lua_tostring(L, 2);
            MemoryStreamPtr outputStream = MemoryStream::NewWritableStream(128, true);

            if (lua_isfunction(L, 3))
            {
                SharedPointer<ScriptHttpCallback> callback = new ScriptHttpCallback(game->GetLua(),
                                                                                    game->GetLua()->RegisterCallback(3));

                if (String::EqualsCharsIgnoreCase(method, "POST"))
                    http->POST(url, outputStream, callback);
                else if (String::EqualsCharsIgnoreCase(method, "GET"))
                    http->GET(url, outputStream, callback);
            }
            else if (lua_isfunction(L, 4))
            {
                std::vector<HttpClient::KeyValue> params;
                if (lua_istable(L, 3))
                {
                    lua_pushnil(L);
                    while (lua_next(L, 3) != 0)
                    {
                        const int keyType = lua_type(L, -2);
                        const int valueType = lua_type(L, -1);
                        if ((keyType == LUA_TNUMBER || keyType == LUA_TSTRING) &&
                            (valueType == LUA_TBOOLEAN || valueType == LUA_TNUMBER || valueType == LUA_TSTRING))
                        {
                            const char* key = lua_tostring(L, -2);
                            const char* value = nullptr;
                            if (valueType == LUA_TBOOLEAN)
                            {
                                if (lua_toboolean(L, -1))
                                    value = "true";
                                else
                                    value = "false";
                            }
                            else
                                value = lua_tostring(L, -1);

                            params.push_back(HttpClient::KeyValue(key, value));
                        }

                        lua_pop(L, 1);
                    }
                }

                BBAssertDebug(lua_isfunction(L, 4));
                SharedPointer<ScriptHttpCallback> callback = new ScriptHttpCallback(game->GetLua(),
                                                                                    game->GetLua()->RegisterCallback(4));

                if (String::EqualsCharsIgnoreCase(method, "POST"))
                    http->POST(url, params, outputStream, callback);
                else if (String::EqualsCharsIgnoreCase(method, "GET"))
                    http->GET(url, params, outputStream, callback);
            }

            return 0;
        }

        static int Download(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            HttpClient* http = game->GetHttpClient();
            if (http == nullptr)
                return 0;

            luaL_checkstring(L, 1);
            luaL_checkstring(L, 2);

            const char* url = lua_tostring(L, 1);
            const char* localPath = lua_tostring(L, 2);
            int progressCallback = -1;
            int downloadCllaback = -1;
            
            if (lua_isfunction(L, 3))
            {
                if (lua_isfunction(L, 4))
                {
                    progressCallback = game->GetLua()->RegisterCallback(3);
                    downloadCllaback = game->GetLua()->RegisterCallback(4);
                }
                else
                {
                    progressCallback = -1;
                    downloadCllaback = game->GetLua()->RegisterCallback(3);
                }
            }

            SharedPointer< ScriptDownloadCallback> callback = new ScriptDownloadCallback(game->GetLua(),
                                                                                        progressCallback,
                                                                                        downloadCllaback);

            FileStreamPtr outputStream = new FileStream(localPath, FileStream::WriteOnly);
            if (outputStream->CanWrite())
                http->GET(url, outputStream, callback);
            else
            {
                // callback->OnResponse(url, HttpClient::ClientError, nullptr, String::Empty);
            }
            
            return 0;
        }

        static int UserAgent(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            HttpClient* http = game->GetHttpClient();
            if (http == nullptr)
                return 0;

            if (lua_isstring(L, 1))
            {
                http->SetUserAgent(lua_tostring(L, 1));
                return 0;
            }
            else
            {
                const String& ua = http->GetUserAgent();
                lua_pushlstring(L, ua.CStr(), ua.GetLength());
                return 1;
            }
        }

        static int SetClipboardText(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TSTRING);

            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            Clipboard* clipboard = game->GetClipboard();
            if (clipboard == nullptr)
                return 0;

            clipboard->SetText(lua_tostring(L, 1));

            return 0;
        }

        static int GetClipboardText(lua_State* L)
        {
            StandardGame* game = GetGame(L);
            if (game == nullptr)
                return 0;

            Clipboard* clipboard = game->GetClipboard();
            if (clipboard == nullptr)
                return 0;

            const String text = clipboard->GetText();
            
            lua_pushlstring(L, text.CStr(), text.GetLength());

            return 1;
        }
    }

    StandardGame::LuaBase::LuaBase(StandardGame* game)
        : game(game)
    {
        const struct luaL_Reg thLib [] = {
            { "title", &SetTitle },
            { "restart", &RestartGame },
            { "exit", &ExitGame },
            { "load", &LoadAsset },
            { "preload", &PreloadAsset },
            { "store", &Store },
            { "time", &Time },
            { "systime", &SystemTime },
            { "timeout",  &AddTimeout },
            { "alarm", &AddAlarm },
            { "canceltimeout", &CancelAlarm },
            { "cancelalarm", &CancelAlarm },
            { "lua", &GetLuaObject },
            { "timeline", &GetTimeline },
            { "ime", &GetIMEObject },
            { "resetloadingstatus", &ResetLoadingStatus },
            { "loadingstatus", &LoadingStatus },
            { "commandline", &CommandLine },
            { NULL, NULL}  /* sentinel */
        };

        const struct luaL_Reg preferencesLib [] = {
            { "get", &GetPreferenceItem },
            { "set", &SetPreferenceItem },
            { "commit", &CommitPreferences },
            { NULL, NULL}  /* sentinel */
        };

        const struct luaL_Reg uiLib [] = {
            { "all", &All },
            { "children", &Children },
            { "selfdetach", &SelfDetach },
            { "getroot", &GetRoot },
            { "root", &GetRoot },
            { "bounds", &Bounds },
            { "focus", &Focus },
            { "createfont", &NewFont },
            { "on", &On },
            { "off", &Off },
            { "capture", &Capture },
            { NULL, NULL}  /* sentinel */
        };

        const struct luaL_Reg bgmLib [] = {
            { "change", &ChangeBGM },
            { "duration", &DurationBGM },
            { "crossfade", &CrossfadeTimeBGM },
            { NULL, NULL}  /* sentinel */
        };

        const struct luaL_Reg sfxLib [] = {
            { "play", &Play },
            { "stop", &Stop },
            { "pause", &Pause },
            { "resume", &Resume },
            { NULL, NULL}  /* sentinel */
        };

        const struct luaL_Reg httpLib [] = {
            { "request", &REQUEST },
            { "download", &Download },
            { "useragent", &UserAgent },
            { NULL, NULL}  /* sentinel */
        };

        const struct luaL_Reg clipboardLib [] = {
            { "set", &SetClipboardText },
            { "get", &GetClipboardText },
            { NULL, NULL}  /* sentinel */
        };

        lua_State* state = GetState();

        lua_newtable(state);
        lua_setglobal(state, "th");
        lua_getglobal(state, "th");
        luaL_setfuncs(state, thLib, 0);
        lua_pop(state, 1);

        lua_newtable(state);
        lua_setglobal(state, "preferences");
        lua_getglobal(state, "preferences");
        luaL_setfuncs(state, preferencesLib, 0);
        lua_pop(state, 1);

        lua_newtable(state);
        lua_setglobal(state, "ui");
        lua_getglobal(state, "ui");
        luaL_setfuncs(state, uiLib, 0);
        lua_pop(state, 1);

        lua_newtable(state);
        lua_setglobal(state, "bgm");
        lua_getglobal(state, "bgm");
        luaL_setfuncs(state, bgmLib, 0);
        lua_pop(state, 1);

        lua_newtable(state);
        lua_setglobal(state, "sfx");
        lua_getglobal(state, "sfx");
        luaL_setfuncs(state, sfxLib, 0);
        lua_pop(state, 1);

        lua_newtable(state);
        lua_setglobal(state, "http");
        lua_getglobal(state, "http");
        luaL_setfuncs(state, httpLib, 0);
        lua_pop(state, 1);

        lua_newtable(state);
        lua_setglobal(state, "clipboard");
        lua_getglobal(state, "clipboard");
        luaL_setfuncs(state, clipboardLib, 0);
        lua_pop(state, 1);

        lua_getglobal(state, "ui");
        if(lua_istable(state, -1))
        {
            lua_newtable(state);
            lua_pushstring(state, "__call");
            lua_pushcclosure(state, &Select, 0);
            lua_rawset(state, -3);
            lua_setmetatable(state, -2);
        }
        lua_pop(state, 1);
    }

    StandardGame::LuaBase::~LuaBase()
    {
    }

    void StandardGame::LuaBase::Load(const String& path)
    {
        GameAssetStorage* storage = GetGame()->GetAssetStorage();
        if (storage == nullptr)
            return;

        StreamPtr stream = storage->Open(path);
        if (stream)
        {
            BinaryReader reader(stream);
            const int size = reader.ReadInt();
            if (size > 0)
            {
                byte* data = BBStackAlloc(byte, size);
                reader.Read(data, size);

                Lua::DoBuffer(data, size, path);

                BBStackFree(data);
            }
            else
                Log::Error("Lua", String::CFormat("Couldn't open lua file. (%s)", path.CStr()));
        }
        else
            Log::Error("Lua", String::CFormat("Couldn't open lua file. (%s)", path.CStr()));
    }
}   