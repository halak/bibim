#pragma once
#ifndef __BIBIM_GAMEASSETSTORAGE_H__
#define __BIBIM_GAMEASSETSTORAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Lock.h>
#   include <Bibim/String.h>
#   include <Bibim/Thread.h>
#   include <map>
#   include <deque>
#   include <vector>

    namespace Bibim
    {
        class GameAssetStorage : public GameModule
        {
            BBGameModuleClass('G', 'A', 'S', 'T');
            public:
                typedef std::map<String, GameAsset*> AssetTable;
                typedef std::vector<AssetProvider*> ProviderCollection;

                struct LoadingStatus
                {
                    uint TotalBytes;
                    uint LoadedBytes;
                    uint CurrentTaskTotalBytes;
                    uint CurrentTaskLoadedBytes;
                    String CurrentTaskName;

                    LoadingStatus();
                    LoadingStatus(uint totalBytes, uint loadedBytes,
                                  uint taskTotalBytes, uint taskLoadedBytes, const String& taskName);
                    LoadingStatus(const LoadingStatus& original);

                    LoadingStatus& operator = (const LoadingStatus& right);
                    bool operator == (const LoadingStatus& right) const;
                    inline bool operator != (const LoadingStatus& right) const;
                };

            public:
                GameAssetStorage();
                GameAssetStorage(GameModuleTree* modules);
                virtual ~GameAssetStorage();

                bool Preload(const String& name);
                GameAsset* Load(const String& name);

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
                        uint totalBytes;
                        uint loadedBytes;
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
    }

#   include <Bibim/GameAssetStorage.inl>

#endif