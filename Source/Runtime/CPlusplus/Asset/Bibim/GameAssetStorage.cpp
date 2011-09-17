#include <Bibim/PCH.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/Assert.h>
#include <Bibim/AssetProvider.h>
#include <Bibim/AutoLocker.h>
#include <Bibim/GameAssetLoadingTask.h>
#include <algorithm>

namespace Bibim
{
    GameAssetStorage::GameAssetStorage()
        : modules(nullptr)
    {
    }

    GameAssetStorage::GameAssetStorage(GameModuleTree* modules)
        : modules(modules)
    {
    }

    GameAssetStorage::~GameAssetStorage()
    {
        loadingThread.RequestClose();
        loadingThread.Join();
    }

    GameAsset* GameAssetStorage::Load(const String& name)
    {
        AssetTable::iterator it = assets.find(name);
        if (it != assets.end())
            return (*it).second;
        else
        {
            for (ProviderCollection::const_iterator it = providers.begin(); it != providers.end(); it++)
            {
                if (GameAsset* asset = (*it)->Load(name))
                {
                    assets.insert(AssetTable::value_type(name, asset));
                    return asset;
                }
            }

            return nullptr;
        }
    }

    void GameAssetStorage::OnStatusChanged(Status /*old*/)
    {
        switch (GetStatus())
        {
            case DeadStatus:
                loadingThread.Suspend();
                break;
            case AliveStatus:
            case ActiveStatus:
                loadingThread.Resume();
                break;
        }
    }

    void GameAssetStorage::Add(GameAssetLoadingTask* item)
    {
        loadingThread.AddTask(item);
    }

    void GameAssetStorage::Add(AssetProvider* item)
    {
        BBAssertDebug(std::find(providers.begin(), providers.end(), item) == providers.end());

        providers.push_back(item);
    }

    void GameAssetStorage::Remove(AssetProvider* item)
    {
        ProviderCollection::iterator it = std::find(providers.begin(), providers.end(), item);
        BBAssertDebug(it != providers.end());

        providers.erase(it);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameAssetStorage::LoadingThread::LoadingThread()
        : closed(false)
    {
    }

    GameAssetStorage::LoadingThread::~LoadingThread()
    {
    }

    void GameAssetStorage::LoadingThread::AddTask(GameAssetLoadingTask* item)
    {
        AutoLocker locker(taskQueueLock);
        taskQueue.push(item);
    }

    void GameAssetStorage::LoadingThread::OnWork()
    {
        while (closed == false)
        {
            if (taskQueue.empty() == false)
            {
                GameAssetLoadingTask* task = nullptr;
                {
                    AutoLocker locker(taskQueueLock);
                    task = taskQueue.front();
                    taskQueue.pop();
                }

                task->Execute();

                delete task;
            }

            Thread::Sleep();
        }
    }
}