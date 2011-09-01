#pragma once
#ifndef __BIBIM_SIGNAL_H__
#define __BIBIM_SIGNAL_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        class SignalBase
        {
            public:
                inline int GetNumberOfSlots() const;

            protected:
                class Slot;

            protected:
                inline ~SignalBase();

            protected:
                inline void Disconnect(Slot* slot);
                inline void Disconnect(const void* instance, const void* function, int functionSize);
                inline void DisconnectAll(const void* instance, const void* function, int functionSize);

                template <typename T> inline static T  Strip(T pointer);
                template <typename T> inline static T* Strip(SharedPointer<T> pointer);
                template <typename T> inline static T* Strip(WeakPointer<T> pointer);

                template <typename T> struct Extract { };
                template <typename T> struct Extract<T*>               { typedef T Result; };
                template <typename T> struct Extract<SharedPointer<T>> { typedef T Result; };
                template <typename T> struct Extract<WeakPointer<T>>   { typedef T Result; };

                template <typename F> inline static bool CompareGlobalFunctionTemplate(const F* globalFunction, const void* otherInstance, const void* otherFunction, int otherFunctionSize);
                template <typename C> inline static bool CompareMemberFunctionTemplate(const C* instance, const void* memberFunction, int memberFunctionSize, const void* otherInstance, const void* otherFunction, int otherFunctionSize);

            protected:
                class Slot
                {
                    friend class SignalBase;
                    public:
                        inline Slot(SignalBase* signal);
                        inline virtual ~Slot();
                        inline void Disconnect();

                        virtual bool Compare(const void* instance, const void* function, int functionSize) = 0;

                    private:
                        SignalBase* signal;
                };

            protected:
                std::vector<Slot*> slots;
        };

        template <typename Arg1 = void, typename Arg2 = void, typename Arg3 = void, typename Arg4 = void, typename Arg5 = void>
        class Signal : public SignalBase
        {
            private:
                class Slot : public SignalBase::Slot
                {
                    public:
                        Slot(SignalBase* signal)
                            : SignalBase::Slot(signal)
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) = 0;
                };

                class GlobalFunctionSlot : public Slot
                {
                    public:
                        typedef void (*Function)(Arg1, Arg2, Arg3, Arg4, Arg5);

                    public:
                        GlobalFunctionSlot(SignalBase* signal, Function function)
                            : Slot(signal),
                              function(function)
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
                        {
                            (*function)(arg1, arg2, arg3, arg4, arg5);
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareGlobalFunctionTemplate(this->function, instance, function, functionSize);
                        }

                    private:
                        Function function;
                };

                template <typename ClassType, typename InstanceType>
                class MemberFunctionSlot : public Slot
                {
                    public:
                        typedef void (ClassType::*Function)(Arg1, Arg2, Arg3, Arg4, Arg5);
                        typedef void (ClassType::*ConstFunction)(Arg1, Arg2, Arg3, Arg4, Arg5) const;

                    public:
                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, Function function)
                            : Slot(signal),
                              instance(instance),
                              function(function)
                        {
                        }

                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, ConstFunction function)
                            : Slot(signal),
                              instance(instance),
                              function(reinterpret_cast<Function>(function))
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
                        {
                            if (ClassType* c = Strip(instance))
                                (c->*function)(arg1, arg2, arg3, arg4, arg5);
                            else
                                Disconnect();
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareMemberFunctionTemplate(Strip(this->instance), &this->function, sizeof(this->function), instance, function, functionSize);
                        }

                    private:
                        InstanceType instance;
                        Function function;
                };

            public:
                void Emit(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
                {
                    std::vector<SignalBase::Slot*> temporarySlots = slots;
                    for (std::vector<SignalBase::Slot*>::iterator it = temporarySlots.begin(); it != temporarySlots.end(); it++)
                        static_cast<Slot*>(*it)->Invoke(arg1, arg2, arg3, arg4, arg5);
                }

                void Connect(typename GlobalFunctionSlot::Function function)
                {
                    slots.push_back(new GlobalFunctionSlot(this, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                void Disconnect(typename GlobalFunctionSlot::Function function)
                {
                    SignalBase::Disconnect(nullptr, function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance)
                {
                    SignalBase::DisconnectAll(Strip(instance), nullptr, 0);
                }
        };

        template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
        class Signal<Arg1, Arg2, Arg3, Arg4, void> : public SignalBase
        {
            private:
                class Slot : public SignalBase::Slot
                {
                    public:
                        Slot(SignalBase* signal)
                            : SignalBase::Slot(signal)
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) = 0;
                };

                class GlobalFunctionSlot : public Slot
                {
                    public:
                        typedef void (*Function)(Arg1, Arg2, Arg3, Arg4);

                    public:
                        GlobalFunctionSlot(SignalBase* signal, Function function)
                            : Slot(signal),
                              function(function)
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
                        {
                            (*function)(arg1, arg2, arg3, arg4);
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareGlobalFunctionTemplate(this->function, instance, function, functionSize);
                        }

                    private:
                        Function function;
                };

                template <typename ClassType, typename InstanceType>
                class MemberFunctionSlot : public Slot
                {
                    public:
                        typedef void (ClassType::*Function)(Arg1, Arg2, Arg3, Arg4);
                        typedef void (ClassType::*ConstFunction)(Arg1, Arg2, Arg3, Arg4) const;

                    public:
                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, Function function)
                            : Slot(signal),
                              instance(instance),
                              function(function)
                        {
                        }

                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, ConstFunction function)
                            : Slot(signal),
                              instance(instance),
                              function(reinterpret_cast<Function>(function))
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
                        {
                            if (ClassType* c = Strip(instance))
                                (c->*function)(arg1, arg2, arg3, arg4);
                            else
                                Disconnect();
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareMemberFunctionTemplate(Strip(this->instance), &this->function, sizeof(this->function), instance, function, functionSize);
                        }

                    private:
                        InstanceType instance;
                        Function function;
                };

            public:
                void Emit(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
                {
                    std::vector<SignalBase::Slot*> temporarySlots = slots;
                    for (std::vector<SignalBase::Slot*>::iterator it = temporarySlots.begin(); it != temporarySlots.end(); it++)
                        static_cast<Slot*>(*it)->Invoke(arg1, arg2, arg3, arg4);
                }

                void Connect(typename GlobalFunctionSlot::Function function)
                {
                    slots.push_back(new GlobalFunctionSlot(this, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                void Disconnect(typename GlobalFunctionSlot::Function function)
                {
                    SignalBase::Disconnect(nullptr, function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance)
                {
                    SignalBase::DisconnectAll(Strip(instance), nullptr, 0);
                }
        };

        template <typename Arg1, typename Arg2, typename Arg3>
        class Signal<Arg1, Arg2, Arg3, void, void> : public SignalBase
        {
            private:
                class Slot : public SignalBase::Slot
                {
                    public:
                        Slot(SignalBase* signal)
                            : SignalBase::Slot(signal)
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3) = 0;
                };

                class GlobalFunctionSlot : public Slot
                {
                    public:
                        typedef void (*Function)(Arg1, Arg2, Arg3);

                    public:
                        GlobalFunctionSlot(SignalBase* signal, Function function)
                            : Slot(signal),
                              function(function)
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3)
                        {
                            (*function)(arg1, arg2, arg3);
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareGlobalFunctionTemplate(this->function, instance, function, functionSize);
                        }

                    private:
                        Function function;
                };

                template <typename ClassType, typename InstanceType>
                class MemberFunctionSlot : public Slot
                {
                    public:
                        typedef void (ClassType::*Function)(Arg1, Arg2, Arg3);
                        typedef void (ClassType::*ConstFunction)(Arg1, Arg2, Arg3) const;

                    public:
                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, Function function)
                            : Slot(signal),
                              instance(instance),
                              function(function)
                        {
                        }

                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, ConstFunction function)
                            : Slot(signal),
                              instance(instance),
                              function(reinterpret_cast<Function>(function))
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2, Arg3 arg3)
                        {
                            if (ClassType* c = Strip(instance))
                                (c->*function)(arg1, arg2, arg3);
                            else
                                Disconnect();
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareMemberFunctionTemplate(Strip(this->instance), &this->function, sizeof(this->function), instance, function, functionSize);
                        }

                    private:
                        InstanceType instance;
                        Function function;
                };

            public:
                void Emit(Arg1 arg1, Arg2 arg2, Arg3 arg3)
                {
                    std::vector<SignalBase::Slot*> temporarySlots = slots;
                    for (std::vector<SignalBase::Slot*>::iterator it = temporarySlots.begin(); it != temporarySlots.end(); it++)
                        static_cast<Slot*>(*it)->Invoke(arg1, arg2, arg3);
                }

                void Connect(typename GlobalFunctionSlot::Function function)
                {
                    slots.push_back(new GlobalFunctionSlot(this, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                void Disconnect(typename GlobalFunctionSlot::Function function)
                {
                    SignalBase::Disconnect(nullptr, function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance)
                {
                    SignalBase::DisconnectAll(Strip(instance), nullptr, 0);
                }
        };

        template <typename Arg1, typename Arg2>
        class Signal<Arg1, Arg2, void, void, void> : public SignalBase
        {
            private:
                class Slot : public SignalBase::Slot
                {
                    public:
                        Slot(SignalBase* signal)
                            : SignalBase::Slot(signal)
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2) = 0;
                };

                class GlobalFunctionSlot : public Slot
                {
                    public:
                        typedef void (*Function)(Arg1, Arg2);

                    public:
                        GlobalFunctionSlot(SignalBase* signal, Function function)
                            : Slot(signal),
                              function(function)
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2)
                        {
                            (*function)(arg1, arg2);
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareGlobalFunctionTemplate(this->function, instance, function, functionSize);
                        }

                    private:
                        Function function;
                };

                template <typename ClassType, typename InstanceType>
                class MemberFunctionSlot : public Slot
                {
                    public:
                        typedef void (ClassType::*Function)(Arg1, Arg2);
                        typedef void (ClassType::*ConstFunction)(Arg1, Arg2) const;

                    public:
                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, Function function)
                            : Slot(signal),
                              instance(instance),
                              function(function)
                        {
                        }

                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, ConstFunction function)
                            : Slot(signal),
                              instance(instance),
                              function(reinterpret_cast<Function>(function))
                        {
                        }

                        virtual void Invoke(Arg1 arg1, Arg2 arg2)
                        {
                            if (ClassType* c = Strip(instance))
                                (c->*function)(arg1, arg2);
                            else
                                Disconnect();
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareMemberFunctionTemplate(Strip(this->instance), &this->function, sizeof(this->function), instance, function, functionSize);
                        }

                    private:
                        InstanceType instance;
                        Function function;
                };

            public:
                void Emit(Arg1 arg1, Arg2 arg2)
                {
                    std::vector<SignalBase::Slot*> temporarySlots = slots;
                    for (std::vector<SignalBase::Slot*>::iterator it = temporarySlots.begin(); it != temporarySlots.end(); it++)
                        static_cast<Slot*>(*it)->Invoke(arg1, arg2);
                }

                void Connect(typename GlobalFunctionSlot::Function function)
                {
                    slots.push_back(new GlobalFunctionSlot(this, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                void Disconnect(typename GlobalFunctionSlot::Function function)
                {
                    SignalBase::Disconnect(nullptr, function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance)
                {
                    SignalBase::DisconnectAll(Strip(instance), nullptr, 0);
                }
        };

        template <typename Arg1>
        class Signal<Arg1, void, void, void, void> : public SignalBase
        {
            private:
                class Slot : public SignalBase::Slot
                {
                    public:
                        Slot(SignalBase* signal)
                            : SignalBase::Slot(signal)
                        {
                        }

                        virtual void Invoke(Arg1 arg1) = 0;
                };

                class GlobalFunctionSlot : public Slot
                {
                    public:
                        typedef void (*Function)(Arg1);

                    public:
                        GlobalFunctionSlot(SignalBase* signal, Function function)
                            : Slot(signal),
                              function(function)
                        {
                        }

                        virtual void Invoke(Arg1 arg1)
                        {
                            (*function)(arg1);
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareGlobalFunctionTemplate(this->function, instance, function, functionSize);
                        }

                    private:
                        Function function;
                };

                template <typename ClassType, typename InstanceType>
                class MemberFunctionSlot : public Slot
                {
                    public:
                        typedef void (ClassType::*Function)(Arg1);
                        typedef void (ClassType::*ConstFunction)(Arg1) const;

                    public:
                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, Function function)
                            : Slot(signal),
                              instance(instance),
                              function(function)
                        {
                        }

                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, ConstFunction function)
                            : Slot(signal),
                              instance(instance),
                              function(reinterpret_cast<Function>(function))
                        {
                        }

                        virtual void Invoke(Arg1 arg1)
                        {
                            if (ClassType* c = Strip(instance))
                                (c->*function)(arg1);
                            else
                                Disconnect();
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareMemberFunctionTemplate(Strip(this->instance), &this->function, sizeof(this->function), instance, function, functionSize);
                        }

                    private:
                        InstanceType instance;
                        Function function;
                };

            public:
                void Emit(Arg1 arg1)
                {
                    std::vector<SignalBase::Slot*> temporarySlots = slots;
                    for (std::vector<SignalBase::Slot*>::iterator it = temporarySlots.begin(); it != temporarySlots.end(); it++)
                        static_cast<Slot*>(*it)->Invoke(arg1);
                }

                void Connect(typename GlobalFunctionSlot::Function function)
                {
                    slots.push_back(new GlobalFunctionSlot(this, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                void Disconnect(typename GlobalFunctionSlot::Function function)
                {
                    SignalBase::Disconnect(nullptr, function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance)
                {
                    SignalBase::DisconnectAll(Strip(instance), nullptr, 0);
                }
        };

        template <> 
        class Signal<void, void, void, void, void> : public SignalBase
        {
            private:
                class Slot : public SignalBase::Slot
                {
                    public:
                        Slot(SignalBase* signal)
                            : SignalBase::Slot(signal)
                        {
                        }

                        virtual void Invoke() = 0;
                };

                class GlobalFunctionSlot : public Slot
                {
                    public:
                        typedef void (*Function)();

                    public:
                        GlobalFunctionSlot(SignalBase* signal, Function function)
                            : Slot(signal),
                              function(function)
                        {
                        }

                        virtual void Invoke()
                        {
                            (*function)();
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareGlobalFunctionTemplate(this->function, instance, function, functionSize);
                        }

                    private:
                        Function function;
                };

                template <typename ClassType, typename InstanceType>
                class MemberFunctionSlot : public Slot
                {
                    public:
                        typedef void (ClassType::*Function)();
                        typedef void (ClassType::*ConstFunction)() const;

                    public:
                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, Function function)
                            : Slot(signal),
                              instance(instance),
                              function(function)
                        {
                        }

                        MemberFunctionSlot(SignalBase* signal, InstanceType instance, ConstFunction function)
                            : Slot(signal),
                              instance(instance),
                              function(reinterpret_cast<Function>(function))
                        {
                        }

                        virtual void Invoke()
                        {
                            if (ClassType* c = Strip(instance))
                                (c->*function)();
                            else
                                Disconnect();
                        }

                        virtual bool Compare(const void* instance, const void* function, int functionSize)
                        {
                            return CompareMemberFunctionTemplate(Strip(this->instance), &this->function, sizeof(this->function), instance, function, functionSize);
                        }

                    private:
                        InstanceType instance;
                        Function function;
                };

            public:
                void Emit()
                {
                    std::vector<SignalBase::Slot*> temporarySlots = slots;
                    for (std::vector<SignalBase::Slot*>::iterator it = temporarySlots.begin(); it != temporarySlots.end(); it++)
                        static_cast<Slot*>(*it)->Invoke();
                }

                void Connect(GlobalFunctionSlot::Function function)
                {
                    slots.push_back(new GlobalFunctionSlot(this, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                template <typename I>
                void Connect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    slots.push_back(new MemberFunctionSlot<typename Extract<I>::Result, I>(this, instance, function));
                }

                void Disconnect(GlobalFunctionSlot::Function function)
                {
                    SignalBase::Disconnect(nullptr, function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::Function function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance, typename MemberFunctionSlot<typename Extract<I>::Result, I>::ConstFunction function)
                {
                    SignalBase::Disconnect(Strip(instance), &function, sizeof(function));
                }

                template <typename I>
                void Disconnect(I instance)
                {
                    SignalBase::DisconnectAll(Strip(instance), nullptr, 0);
                }
        };
    }

#   include <Bibim/Signal.inl>

#endif