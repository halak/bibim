#pragma once
#ifndef __BIBIM_TIMELINEGAMEMODULE_H__
#define __BIBIM_TIMELINEGAMEMODULE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UpdateableGameModule.h>

    namespace Bibim
    {
        class TimelineGameModule : public UpdateableGameModule
        {
            BBGameModuleClass('T', 'L', 'G', 'M');
            public:
                TimelineGameModule();
                virtual ~TimelineGameModule();

                inline Timeline* GetTimeline() const;
                void SetTimeline(Timeline* value);

            private:
                Timeline* timeline;
        };
    }

#    include <Bibim/TimelineGameModule.inl>

#endif