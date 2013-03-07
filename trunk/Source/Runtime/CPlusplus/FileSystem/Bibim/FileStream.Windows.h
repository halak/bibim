#pragma once
#ifndef __BIBIM_FILESTREAM_WINDOWS_H__
#define __BIBIM_FILESTREAM_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Stream.h>
#   include <Bibim/String.h>

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
                virtual int Seek(int offset, SeekOrigin origin);

                virtual int GetPosition();
                virtual int GetLength();

                virtual bool CanRead() const;
                virtual bool CanWrite() const;
                virtual bool CanSeek() const;

            private:
                void* handle;
                bool canRead;
                bool canWrite;
        };
    }

#   include <Bibim/FileStream.Windows.inl>

#endif