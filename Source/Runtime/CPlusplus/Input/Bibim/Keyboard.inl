namespace Bibim
{
    bool Keyboard::GetAllowKey(Key::Code code) const
    {
        const uint index = static_cast<uint>(static_cast<uint>(code) / (sizeof(dword) * 8));
        const uint bit   = static_cast<uint>(static_cast<uint>(code) % (sizeof(dword) * 8));
        return allowedKeys[index] & (0x80000000 >> bit) ? true : false;;
    }

    void Keyboard::SetAllowKey(Key::Code code, bool allow)
    {
        const uint index = static_cast<uint>(static_cast<uint>(code) / (sizeof(dword) * 8));
        const uint bit   = static_cast<uint>(static_cast<uint>(code) % (sizeof(dword) * 8));
        if (allow)
            allowedKeys[index] |= (0x80000000 >> bit);
        else
            allowedKeys[index] &= ~(0x80000000 >> bit);
    }
}