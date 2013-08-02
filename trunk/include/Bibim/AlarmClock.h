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

        private:
            struct AlarmCounter
            {
                float RemainTickTime;
                float RemainAlarmTime;

                inline AlarmCounter();
                inline AlarmCounter(float tickTime, float alarmTime);
            };

            struct Alarm
            {
                int   Group;
                float TickTime;
                float AlarmTime;

                inline Alarm();
                inline Alarm(int group, float tickTime, float alarmTime);
            };

            typedef std::vector<AlarmCounter> AlarmCounterCollection;
            typedef std::vector<Alarm> AlarmCollection;

        private:
            AlarmCounterCollection alarmCounters;
            AlarmCollection alarms;
            CallbackCollection callbacks;
    };
}

#endif