#pragma once
#ifndef __BIBIM_COMMANDQUEUE_H__
#define __BIBIM_COMMANDQUEUE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/TimelineGameModule.h>
#   include <list>

    namespace Bibim
    {
        class CommandQueue : public TimelineGameModule
        {
            BBModuleClass(CommandQueue, TimelineGameModule, 'C', 'M', 'D', 'Q');
            public:
                class Event
                {
                    public:
                        Event(float time, int frame, Command* command);
                        Event(const Event& original);

                        inline float GetTime() const;
                        inline int GetFrame() const;
                        inline Bibim::Command* GetCommand() const;

                        Event& operator = (const Event& original);

                    private:
                        float time;
                        int frame;
                        CommandPtr command;
                };

                typedef std::list<Event> EventCollection;

            public:
                CommandQueue();
                virtual ~CommandQueue();

                inline void Reset();
                void Reset(float time, int frame);
                virtual void Update(float dt, int timestamp);

                void Execute(Command* command);

                inline const EventCollection& GetEvents() const;

            private:
                float time;
                int frame;
                EventCollection events;
        };
    }

#   include <Bibim/CommandQueue.inl>

#endif