#pragma once
#ifndef __BIBIM_PIPESTREAM_WINDOWS_H__
#define __BIBIM_PIPESTREAM_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Stream.h>
#   include <Bibim/String.h>
#   include <windows.h>

    namespace Bibim
    {
        class PipeStream : public Stream
        {
            BBThisIsNoncopyableClass(PipeStream);
            public:
                enum AccessMode
                {
                    ReadOnly,
                    WriteOnly,
                    ReadAndWrite,
                };

            public:
                virtual ~PipeStream();

                virtual void Disconnect() = 0;

                virtual int Read(void* buffer, int size);
                virtual int Write(const void* buffer, int size);
                virtual void Flush();
                virtual int Seek(int offset, SeekOrigin origin);

                inline const String& GetName() const;
                inline AccessMode GetAccessMode() const;

                virtual bool IsConnected() const = 0;

                virtual bool CanRead() const;
                virtual bool CanWrite() const;
                virtual bool CanSeek() const;

            protected:
                PipeStream(const String& name, AccessMode accessMode);

                inline HANDLE GetHandle() const;
                inline void SetHandle(HANDLE value);

            private:
                HANDLE handle;
                String name;
                AccessMode accessMode;
        };
    }

#   include <Bibim/PipeStream.Windows.inl>

#endif