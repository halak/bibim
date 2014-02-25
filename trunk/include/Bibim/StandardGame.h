#pragma once
#ifndef __BIBIM_STANDARDGAME_H__
#define __BIBIM_STANDARDGAME_H__

#include <Bibim/FWD.h>
#include <Bibim/GameFramework.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Log.h>
#include <Bibim/Lua.h>
#include <Bibim/String.h>
#include <Bibim/UIHandledDrawingContext.h>
#include <Bibim/Window.h>

namespace Bibim
{
    class StandardGame : public GameFramework,
                         public Window::ResizeEventListener,
                         public GraphicsDevice::RestoreEventListener
    {
        BBThisIsNoncopyableClass(StandardGame);
        public:
            class LuaBase : public Bibim::Lua
            {
                BBThisIsNoncopyableClass(LuaBase);
                BBModuleClass(LuaBase, Bibim::Lua, 'S', 'L', 'U', 'L');
                public:
                    LuaBase(StandardGame* game);
                    virtual ~LuaBase();

                    void Load(const String& path);
                    void LoadFromFileSystem(const String& path);

                    inline StandardGame* GetGame() const;

                private:
                    StandardGame* game;
                    struct Internal;
            };

        public:
            virtual ~StandardGame();

            void Restart();
            void CollectGarbage();

            void AddArchive(const String& name);
            void AddArchive(const String& name, int priority);

            inline bool GetFullscreen() const;
            void SetFullscreen(bool value);

            inline Point2 GetContentSize() const;

            inline Color GetClearColor() const;
            inline void SetClearColor(Color value);

            inline Preferences* GetPreferences() const;
            inline Keyboard* GetKeyboard() const;
            inline Mouse* GetMouse() const;
            inline IME* GetIME() const;
            inline GameAssetStorage* GetAssetStorage() const;
            inline AlarmClock* GetAlarmClock() const;
            inline FontLibrary* GetFontLibrary() const;
            AudioDevice* GetAudioDevice() const;
            inline BGM* GetBGM() const;
            inline SoundFX* GetSFX() const;
            inline HttpClient* GetHttpClient() const;
            inline UIDomain* GetUIDomain() const;
            inline UIAsyncEventQueue* GetAsyncEventQueue() const;
            inline UIAppEventDispatcher* GetAppEventDispatcher() const;
            inline LuaBase* GetLua() const;
            inline Clipboard* GetClipboard() const;

        protected:
            StandardGame();
            StandardGame(Point2 windowSize);
            StandardGame(Point2 windowSize, Point2 contentSize);

            void Start(const String& gameName,
                       const String& version,
                       StandardGame::LuaBase* lua,
                       bool windowMoveToScreenCenter = true);

            virtual BGM* CreateBGM(AudioDevice* audioDevice);

            virtual void Finalize();
            virtual void Update(float dt, int timestamp);
            virtual void Draw();
            virtual void EndDraw();
            void DrawDebugText(UIDrawingContext& context, RectF bounds, const String& text);

        protected:
            inline Dashboard* GetDashboard() const;

            void MatchContentToWindow();
            void ReloadUI();

            virtual void ReloadScripts() = 0;
            virtual bool OnKeyDown(const UIEventArgs& args);

        private:
            virtual void OnWindowResized(Window* window);
            virtual void OnGraphicsDeviceRestore(GraphicsDeviceBase* g);
            
            static bool KeyDownHandler(const UIEventArgs& args, void* userData);

        private:
            Point2 windowSize;
            Point2 contentSize;
            bool fullscreen;
            char __padding__[3];
            Color clearColor;
            Dashboard* dashboard;
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
            UIAppEventDispatcher* appEventDispatcher;
            UIMouseEventDispatcher* mouseEventDispatcher;
            ScreenshotPrinter* screenshotPrinter;
            BGM* bgm;
            SoundFX* sfx;
            LuaBase* lua;
            Clipboard* clipboard;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool StandardGame::GetFullscreen() const
    {
        return fullscreen;
    }

    Point2 StandardGame::GetContentSize() const
    {
        return contentSize;
    }

    Color StandardGame::GetClearColor() const
    {
        return clearColor;
    }

    void StandardGame::SetClearColor(Color value)
    {
        clearColor = value;
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

    UIAppEventDispatcher* StandardGame::GetAppEventDispatcher() const
    {
        return appEventDispatcher;
    }

    StandardGame::LuaBase* StandardGame::GetLua() const
    {
        return lua;
    }

    Clipboard* StandardGame::GetClipboard() const
    {
        return clipboard;
    }

    Dashboard* StandardGame::GetDashboard() const
    {
        return dashboard;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    StandardGame* StandardGame::LuaBase::GetGame() const
    {
        return game;
    }
}

#endif