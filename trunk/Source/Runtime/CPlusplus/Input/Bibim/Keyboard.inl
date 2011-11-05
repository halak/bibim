namespace Bibim
{
    bool Keyboard::GetAllowKey(Key::Code code) const
    {
        const int index = static_cast<int>(static_cast<int>(code) / (sizeof(int) * 8));
        const int bit   = static_cast<int>(static_cast<int>(code) % (sizeof(int) * 8));
        return allowedKeys[index] & (0x80000000 >> bit) ? true : false;;
    }

    void Keyboard::SetAllowKey(Key::Code code, bool allow)
    {
        const int index = static_cast<int>(static_cast<int>(code) / (sizeof(int) * 8));
        const int bit   = static_cast<int>(static_cast<int>(code) % (sizeof(int) * 8));
        if (allow)
            allowedKeys[index] |= (0x80000000 >> bit);
        else
            allowedKeys[index] &= ~(0x80000000 >> bit);
    }

    Window* Keyboard::GetWindow() const
    {
        return window;
    }

    void Keyboard::SetWindow(Window* value)
    {
        window = value;
    }
}