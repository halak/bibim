#pragma once
#ifndef __BIBIM_TIMELINEGAMECOMPONENT_H__
#define __BIBIM_TIMELINEGAMECOMPONENT_H__

#include <Bibim/FWD.h>
#include <Bibim/UpdateableGameComponent.h>

namespace Bibim
{
    class TimelineGameComponent : public UpdateableGameComponent
    {
        BBAbstractComponentClass(TimelineGameComponent, UpdateableGameComponent);
        public:
            virtual ~TimelineGameComponent();

            inline Timeline* GetTimeline() const;
            void SetTimeline(Timeline* value);

        protected:
            TimelineGameComponent();

        private:
            Timeline* timeline;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Timeline* TimelineGameComponent::GetTimeline() const
    {
        return timeline;
    }
}

#endif