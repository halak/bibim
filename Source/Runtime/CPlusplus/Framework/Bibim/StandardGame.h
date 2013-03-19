#pragma once
#ifndef __BIBIM_STANDARDGAME_H__
#define __BIBIM_STANDARDGAME_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameFramework.h>
#   include <Bibim/Log.h>
#   include <Bibim/Lua.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class StandardGame : public GameFramework, public Log::Listener
        {
            BBThisIsNoncopyableClass(StandardGame);
            public:
                virtual ~StandardGame();

                inline Color GetClearColor() const;
                inline void SetClearColor(Color value);

                inline Preferences* GetPreferences() const;
                inline Keyboard* GetKeyboard() const;
                inline Mouse* GetMouse() const;
                inline GameAssetStorage* GetAssetStorage() const;
                inline AlarmClock* GetAlarmClock() const;
                inline FontLibrary* GetFontLibrary() const;
                inline BGM* GetBGM() const;
                inline SoundFX* GetSFX() const;
                inline HttpClient* GetHttpClient() const;
                inline UIDomain* GetUIDomain() const;
                inline UIAsyncEventQueue* GetAsyncEventQueue() const;
                inline Lua* GetLua() const;

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
                StandardGame(int resolutionWidth, int resolutionHeight);

                void Initialize(const String& gameName, const String& version, StandardGame::LuaBase* lua);

                virtual void Finalize();
                virtual void Draw();

            protected:
                void ReloadUI();

                virtual void ReloadScripts() = 0;
            private:
                static bool KeyDownHandler(const UIEventArgs& args, void* userData);

                bool OnKeyDown(const UIEventArgs& args);

                virtual void Error(const char* category, const char* message);
                virtual void Warning(const char* category, const char* message);
                virtual void Information(const char* category, const char* message);
                void OnLog(Color color, const char* category, const char* message);

            private:
                Color clearColor;
                Preferences* preferences;
                Keyboard* keyboard;
                Mouse* mouse;
                GameAssetStorage* storage;
                AlarmClock* alarmClock;
                FontLibrary* fontLibrary;
                HttpClient* httpClient;
                UIDomain* uiDomain;
                UIRenderer* uiRenderer;
                UIFunctionTable* uiFunctions;
                UIAsyncEventQueue* asyncEventQueue;
                ScreenshotPrinter* screenshotPrinter;
                BGM* bgm;
                SoundFX* sfx;
                Lua* lua;
                String  recentLog;
                FontPtr recentLogFont;
        };
    }

#   include <Bibim/StandardGame.inl>

#endif