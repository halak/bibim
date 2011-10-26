#include <Bibim/PCH.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/Assert.h>
#include <Bibim/AssetProvider.h>
#include <Bibim/AutoLocker.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/GameAsset.h>
#include <algorithm>

namespace Bibim
{
    const GameAssetPtr GameAssetStorage::BadAsset = new GameAsset();

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

    bool GameAssetStorage::Preload(const String& name)
    {
        AssetTable::iterator it = assets.find(name);
        if (it == assets.end())
        {
            for (ProviderCollection::const_iterator it = providers.begin(); it != providers.end(); it++)
            {
                if ((*it)->Preload(name))
                {
                    assets.insert(AssetTable::value_type(name, nullptr));
                    return true;
                }
            }

            return false;
        }
        else
            return true;
    }

    GameAsset* GameAssetStorage::Load(const String& name)
    {
        AssetTable::iterator it = assets.find(name);
        if (it != assets.end())
        {
            GameAsset* result = (*it).second;
            if (result == nullptr)
                return nullptr;
            else if (result == BadAsset)
            {
                assets.erase(it);
                return nullptr;
            }
            else
                return (*it).second;
        }
        else
        {
            if (GameAsset* asset = LoadNew(name))
            {
                assets.insert(AssetTable::value_type(name, asset));
                return asset;
            }
            else
                return nullptr;
        }
    }

    const String& GameAssetStorage::FindName(GameAsset* value) const
    {
        for (AssetTable::const_iterator it = assets.begin(); it != assets.end(); it++)
        {
            if ((*it).second == value)
                return (*it).first;
        }

        return String::Empty;
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

    GameAsset* GameAssetStorage::LoadNew(const String& name)
    {
        for (ProviderCollection::const_iterator it = providers.begin(); it != providers.end(); it++)
        {
            if (GameAsset* asset = (*it)->Load(name))
                return asset;
        }

        return nullptr;
    }

    void GameAssetStorage::AddFirst(AssetLoadingTask* item)
    {
        loadingThread.AddFirst(item);
    }

    void GameAssetStorage::AddLast(AssetLoadingTask* item)
    {
        loadingThread.AddLast(item);
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

    void GameAssetStorage::SetAsset(const String& name, GameAsset* asset)
    {
        AssetTable::iterator it = assets.find(name);
        BBAssert(it != assets.end()); // Preload�� ȣ���� �� �̹� �Ҵ��� ���ҽ��ϴ�.

        if (asset == nullptr)
            asset = BadAsset;

        (*it).second = asset; // interlocked exchange
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameAssetStorage::LoadingStatus::LoadingStatus()
        : TotalBytes(0),
          LoadedBytes(0),
          CurrentTaskTotalBytes(0),
          CurrentTaskLoadedBytes(0)
    {
    }

    GameAssetStorage::LoadingStatus::LoadingStatus(uint totalBytes, uint loadedBytes,
                                                   uint taskTotalBytes, uint taskLoadedBytes, const String& taskName)
        : TotalBytes(totalBytes),
          LoadedBytes(loadedBytes),
          CurrentTaskTotalBytes(taskTotalBytes),
          CurrentTaskLoadedBytes(taskLoadedBytes),
          CurrentTaskName(taskName)
    {
    }

    GameAssetStorage::LoadingStatus::LoadingStatus(const LoadingStatus& original)
        : TotalBytes(original.TotalBytes),
          LoadedBytes(original.LoadedBytes),
          CurrentTaskTotalBytes(original.CurrentTaskTotalBytes),
          CurrentTaskLoadedBytes(original.CurrentTaskLoadedBytes),
          CurrentTaskName(original.CurrentTaskName)
    {
    }

    GameAssetStorage::LoadingStatus& GameAssetStorage::LoadingStatus::operator = (const LoadingStatus& right)
    {
        TotalBytes = right.TotalBytes;
        LoadedBytes = right.LoadedBytes;
        CurrentTaskTotalBytes = right.CurrentTaskTotalBytes;
        CurrentTaskLoadedBytes = right.CurrentTaskLoadedBytes;
        CurrentTaskName = right.CurrentTaskName;
        return *this;
    }

    bool GameAssetStorage::LoadingStatus::operator == (const LoadingStatus& right) const
    {
        return (TotalBytes == right.TotalBytes &&
                LoadedBytes == right.LoadedBytes &&
                CurrentTaskTotalBytes == right.CurrentTaskTotalBytes &&
                CurrentTaskLoadedBytes == right.CurrentTaskLoadedBytes &&
                CurrentTaskName == right.CurrentTaskName);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameAssetStorage::LoadingThread::LoadingThread()
        : Thread(false),
          currentTask(nullptr),
          totalBytes(0),
          loadedBytes(0),
          closed(false)
    {
        Resume();
    }

    GameAssetStorage::LoadingThread::~LoadingThread()
    {
        TaskQueue temporaryQueue;
        {
            BBAutoLock(taskQueueLock);
            taskQueue.swap(temporaryQueue);
        }

        for (TaskQueue::const_iterator it = temporaryQueue.begin(); it != temporaryQueue.end(); it++)
            delete (*it);
    }

    void GameAssetStorage::LoadingThread::AddFirst(AssetLoadingTask* item)
    {
        totalBytes += item->GetTotalBytes();
        AutoLocker locker(taskQueueLock);
        taskQueue.push_front(item);
    }

    void GameAssetStorage::LoadingThread::AddLast(AssetLoadingTask* item)
    {
        totalBytes += item->GetTotalBytes();
        AutoLocker locker(taskQueueLock);
        taskQueue.push_back(item);
    }

    void GameAssetStorage::LoadingThread::RequestClose()
    {
        closed = true;
        Suspend();

        if (currentTask)
            currentTask->Cancel();

        Resume();
    }

    void GameAssetStorage::LoadingThread::ResetBackgroundLoadingStatus()
    {
        totalBytes = 0;
        loadedBytes = 0;

        if (taskQueue.empty() == false)
        {
            BBAutoLock(taskQueueLock);
            BBAutoLock(currentTaskLock);

            for (TaskQueue::const_iterator it = taskQueue.begin(); it != taskQueue.end(); it++)
                totalBytes += (*it)->GetTotalBytes();
        }
    }

    GameAssetStorage::LoadingStatus GameAssetStorage::LoadingThread::GetBackgroundLoadingStatus()
    {
        LoadingStatus result;
        
        if (currentTask)
        {
            BBAutoLock(currentTaskLock);
            result.CurrentTaskTotalBytes = currentTask->GetTotalBytes();
            result.CurrentTaskLoadedBytes = currentTask->GetLoadedBytes();
            result.CurrentTaskName = currentTask->GetName();
        }

        result.TotalBytes = totalBytes;
        result.LoadedBytes = loadedBytes + result.CurrentTaskLoadedBytes;

        return result;
    }

    void GameAssetStorage::LoadingThread::OnWork()
    {
        while (closed == false)
        {
            if (taskQueue.empty() == false)
            {
                AssetLoadingTask* task = nullptr;
                {
                    BBAutoLock(taskQueueLock);
                    task = taskQueue.front();
                    taskQueue.pop_front();
                }

                currentTask = task;
                task->Execute();

                {
                    BBAutoLock(currentTaskLock);
                    currentTask = nullptr;
                }

                loadedBytes += task->GetTotalBytes();

                delete task;
            }

            Thread::Sleep();
        }
    }
}