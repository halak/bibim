#pragma once
#ifndef __BIBIM_STANDARDGAME_H__
#define __BIBIM_STANDARDGAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameFramework.h>
#   include <Bibim/GraphicsDevice.h>
#   include <Bibim/Log.h>
#   include <Bibim/Lua.h>
#   include <Bibim/String.h>
#   include <Bibim/Window.h>

    namespace Bibim
    {
        class StandardGame : public GameFramework,
                             public Window::ResizeEventListener,
                             public GraphicsDevice::RestoreEventListener,
                             public Log::Listener
        {
            BBThisIsNoncopyableClass(StandardGame);
            public:
                virtual ~StandardGame();

                void Restart();

                inline Color GetClearColor() const;
                inline void SetClearColor(Color value);

                inline bool GetDebugDisplay() const;
                inline void SetDebugDisplay(bool value);

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
                inline Lua* GetLua() const;
                inline Clipboard* GetClipboard() const;

            public:
                class LuaBase : public Bibim::Lua
                {
                    BBThisIsNoncopyableClass(LuaBase);
                    BBModuleClass(LuaBase, Bibim::Lua, 'S', 'L', 'U', 'L');
                    public:
                        LuaBase(StandardGame* game);
                        virtual ~LuaBase();

                        inline StandardGame* GetGame() const;

                    private:
                        StandardGame* game;
                        struct Internal;
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
                Point2 contentSize;
                Color clearColor;
                bool debugDisplay;
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
                Lua* lua;
                Clipboard* clipboard;
                String  recentLog;
                FontPtr debugFont;
        };
    }

#   include <Bibim/StandardGame.inl>

#endif