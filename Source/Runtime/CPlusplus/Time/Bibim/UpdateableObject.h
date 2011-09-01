#pragma once
#ifndef __BIBIM_UPDATEABLEOBJECT_H__
#define __BIBIM_UPDATEABLEOBJECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/IUpdateable.h>

    namespace Bibim
    {
        class UpdateableObject : public SharedObject, public IUpdateable
        {
            public:
                UpdateableObject();
                virtual ~UpdateableObject();

                inline Timeline* GetTimeline() const;
                void SetTimeline(Timeline* value);

            protected:
                inline bool Seal(uint timestamp);

            private:
                Timeline* timeline;
                uint lastTimestamp;
        };
    }

#    include <Bibim/UpdateableObject.inl>

#endif