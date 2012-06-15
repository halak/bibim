namespace Bibim
{
    void Log::Error(const char* message)
    {
        Error(nullptr, message);
    }

    void Log::Warning(const char* message)
    {
        Warning(nullptr, message);
    }

    void Log::Information(const char* message)
    {
        Information(nullptr, message);
    }
}