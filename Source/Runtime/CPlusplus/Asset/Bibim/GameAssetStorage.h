#pragma once
#ifndef __BIBIM_GAMEASSETSTORAGE_H__
#define __BIBIM_GAMEASSETSTORAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Lock.h>
#   include <Bibim/String.h>
#   include <Bibim/Thread.h>
#   include <map>
#   include <queue>
#   include <vector>

    namespace Bibim
    {
        class GameAssetStorage : public GameModule
        {
            BBGameModuleClass('G', 'A', 'S', 'T');
            public:
                typedef std::map<String, GameAsset*> AssetTable;
                typedef std::vector<AssetProvider*> ProviderCollection;

            public:
                GameAssetStorage();
                GameAssetStorage(GameModuleTree* modules);
                virtual ~GameAssetStorage();

                GameAsset* Load(const String& name);

                inline GameModuleTree* GetModules() const;
                inline void SetModules(GameModuleTree* value);

                inline const AssetTable& GetAssets() const;
                inline const ProviderCollection& GetProviders() const;

            protected:
                virtual void OnStatusChanged(Status old);

                class LoadingThread : public Thread
                {
                    public:
                        typedef std::queue<AssetLoadingTask*> TaskQueue;

                    public:
                        LoadingThread();
                        virtual ~LoadingThread();

                        void AddTask(AssetLoadingTask* item);

                        inline void RequestClose();

                    protected:
                        virtual void OnWork();

                    private:
                        TaskQueue taskQueue;
                        Lock taskQueueLock;
                        bool closed;
                };

            private:
                void Add(AssetLoadingTask* item); // call in AssetReader
                void Add(AssetProvider* item); // call in AssetProvider
                void Remove(AssetProvider* item); // call in AssetProvider

            private:
                GameModuleTree* modules;
                AssetTable assets;
                ProviderCollection providers;

                LoadingThread loadingThread;

                friend class AssetProvider;
                friend class AssetReader;
        };
    }

#   include <Bibim/GameAssetStorage.inl>

#endif