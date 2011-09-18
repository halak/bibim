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

                virtual void Execute() = 0;

                inline const String& GetName() const;
                inline uint GetTotalBytes() const;
                inline uint GetLoadedBytes() const;

            protected:
                AssetLoadingTask(const String& name, uint totalBytes);

                inline void SetLoadedBytes(uint value);
                inline void AddLoadedBytes(uint value);

            private:
                const String name;
                const uint totalBytes;
                uint loadedBytes;
        };
    }

#   include <Bibim/AssetLoadingTask.inl>

#endif