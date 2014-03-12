#include <Bibim/Config.h>
#include <Bibim/Log.h>
#include <algorithm>
#include <vector>

namespace Bibim
{
    static std::vector<Log::Listener*> LogListeners;

    void Log::Error(const char* category, const char* message)
    {
        for (std::vector<Listener*>::const_iterator it = LogListeners.begin(); it != LogListeners.end(); ++it)
            (*it)->Error(category, message);
    }

    void Log::Warning(const char* category, const char* message)
    {
        for (std::vector<Listener*>::const_iterator it = LogListeners.begin(); it != LogListeners.end(); ++it)
            (*it)->Warning(category, message);
    }

    void Log::Information(const char* category, const char* message)
    {
        for (std::vector<Listener*>::const_iterator it = LogListeners.begin(); it != LogListeners.end(); ++it)
            (*it)->Information(category, message);
    }

    void Log::Add(Listener* item)
    {
        if (item)
        {
            // Concurrency issue
            LogListeners.push_back(item);
        }
    }

    void Log::Remove(Listener* item)
    {
        if (item)
        {
            // Concurrency issue
            std::vector<Listener*>::iterator it = std::find(LogListeners.begin(), LogListeners.end(), item);
            if (it != LogListeners.end())
                LogListeners.erase(it);
        }
    }
}