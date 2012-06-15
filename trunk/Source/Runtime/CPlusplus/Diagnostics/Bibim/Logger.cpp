#include <Bibim/PCH.h>
#include <Bibim/Logger.h>

namespace Bibim
{
    Logger::Logger()
    {
        Log::Add(this);
    }

    Logger::~Logger()
    {
        Log::Remove(this);
    }
}