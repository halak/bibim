#pragma once
#ifndef __BIBIM_UPDATEABLEGAMECOMPONENT_H__
#define __BIBIM_UPDATEABLEGAMECOMPONENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/IUpdateable.h>

    namespace Bibim
    {
        class UpdateableGameComponent : public GameComponent, public IUpdateable
        {
            BBClassFOURCC('U', 'P', 'G', 'C');
            public:
                UpdateableGameComponent();
                virtual ~UpdateableGameComponent();

                inline Timeline* GetTimeline() const;
                void SetTimeline(Timeline* value);

                virtual IUpdateable* QueryUpdateableInterface();

            protected:
                inline bool Seal(uint timestamp);

            private:
                Timeline* timeline;
                uint lastTimestamp;
        };
    }

#    include <Bibim/UpdateableGameComponent.inl>

#endif