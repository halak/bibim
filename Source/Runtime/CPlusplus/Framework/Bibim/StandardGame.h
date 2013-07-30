#pragma once
#ifndef __BIBIM_STANDARDGAME_H__
#define __BIBIM_STANDARDGAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameFramework.h>
#   include <Bibim/GraphicsDevice.h>
#   include <Bibim/Log.h>
#   include <Bibim/Lua.h>
#   include <Bibim/String.h>
#   include <Bibim/UIHandledDrawingContext.h>
#   include <Bibim/Window.h>
#   include <sstream>

    namespace Bibim
    {
        class StandardGame : public GameFramework,
                             public Window::ResizeEventListener,
                             public GraphicsDevice::RestoreEventListener,
                             public Log::Listener
        {
            BBThisIsNoncopyableClass(StandardGame);
            public:
                enum DebugMode
                {
                    NoDebugMode,
                    SimpleDebugDisplay,
                    RemoteDebugging,
                };

                class LuaBase : public Bibim::Lua
                {
                    BBThisIsNoncopyableClass(LuaBase);
                    BBModuleClass(LuaBase, Bibim::Lua, 'S', 'L', 'U', 'L');
                    public:
                        LuaBase(StandardGame* game);
                        virtual ~LuaBase();

                        void Load(const String& path);

                        inline StandardGame* GetGame() const;

                    private:
                        StandardGame* game;
                        struct Internal;
                };

            public:
                virtual ~StandardGame();

                void Restart();

                inline bool GetFullscreen() const;
                void SetFullscreen(bool value);

                inline Color GetClearColor() const;
                inline void SetClearColor(Color value);

                inline DebugMode GetDebugMode() const;
                void SetDebugMode(DebugMode value);

                inline Preferences* GetPreferences() const;
                inline Keyboard* GetKeyboard() const;
                inline Mouse* GetMouse() const;
                inline IME* GetIME() const;
                inline GameAssetStorage* GetAssetStorage() const;
                inline AlarmClock* GetAlarmClock() const;
                inline FontLibrary* GetFontLibrary() const;
                inline BGM* GetBGM() const;
                inline SoundFX* GetSFX() const;
                inline HttpClient* GetHttpClient() const;
                inline UIDomain* GetUIDomain() const;
                inline UIAsyncEventQueue* GetAsyncEventQueue() const;
                inline LuaBase* GetLua() const;
                inline Clipboard* GetClipboard() const;

            protected:
                class RemoteDebugger : public UIHandledDrawingContext::Handler
                {
                    public:
                        RemoteDebugger();
                        virtual ~RemoteDebugger();

                    protected:
                        virtual void OnBegan(UIHandledDrawingContext& context, UIVisual* target);
                        virtual void OnEnded(UIHandledDrawingContext& context, UIVisual* target);
                        virtual void OnVisualBegan(UIHandledDrawingContext& context);
                        virtual void OnVisualEnded(UIHandledDrawingContext& context);

                    private:
                        bool TryConnectToServer();

                        void Synchronize(const UIVisual* visual);

                    private:
                        int syncCountdown;
                        SocketPtr socket;
                        StreamPtr queryStream;
                        std::ostringstream stringstream;
                        void* selectedVisual;
                        RectF selectedVisualBounds;
                        RectF selectedVisualClippedBounds;
                };

            protected:
                StandardGame();
                StandardGame(Point2 windowSize);
                StandardGame(Point2 windowSize, Point2 contentSize);

                void Initialize(const String& gameName,
                                const String& version,
                                StandardGame::LuaBase* lua,
                                bool windowMoveToScreenCenter = true);

                virtual BGM* CreateBGM(AudioDevice* audioDevice);

                virtual void Finalize();
                virtual void Draw();
                void DrawDebugText(UIDrawingContext& context, RectF bounds, const String& text);

            protected:
                void MatchContentToWindow();
                void ReloadUI();
                void SetRecentLog(const String& value);

                virtual void ReloadScripts() = 0;
                virtual bool OnKeyDown(const UIEventArgs& args);

            private:
                virtual void OnWindowResized(Window* window);
                virtual void OnGraphicsDeviceRestore(GraphicsDeviceBase* g);
                
                static bool KeyDownHandler(const UIEventArgs& args, void* userData);

                virtual void Error(const char* category, const char* message);
                virtual void Warning(const char* category, const char* message);
                virtual void Information(const char* category, const char* message);
                void OnLog(Color color, const char* category, const char* message);

            private:
                Point2 windowSize;
                Point2 contentSize;
                bool fullscreen;
                char __padding__[3];
                Color clearColor;
                DebugMode debugMode;
                RemoteDebugger* remoteDebugger;
                Preferences* preferences;
                Keyboard* keyboard;
                Mouse* mouse;
                IME* ime;
                GameAssetStorage* storage;
                AlarmClock* alarmClock;
                FontLibrary* fontLibrary;
                HttpClient* httpClient;
                UIDomain* uiDomain;
                UIRenderer* uiRenderer;
                UIFunctionTable* uiFunctions;
                UIAsyncEventQueue* asyncEventQueue;
                UIMouseEventDispatcher* mouseEventDispatcher;
                ScreenshotPrinter* screenshotPrinter;
                BGM* bgm;
                SoundFX* sfx;
                LuaBase* lua;
                Clipboard* clipboard;
                String  recentLog;
                FontPtr debugFont;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool StandardGame::GetFullscreen() const
        {
            return fullscreen;
        }

        Color StandardGame::GetClearColor() const
        {
            return clearColor;
        }

        void StandardGame::SetClearColor(Color value)
        {
            clearColor = value;
        }

        StandardGame::DebugMode StandardGame::GetDebugMode() const
        {
            return debugMode;
        }

        Preferences* StandardGame::GetPreferences() const
        {
            return preferences;
        }

        Keyboard* StandardGame::GetKeyboard() const
        {
            return keyboard;
        }

        Mouse* StandardGame::GetMouse() const
        {
            return mouse;
        }

        IME* StandardGame::GetIME() const
        {
            return ime;
        }

        GameAssetStorage* StandardGame::GetAssetStorage() const
        {
            return storage;
        }

        AlarmClock* StandardGame::GetAlarmClock() const
        {
            return alarmClock;
        }

        FontLibrary* StandardGame::GetFontLibrary() const
        {
            return fontLibrary;
        }

        BGM* StandardGame::GetBGM() const
        {
            return bgm;
        }

        SoundFX* StandardGame::GetSFX() const
        {
            return sfx;
        }

        HttpClient* StandardGame::GetHttpClient() const
        {
            return httpClient;
        }

        UIDomain* StandardGame::GetUIDomain() const
        {
            return uiDomain;
        }

        UIAsyncEventQueue* StandardGame::GetAsyncEventQueue() const
        {
            return asyncEventQueue;
        }

        StandardGame::LuaBase* StandardGame::GetLua() const
        {
            return lua;
        }

        Clipboard* StandardGame::GetClipboard() const
        {
            return clipboard;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        StandardGame* StandardGame::LuaBase::GetGame() const
        {
            return game;
        }
    }

#endif