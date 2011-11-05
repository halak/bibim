#pragma once
#ifndef __BIBIM_TIMELINE_H__
#define __BIBIM_TIMELINE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UpdateableGameModule.h>
#   include <vector>

    namespace Bibim
    {
        class Timeline : public UpdateableGameModule
        {
            BBModuleClass(Timeline, UpdateableGameModule, 'T', 'M', 'L', 'N');
            public:
                typedef std::vector<UpdateableGameModule*> ItemCollection;

            public:
                Timeline();
                virtual ~Timeline();

                virtual void Update(float dt, int timestamp);

                void Add(UpdateableGameModule* item);
                bool Remove(UpdateableGameModule* item);
                void RemoveAt(int index);
                void Clear();
                bool Contains(UpdateableGameModule* item) const;

                inline const ItemCollection& GetItems() const;

                inline float GetSpeed() const;
                void         SetSpeed(float value);

            private:
                ItemCollection items;
                ItemCollection temporaryItems;
                float speed;

                friend class SubTimeline;
                friend class TimelineGameModule;
        };
    }

#   include <Bibim/Timeline.inl>

#endif