namespace Bibim
{
    const String& HttpClient::GetUserAgent() const
    {
        return userAgent;
    }

    void HttpClient::SetUserAgent(const String& value)
    {
        userAgent = value;
    }
}