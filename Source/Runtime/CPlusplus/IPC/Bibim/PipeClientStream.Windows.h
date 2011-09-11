#pragma once
#ifndef __BIBIM_PIPECLIENTSTREAM_WINDOWS_H__
#define __BIBIM_PIPECLIENTSTREAM_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/PipeStream.h>

    namespace Bibim
    {
        class PipeClientStream : public PipeStream
        {
            BBThisIsNoncopyableClass(PipeClientStream);
            public:
                PipeClientStream();
                PipeClientStream(const String& name, AccessMode accessMode);
                PipeClientStream(const String& machineName, const String& name, AccessMode accessMode);
                virtual ~PipeClientStream();

                bool Open(const String& name, AccessMode accessMode);
                bool Open(const String& machineName, const String& name, AccessMode accessMode);
                void Close();

                inline const String& GetMachineName() const;

            private:
                bool OpenActually(const String& fullName, const String& name, AccessMode accessMode);

            private:
                String machineName;
        };
    }

#   include <Bibim/PipeClientStream.Windows.inl>

#endif