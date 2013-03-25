namespace Bibim
{
    const String& HttpClientBase::GetUserAgent() const
    {
        return userAgent;
    }

    void HttpClientBase::SetUserAgent(const String& value)
    {
        userAgent = value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const char* HttpClientBase::Request::GetMethod() const
    {
        return method;
    }

    const String& HttpClientBase::Request::GetURL() const
    {
        return url;
    }

    const std::vector<HttpClientBase::KeyValue>& HttpClientBase::Request::GetParams() const
    {
        return params;
    }

    const String& HttpClientBase::Request::GetUserAgent() const
    {
        return userAgent;
    }

    Stream* HttpClientBase::Request::GetOutputStream() const
    {
        return outputStream;
    }
}