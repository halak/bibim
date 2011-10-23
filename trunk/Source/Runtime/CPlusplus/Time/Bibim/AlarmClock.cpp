#include <Bibim/PCH.h>
#include <Bibim/AlarmClock.h>
#include <Bibim/Assert.h>
#include <algorithm>

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
    const float AlarmClock::InvalidTime = 0.0f;

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
            AlarmCounter& item = alarmCounters[i];

            if (item.RemainTickTime >= 0.0f)
            {
                item.RemainTickTime -= dt;
                if (item.RemainTickTime <= 0.0f)
                {
                    if (callbacks[i])
                    {
                        switch (callbacks[i]->OnTick(this, alarms[i].AlarmTime - item.RemainAlarmTime, alarms[i].AlarmTime))
                        {
                            case Callback::Continue:
                                item.RemainTickTime = alarms[i].TickTime;
                                break;
                            case Callback::Stop:
                                callbacks[i].Reset();
                                needsGarbageCollection = true;
                                break;
                            case Callback::StopTick:
                                item.RemainTickTime = -1.0f;
                                break;
                            case Callback::Restart:
                                item.RemainTickTime = alarms[i].TickTime;
                                item.RemainAlarmTime = alarms[i].AlarmTime;
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

            if (item.RemainAlarmTime >= 0.0f)
            {
                item.RemainAlarmTime -= dt;
                if (item.RemainAlarmTime <= 0.0f)
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
                                item.RemainTickTime = alarms[i].TickTime;
                                item.RemainAlarmTime = alarms[i].AlarmTime;
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
            for (int i = 0; i < newCount;)
            {
                if (callbacks[i] == nullptr)
                {
                    alarmCounters[i] = alarmCounters[newCount - 1];
                    alarms[i] = alarms[newCount - 1];
                    callbacks[i] = callbacks[newCount - 1];
                    newCount--;
                }
                else
                    i++;
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