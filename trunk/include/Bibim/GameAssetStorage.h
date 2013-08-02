#pragma once
#ifndef __BIBIM_GAMEASSETSTORAGE_H__
#define __BIBIM_GAMEASSETSTORAGE_H__

#include <Bibim/FWD.h>
#include <Bibim/GameModule.h>
#include <Bibim/Lock.h>
#include <Bibim/String.h>
#include <Bibim/Thread.h>
#include <map>
#include <deque>
#include <vector>

namespace Bibim
{
    class GameAssetStorage : public GameModule
    {
        BBModuleClass(GameAssetStorage, GameModule, 'G', 'A', 'S', 'T');
        public:
            typedef std::map<String, GameAssetPtr> AssetTable;
            typedef std::vector<AssetProvider*> ProviderCollection;

            struct LoadingStatus
            {
                int TotalBytes;
                int LoadedBytes;
                int CurrentTaskTotalBytes;
                int CurrentTaskLoadedBytes;
                String CurrentTaskName;

                LoadingStatus();
                LoadingStatus(int totalBytes, int loadedBytes,
                              int taskTotalBytes, int taskLoadedBytes, const String& taskName);
                LoadingStatus(const LoadingStatus& original);

                LoadingStatus& operator = (const LoadingStatus& right);
                bool operator == (const LoadingStatus& right) const;
                inline bool operator != (const LoadingStatus& right) const;
            };

        public:
            GameAssetStorage();
            GameAssetStorage(GameModuleTree* modules);
            virtual ~GameAssetStorage();

            Stream* Open(const String& name);
            bool Preload(const String& name);
            GameAsset* Load(const String& name);
            void Store(const String& name, GameAsset* asset);

            void Restore();

            void Reset();

            const String& FindName(GameAsset* value) const;

            inline GameModuleTree* GetModules() const;
            inline void SetModules(GameModuleTree* value);

            inline const AssetTable& GetAssets() const;
            inline const ProviderCollection& GetProviders() const;

            inline void ResetBackgroundLoadingStatus();
            inline LoadingStatus GetBackgroundLoadingStatus();

        protected:
            virtual void OnStatusChanged(Status old);

            class LoadingThread : public Thread
            {
                public:
                    typedef std::deque<AssetLoadingTask*> TaskQueue;

                public:
                    LoadingThread();
                    virtual ~LoadingThread();

                    virtual void Start();

                    void AddFirst(AssetLoadingTask* item);
                    void AddLast(AssetLoadingTask* item);

                    void RequestClose();

                    void ResetBackgroundLoadingStatus();
                    LoadingStatus GetBackgroundLoadingStatus();

                protected:
                    virtual void OnWork();

                private:
                    AssetLoadingTask* currentTask;
                    Lock currentTaskLock;
                    TaskQueue taskQueue;
                    Lock taskQueueLock;
                    int totalBytes;
                    int loadedBytes;
                    bool closed;
            };

        private:
            GameAsset* LoadNew(const String& name);

            void AddFirst(AssetLoadingTask* item); // call in AssetStreamReader, AssetProvider
            void AddLast(AssetLoadingTask* item); // call in AssetStreamReader, AssetProvider
            void Add(AssetProvider* item); // call in AssetProvider
            void Remove(AssetProvider* item); // call in AssetProvider
            void SetAsset(const String& name, GameAsset* asset); // call in AssetPreloadingTask

        private:
            GameModuleTree* modules;
            AssetTable assets;
            ProviderCollection providers;

            LoadingThread loadingThread;

            static const GameAssetPtr BadAsset; // reference in AssetPreloadingTask

            friend class AssetProvider;
            friend class AssetStreamReader;
            friend class AssetPreloadingTask;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameModuleTree* GameAssetStorage::GetModules() const
    {
        return modules;
    }

    void GameAssetStorage::SetModules(GameModuleTree* value)
    {
        modules = value;
    }

    const GameAssetStorage::AssetTable& GameAssetStorage::GetAssets() const
    {
        return assets;
    }

    const GameAssetStorage::ProviderCollection& GameAssetStorage::GetProviders() const
    {
        return providers;
    }

    void GameAssetStorage::ResetBackgroundLoadingStatus()
    {
        return loadingThread.ResetBackgroundLoadingStatus();
    }

    GameAssetStorage::LoadingStatus GameAssetStorage::GetBackgroundLoadingStatus()
    {
        return loadingThread.GetBackgroundLoadingStatus();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool GameAssetStorage::LoadingStatus::operator != (const LoadingStatus& right) const
    {
        return !operator == (right);
    }
}

#endif