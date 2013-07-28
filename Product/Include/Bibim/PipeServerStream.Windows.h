﻿#pragma once
#ifndef __BIBIM_PIPESERVERSTREAM_WINDOWS_H__
#define __BIBIM_PIPESERVERSTREAM_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/PipeStream.h>

    namespace Bibim
    {
        class PipeServerStream : public PipeStream
        {
            BBThisIsNoncopyableClass(PipeServerStream);
            public:
                PipeServerStream(const String& name, AccessMode accessMode);
                virtual ~PipeServerStream();

                bool WaitForConnection();

                virtual void Disconnect();

                virtual bool IsConnected() const;

            private:
        };
    }

#endif