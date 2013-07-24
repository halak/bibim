#pragma once
#ifndef __BIBIM_TIMELINEGAMEMODULE_H__
#define __BIBIM_TIMELINEGAMEMODULE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UpdateableGameModule.h>

    namespace Bibim
    {
        class TimelineGameModule : public UpdateableGameModule
        {
            BBAbstractModuleClass(TimelineGameModule, UpdateableGameModule);
            public:
                virtual ~TimelineGameModule();

                inline Timeline* GetTimeline() const;
                void SetTimeline(Timeline* value);

            protected:
                TimelineGameModule();

            private:
                Timeline* timeline;
        };
    }

#endif