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
                PipeClientStream(const String& name, AccessMode accessMode);
                PipeClientStream(const String& serverName, const String& name, AccessMode accessMode);
                virtual ~PipeClientStream();

                void Connect();
                virtual void Disconnect();

                inline const String& GetServerName() const;

                virtual bool IsConnected() const;

            private:
                String GetFullName() const;
                DWORD GetPlatformAccessMode() const;

            private:
                String serverName;
        };
    }

#   include <Bibim/PipeClientStream.Windows.inl>

#endif