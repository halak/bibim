#include <Bibim/Config.h>
#include <Bibim/Log.h>
#include <algorithm>
#include <vector>

namespace Bibim
{
    // Add/Remove - Error/Warning/Information 간에
    // Multithreading 문제가 발생할 수 있지만
    // 충돌할 일은 거의 없을거라 판단하여 따로 Lock처리는 안했습니다.
    // 나중에 동기화 작업을 하게되면 Read/Write Lock을 구분하여 처리해야합니다.

    static std::vector<Log::Listener*> listeners;

    void Log::Error(const char* category, const char* message)
    {
        if (message == nullptr)
            message = "";

        for (std::vector<Listener*>::const_iterator it = listeners.begin(); it != listeners.end(); it++)
            (*it)->Error(category, message);
    }

    void Log::Warning(const char* category, const char* message)
    {
        if (message == nullptr)
            message = "";

        for (std::vector<Listener*>::const_iterator it = listeners.begin(); it != listeners.end(); it++)
            (*it)->Warning(category, message);
    }

    void Log::Information(const char* category, const char* message)
    {
        if (message == nullptr)
            message = "";

        for (std::vector<Listener*>::const_iterator it = listeners.begin(); it != listeners.end(); it++)
            (*it)->Information(category, message);
    }

    void Log::Add(Listener* item)
    {
        listeners.push_back(item);
    }

    void Log::Remove(Listener* item)
    {
        std::vector<Listener*>::iterator it = std::find(listeners.begin(), listeners.end(), item);
        if (it != listeners.end())
            listeners.erase(it);
    }
}