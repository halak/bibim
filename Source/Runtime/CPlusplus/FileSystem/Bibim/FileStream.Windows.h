#pragma once
#ifndef __BIBIM_FILESTREAM_WINDOWS_H__
#define __BIBIM_FILESTREAM_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Stream.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        struct FileAccess
        {
            enum E
            {
                Read,
                Write
            };
        };

        struct FileShare
        {
            enum E
            {
                None   = 0,
                Read   = (1 << 0),
                Write  = (1 << 1),
                Delete = (1 << 2),
            };
        };

        class FileStream : public Stream
        {
            public:
                FileStream(const String& path, FileAccess::E access, FileShare::E shareMode);
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
                struct Fields;
                Fields* mPointer;
                Fields& m;
        };
    }

#endif