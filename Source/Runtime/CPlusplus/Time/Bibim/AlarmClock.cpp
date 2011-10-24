#include <Bibim/PCH.h>
#include <Bibim/AlarmClock.h>
#include <Bibim/Assert.h>
#include <algorithm>
#include <windows.h>

namespace Bibim
{
    AlarmClock::Callback::~Callback()
    {
    }

    AlarmClock::Callback::Result AlarmClock::Callback::OnTick(AlarmClock* /*clock*/, float /*elapsedAlarmTime*/, float /*alarmTime*/)
    {
        return Callback::Continue;
    }

    AlarmClock::Callback::Result AlarmClock::Callback::OnAlarm(AlarmClock* /*clock*/)
    {
        return Callback::Stop;
    }

    void AlarmClock::Callback::OnCancelled(AlarmClock* /*clock*/)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    AlarmClock::AlarmCounter::AlarmCounter()
    {
    }

    AlarmClock::AlarmCounter::AlarmCounter(float tickTime, float alarmTime)
        : RemainTickTime(tickTime),
          RemainAlarmTime(alarmTime)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    AlarmClock::Alarm::Alarm()
    {
    }

    AlarmClock::Alarm::Alarm(int group, float tickTime, float alarmTime)
        : Group(group),
          TickTime(tickTime),
          AlarmTime(alarmTime)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const int AlarmClock::DefaultGroup = 0;
    const float AlarmClock::InvalidTime = -1.0f;

    AlarmClock::AlarmClock()
    {
    }

    AlarmClock::~AlarmClock()
    {
    }

    void AlarmClock::Update(float dt, uint timestamp)
    {
        if (alarms.empty() || 
            Seal(timestamp))
            return;

        const int count = static_cast<int>(alarmCounters.size());
        bool needsGarbageCollection = false;
        for (int i = 0; i < count; i++)
        {
            //BBAssertDebug(count == alarmCounters.size());
            //BBAssertDebug(count == alarms.size());
            //BBAssertDebug(count == callbacks.size());

            //AlarmCounter& item = alarmCounters[i];

            if (alarmCounters[i].RemainTickTime >= 0.0f)
            {
                alarmCounters[i].RemainTickTime -= dt;
                if (alarmCounters[i].RemainTickTime <= 0.0f)
                {
                    if (callbacks[i])
                    {
                        switch (callbacks[i]->OnTick(this, alarms[i].AlarmTime - alarmCounters[i].RemainAlarmTime, alarms[i].AlarmTime))
                        {
                            case Callback::Continue:
                                alarmCounters[i].RemainTickTime = alarms[i].TickTime;
                                break;
                            case Callback::Stop:
                                callbacks[i].Reset();
                                needsGarbageCollection = true;
                                break;
                            case Callback::StopTick:
                                alarmCounters[i].RemainTickTime = InvalidTime;
                                break;
                            case Callback::Restart:
                                alarmCounters[i].RemainTickTime = alarms[i].TickTime;
                                alarmCounters[i].RemainAlarmTime = alarms[i].AlarmTime;
                                break;
                        }
                    }
                    else
                    {
                        needsGarbageCollection = true;
                        continue;
                    }
                }
            }

            if (alarmCounters[i].RemainAlarmTime >= 0.0f)
            {
                alarmCounters[i].RemainAlarmTime -= dt;
                if (alarmCounters[i].RemainAlarmTime <= 0.0f)
                {
                    if (callbacks[i])
                    {
                        switch (callbacks[i]->OnAlarm(this))
                        {
                            case Callback::Continue:
                            case Callback::Stop:
                            case Callback::StopTick:
                                callbacks[i].Reset();
                                needsGarbageCollection = true;
                                break;
                            case Callback::Restart:
                                alarmCounters[i].RemainTickTime = alarms[i].TickTime;
                                alarmCounters[i].RemainAlarmTime = alarms[i].AlarmTime;
                                break;
                        }
                    }
                    else
                    {
                        needsGarbageCollection = true;
                        continue;
                    }
                }
            }
        }

        if (needsGarbageCollection)
        {
            int newCount = static_cast<int>(alarms.size());
            for (int i = 0; i < newCount; i++)
            {
                if (callbacks[i] == nullptr)
                {
                    alarmCounters[i] = alarmCounters[newCount - 1];
                    alarms[i] = alarms[newCount - 1];
                    callbacks[i] = callbacks[newCount - 1];
                    newCount--;
                }
            }

            alarmCounters.resize(newCount);
            alarms.resize(newCount);
            callbacks.resize(newCount);
        }
    }

    void AlarmClock::Start(Callback* callback, int group, float tickTime, float alaramTime)
    {
        if (callback == nullptr)
            return;

        CallbackPtr sharedCallback = callback;

        //if (group == 1000)
        //{
        //    callback->OnCancelled(this);
        //    return;
        //}

        BBAssertDebug(std::find(callbacks.begin(), callbacks.end(), callback) == callbacks.end());

        alarmCounters.push_back(AlarmCounter(tickTime, alaramTime));
        alarms.push_back(Alarm(group, tickTime, alaramTime));
        callbacks.push_back(callback);
    }

    void AlarmClock::Cancel(int group)
    {
        const int count = static_cast<int>(alarms.size());
        for (int i = 0; i < count; i++)
        {
            if (alarms[i].Group == group)
            {
                if (callbacks[i])
                {
                    callbacks[i]->OnCancelled(this);
                    callbacks[i].Reset();
                }
            }
        }
    }

    void AlarmClock::Cancel(Callback* callback)
    {
        if (callback == nullptr)
            return;

        CallbackPtr sharedCallback = callback;

        const int count = static_cast<int>(callbacks.size());
        for (int i = 0; i < count; i++)
        {
            if (callbacks[i] == callback)
            {
                callbacks[i]->OnCancelled(this);
                callbacks[i].Reset();
            }
        }
    }

    void AlarmClock::CancelAll()
    {
        for (CallbackCollection::iterator it = callbacks.begin(); it != callbacks.end(); it++)
        {
            if (Callback* item = (*it))
            {
                item->OnCancelled(this);
                (*it).Reset();
            }
        }
    }
}