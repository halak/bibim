#pragma once
#ifndef __BIBIM_STREAM_H__
#define __BIBIM_STREAM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class Stream : public SharedObject
        {
            BBThisIsNoncopyableClass(Stream);
            public:
                enum SeekOrigin
                {
                    FromBegin,
                    FromEnd,
                    FromCurrent,
                };

            public:
                virtual ~Stream();

                virtual int Read(void* buffer, int size) = 0;
                virtual int Write(const void* buffer, int size) = 0;
                virtual void Flush() = 0;
                virtual int Seek(int offset, SeekOrigin origin) = 0;

                virtual int GetPosition();
                virtual int GetLength();

                virtual bool CanRead() const = 0;
                virtual bool CanWrite() const = 0;
                virtual bool CanSeek() const = 0;

            protected:
                Stream();
        };
    }

#endif