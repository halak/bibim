#pragma once
#ifndef __BIBIM_FILESTREAM_WINDOWS_H__
#define __BIBIM_FILESTREAM_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Stream.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class FileStream : public Stream
        {
            public:
                enum AccessMode
                {
                    ReadOnly,
                    WriteOnly,
                };

            public:
                FileStream(const String& path, AccessMode accessMode);
                virtual ~FileStream();

                void Close();

                virtual int Read(void* buffer, int size);
                virtual int Write(const void* buffer, int size);
                virtual void Flush();

                int GetPosition() const;
                int GetSize() const;
                uint64 GetPosition64() const;
                uint64 GetSize64() const;

                virtual bool CanRead() const;
                virtual bool CanWrite() const;

            private:
                void StoreCache();

            private:
                void* handle;

                int position;
                int size;
                uint64 position64;
                uint64 size64;

                std::vector<byte> cache;
                int cacheOffset;
                int cacheSize;

                bool canRead;
                bool canWrite;
        };
    }

#   include <Bibim/FileStream.Windows.inl>

#endif