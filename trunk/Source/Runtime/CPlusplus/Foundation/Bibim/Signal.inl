#include <Bibim/Assert.h>
#include <Bibim/Delete.h>
#include <algorithm>
#include <memory.h>

namespace Bibim
{
    SignalBase::~SignalBase()
    {
        DeleteAll(slots);
    }

    int SignalBase::GetNumberOfSlots() const
    {
        return static_cast<int>(slots.size());
    }

    void SignalBase::Disconnect(Slot* slot)
    {
        std::vector<Slot*>::iterator it = std::find(slots.begin(), slots.end(), slot);
        BBAssertDebug(it != slots.end());
        Slot* deletingSlot = (*it);
        slots.erase(it);
        delete deletingSlot;
    }

    void SignalBase::Disconnect(const void* instance, const void* function, int functionSize)
    {
        for (std::vector<Slot*>::iterator it = slots.begin(); it != slots.end(); it++)
        {
            if ((*it)->Compare(instance, function, functionSize))
            {
                Slot* deletingSlot = (*it);
                slots.erase(it);
                delete deletingSlot;
                break;
            }
        }
    }

    void SignalBase::DisconnectAll(const void* instance, const void* function, int functionSize)
    {
        for (std::vector<Slot*>::iterator it = slots.begin(); it != slots.end();)
        {
            if ((*it)->Compare(instance, function, functionSize))
            {
                Slot* deletingSlot = (*it);
                it = slots.erase(it);
                delete deletingSlot;
            }
            else
                it++;
        }
    }

    template <typename T> static T SignalBase::Strip(T pointer)
    {
        return pointer;
    }

    template <typename T> static T* SignalBase::Strip(SharedPointer<T> pointer)
    {
        return pointer.GetPointee();
    }

    template <typename T> static T* SignalBase::Strip(WeakPointer<T> pointer)
    {
        return pointer.Lock().GetPointee();
    }

    template <typename F> bool SignalBase::CompareGlobalFunctionTemplate(const F* globalFunction, const void* otherInstance, const void* otherFunction, int otherFunctionSize)
    {
        return otherInstance == nullptr && globalFunction == otherFunction && sizeof(globalFunction) == otherFunctionSize;
    }

    template <typename C> bool SignalBase::CompareMemberFunctionTemplate(const C* instance, const void* memberFunction, int memberFunctionSize, const void* otherInstance, const void* otherFunction, int otherFunctionSize)
    {
        // 둘 중에 하나라도 nullptr이면 검사 실패.
        // instance가 달라도 검사 실패. 
        if (otherInstance == nullptr || instance == nullptr || instance != otherInstance)
            return false;

        if (otherFunction)
        {
            if (memberFunctionSize == otherFunctionSize)
                return memcmp(memberFunction, otherFunction, memberFunctionSize) == 0;
            else
                return false;
        }
        else
            return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    SignalBase::Slot::Slot(SignalBase* signal)
        : signal(signal)
    {
    }

    SignalBase::Slot::~Slot()
    {
    }

    void SignalBase::Slot::Disconnect()
    {
        signal->Disconnect(this);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}