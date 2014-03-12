#pragma once
#ifndef __BIBIM_ALARMCLOCK_H__
#define __BIBIM_ALARMCLOCK_H__

#include <Bibim/FWD.h>
#include <Bibim/TimelineGameModule.h>
#include <Bibim/SharedObject.h>
#include <vector>

namespace Bibim
{
    class AlarmClock : public TimelineGameModule
    {
        BBModuleClass(AlarmClock, TimelineGameModule, 'A', 'C', 'L', 'K');
        public:
            class Callback : public SharedObject
            {
                protected:
                    enum Result
                    {
                        Continue,
                        Stop,
                        StopTick,
                        Restart,
                    };

                protected:
                    virtual ~Callback();

                    virtual Result OnTick(AlarmClock* clock, float elapsedAlarmTime, float alarmTime);
                    virtual Result OnAlarm(AlarmClock* clock);
                    virtual void OnCancelled(AlarmClock* clock);

                private:
                    friend class AlarmClock;
            };
            typedef SharedPointer<Callback>  CallbackPtr;
            typedef std::vector<CallbackPtr> CallbackCollection;

        public:
            static const int DefaultGroup;
            static const float InvalidTime;

        public:
            AlarmClock();
            virtual ~AlarmClock();

            virtual void Update(float dt, int timestamp);

            void Start(Callback* callback, int group, float tickTime, float alaramTime);
            void Cancel(int group);
            void Cancel(Callback* callback);
            void CancelAll();

            inline float GetScale(int group) const;
            void SetScale(int group, float value);

        private:
            struct AlarmCounter
            {
                float Scale;
                float RemainTickTime;
                float RemainAlarmTime;

                inline AlarmCounter();
                inline AlarmCounter(float scale, float tickTime, float alarmTime);
            };

            struct Alarm
            {
                int   Group;
                float TickTime;
                float AlarmTime;

                inline Alarm();
                inline Alarm(int group, float tickTime, float alarmTime);
            };

            struct Group
            {
                int ID;
                float Scale;

                inline Group();
                inline Group(int id, float scale);
            };

            typedef std::vector<AlarmCounter> AlarmCounterCollection;
            typedef std::vector<Alarm> AlarmCollection;
            typedef std::vector<Group> GroupCollection;

            inline       Group* FindGroup(int id);
            inline const Group* FindGroup(int id) const;

        private:
            AlarmCounterCollection alarmCounters;
            AlarmCollection alarms;
            CallbackCollection callbacks;

            GroupCollection groups;
    };

    AlarmClock::Group* AlarmClock::FindGroup(int id)
    {
        for (GroupCollection::iterator it = groups.begin(); it != groups.end(); ++it)
        {
            if ((*it).ID == id)
                return &(*it);
        }

        return nullptr;
    }

    const AlarmClock::Group* AlarmClock::FindGroup(int id) const
    {
        for (GroupCollection::const_iterator it = groups.begin(); it != groups.end(); ++it)
        {
            if ((*it).ID == id)
                return &(*it);
        }

        return nullptr;
    }

    float AlarmClock::GetScale(int group) const
    {
        if (const Group* g = FindGroup(group))
            return g->Scale;
        else
            return 1.0f;
    }
}

#endif