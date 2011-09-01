#pragma once
#ifndef __BIBIM_PROPERTY_H__
#define __BIBIM_PROPERTY_H__

    namespace Bibim
    {
        /// non-virtual 소멸자는 의도하였습니다.
        /// PropertyBase에서 소멸자를 호출하지 않도록 합니다.
        class PropertyBase
        {
            public:
                inline ~PropertyBase();

            protected:
                inline PropertyBase(uint32 id);

                inline uint32 GetID() const;

            private:
                uint32 id;
        };

        template <typename T> class Property : public PropertyBase
        {
            public:
                template <typename C, typename G> Property(uint32 id, G (C::*getter)())
                    : PropertyBase(id),
                      getterAndSetter(new GetterAndSetterTemplate<C, G, S>(getter))
                {
                }

                template <typename C, typename G> Property(uint32 id, G (C::*getter)() const)
                    : PropertyBase(id),
                      getterAndSetter(new GetterAndSetterTemplate<C, G, S>(getter))
                {
                }

                template <typename C, typename G, typename S> Property(uint32 id, G (C::*getter)(), void (C::*setter)(S))
                    : PropertyBase(id),
                      getterAndSetter(new GetterAndSetterTemplate<C, G, S>(getter, setter))
                {
                }

                template <typename C, typename G, typename S> Property(uint32 id, G (C::*getter)() const, void (C::*setter)(S))
                    : PropertyBase(id),
                      getterAndSetter(new GetterAndSetterTemplate<C, G, S>(getter, setter))
                {
                }

                inline ~Property();

                inline T    GetValue(void* instance) const;
                inline void SetValue(void* instance, T value) const;

            private:
                struct GetterAndSetter
                {
                    virtual ~GetterAndSetter() { }
                    virtual T GetValue(void* instance) const = 0;
                    virtual void SetValue(void* instance, T value) const = 0;
                };

                template <typename C, typename G, typename S> struct GetterAndSetterTemplate : GetterAndSetter
                {
                    G    (C::*Getter)();
                    void (C::*Setter)(S); 

                    GetterAndSetterTemplate(G (C::*getter)())
                        : Getter(getter),
                          Setter(nullptr)
                    {
                    }

                    GetterAndSetterTemplate(G (C::*getter)() const)
                        : Getter(reinterpret_cast<G (C::*)()>(getter)),
                          Setter(nullptr)
                    {
                    }

                    GetterAndSetterTemplate(G (C::*getter)(), void (C::*setter)(S))
                        : Getter(getter),
                          Setter(setter)
                    {
                    }

                    GetterAndSetterTemplate(G (C::*getter)() const, void (C::*setter)(S))
                        : Getter(reinterpret_cast<G (C::*)()>(getter)),
                          Setter(setter)
                    {
                    }

                    virtual ~GetterAndSetterTemplate()
                    {
                    }

                    virtual T GetValue(void* instance) const
                    {
                        return (static_cast<C*>(instance)->*Getter)();
                    }

                    virtual void SetValue(void* instance, T value) const
                    {
                        (static_cast<C*>(instance)->*Setter)(value);
                    }
                };

            private:
                GetterAndSetter* getterAndSetter;
        };
    }

#   include <Bibim/Property.inl>

#endif