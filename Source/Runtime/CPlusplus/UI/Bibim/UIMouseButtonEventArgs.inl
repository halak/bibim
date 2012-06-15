namespace Bibim
{
    Key::Code UIMouseButtonEventArgs::GetButtonCode() const
    {
        return buttonCode;
    }

    const char* UIMouseButtonEventArgs::GetButtonCodeAsChars() const
    {
        return Key::ToString(buttonCode);
    }
}