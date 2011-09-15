#pragma once
#ifndef __BIBIM_SUBTIMELINE_H__
#define __BIBIM_SUBTIMELINE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Timeline.h>

    namespace Bibim
    {
        class SubTimeline : public Timeline
        {
            BBGameModuleClass('S', 'B', 'T', 'L');
            public:
                SubTimeline();
                virtual ~SubTimeline();

                inline Timeline* GetParent() const;
                void SetParent(Timeline* value);

            private:
                Timeline* parent;
        };
    }

#   include <Bibim/SubTimeline.inl>

#endif