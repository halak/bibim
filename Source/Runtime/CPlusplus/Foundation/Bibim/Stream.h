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
            public:
                virtual ~Stream();

                virtual int Read(void* buffer, int size) = 0;
                virtual bool ReadAsync();
                virtual int Write(const void* buffer, int size) = 0;
                virtual bool WriteAsync();
                virtual void Flush() = 0;

                virtual String ReadText();

                virtual bool CanRead() const = 0;
                virtual bool CanWrite() const = 0;

            protected:
                Stream();

            private:
                Stream(const Stream&);
                Stream& operator = (const Stream&);
        };
    }

#endif