namespace Bibim
{
    KeyboardState::KeyboardState()
    {
        for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
            Keys[i] = 0x00000000;
    }

    KeyboardState::KeyboardState(const KeyboardState& original)
    {
        for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
            Keys[i] = original.Keys[i];
    }

    bool KeyboardState::IsPressed(Key::Code code) const
    {
        const uint index = static_cast<uint>(static_cast<uint>(code) / (sizeof(dword) * 8));
        const uint bit   = static_cast<uint>(static_cast<uint>(code) % (sizeof(dword) * 8));
        return Keys[index] & (0x80000000 >> bit) ? true : false;
    }

    bool KeyboardState::IsReleased(Key::Code code) const
    {
        return !IsPressed(code);
    }

    KeyboardState& KeyboardState::operator = (const KeyboardState& right)
    {
        for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
            Keys[i] = right.Keys[i];

        return *this;
    }

    bool KeyboardState::operator == (const KeyboardState& right) const
    {
        for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
        {
            if (Keys[i] != right.Keys[i])
                return false;
        }

        return true;
    }

    bool KeyboardState::operator != (const KeyboardState& right) const
    {
        return !operator == (right);
    }
}