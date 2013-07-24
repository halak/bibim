#pragma once
#ifndef __BIBIM_MPQ_H__
#define __BIBIM_MPQ_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class MPQ : public SharedObject
        {
            public:
                MPQ(const String& path);
                virtual ~MPQ();

                void Close();

                bool Has(const String& path) const;

                inline void* GetHandle() const;

            private:
                void* handle;
        };

        void* MPQ::GetHandle() const
        {
            return handle;
        }
    }

#endif