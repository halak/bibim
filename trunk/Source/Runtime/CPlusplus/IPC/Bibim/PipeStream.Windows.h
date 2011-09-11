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

                virtual int Read(void* buffer, int size);
                virtual int Write(const void* buffer, int size);
                virtual void Flush();

                inline const String& GetName() const;
                inline AccessMode GetAccessMode() const;

                inline bool IsOpen() const;

                virtual bool CanRead() const;
                virtual bool CanWrite() const;

            protected:
                PipeStream();

                void Initialize(HANDLE handle, const String& name, AccessMode accessMode);
                void Finalize();

                inline HANDLE GetHandle() const;

            private:
                HANDLE handle;
                String name;
                AccessMode accessMode;
        };
    }

#   include <Bibim/PipeStream.Windows.inl>

#endif