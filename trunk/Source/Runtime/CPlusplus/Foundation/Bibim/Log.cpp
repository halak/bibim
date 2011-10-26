#include <Bibim/PCH.h>
#include <Bibim/Log.h>
#include <algorithm>
#include <vector>

namespace Bibim
{
    // Add/Remove - Error/Warning/Information ����
    // Multithreading ������ �߻��� �� ������
    // �浹�� ���� ���� �����Ŷ� �Ǵ��Ͽ� ���� Lockó���� ���߽��ϴ�.
    // ���߿� ����ȭ �۾��� �ϰԵǸ� Read/Write Lock�� �����Ͽ� ó���ؾ��մϴ�.

    static std::vector<Log::Listener*> listeners;

    void Log::Error(const char* category, const char* message)
    {
        for (std::vector<Listener*>::const_iterator it = listeners.begin(); it != listeners.end(); it++)
            (*it)->Error(category, message);
    }

    void Log::Warning(const char* category, const char* message)
    {
        for (std::vector<Listener*>::const_iterator it = listeners.begin(); it != listeners.end(); it++)
            (*it)->Warning(category, message);
    }

    void Log::Information(const char* category, const char* message)
    {
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