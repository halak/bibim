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

                /// Background Loading�� �����մϴ�.
                /// �� Method�� ���� Background Loading Thread���� ȣ��˴ϴ�.
                virtual void Execute() = 0;
                /// ���� ���� ���� Loading�� ����մϴ�.
                /// �� Method�� ���� Main Thread���� ȣ��Ǹ�,
                /// �ٸ� Thread���� Execute �ǰ� �ִ� �������� �� Thread�� �����Ǿ� �ֽ��ϴ�.
                virtual void Cancel();

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