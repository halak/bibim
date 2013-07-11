namespace Bibim
{
    Color StandardGame::GetClearColor() const
    {
        return clearColor;
    }

    void StandardGame::SetClearColor(Color value)
    {
        clearColor = value;
    }

    bool StandardGame::GetDebugDisplay() const
    {
        return debugDisplay;
    }

    void StandardGame::SetDebugDisplay(bool value)
    {
        debugDisplay = value;
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

    Lua* StandardGame::GetLua() const
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