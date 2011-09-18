#include <Bibim/AssetLoadingTask.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    AssetLoadingTask::AssetLoadingTask(const String& name, uint totalBytes)
        : name(name),
          totalBytes(totalBytes),
          loadedBytes(0)
    {
    }

    AssetLoadingTask::~AssetLoadingTask()
    {
        BBAssertDebug(totalBytes >= loadedBytes);
    }
}