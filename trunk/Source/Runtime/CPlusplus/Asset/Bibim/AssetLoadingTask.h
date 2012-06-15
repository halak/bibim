#pragma once
#ifndef __BIBIM_GAMEASSETLOADINGTASK_H__
#define __BIBIM_GAMEASSETLOADINGTASK_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class AssetLoadingTask
        {
            BBThisIsNoncopyableClass(AssetLoadingTask);
            public:
                virtual ~AssetLoadingTask();

                /// Background Loading을 시작합니다.
                /// 이 Method는 보통 Background Loading Thread에서 호출됩니다.
                virtual void Execute() = 0;
                /// 현재 진행 중인 Loading을 취소합니다.
                /// 이 Method는 보통 Main Thread에서 호출되며,
                /// 다른 Thread에서 Execute 되고 있는 상태지만 그 Thread는 정지되어 있습니다.
                virtual void Cancel();

                inline const String& GetName() const;
                inline int GetTotalBytes() const;
                inline int GetLoadedBytes() const;

                virtual bool IsPreloading() const;

            protected:
                AssetLoadingTask(const String& name, int totalBytes);

                inline void SetLoadedBytes(int value);
                inline void AddLoadedBytes(int value);

            private:
                const String name;
                const int totalBytes;
                int loadedBytes;
        };

        class AssetPreloadingTask : public AssetLoadingTask
        {
            public:
                virtual ~AssetPreloadingTask();

                virtual bool IsPreloading() const;

                inline GameAssetStorage* GetStorage() const;

            protected:
                AssetPreloadingTask(const String& name, GameAssetStorage* storage);

                void Register(GameAsset* asset);
                void Unregister();

            private:
                GameAssetStorage* storage;
        };
    }

#   include <Bibim/AssetLoadingTask.inl>

#endif