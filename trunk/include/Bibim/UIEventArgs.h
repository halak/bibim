#pragma once
#ifndef __BIBIM_UIEVENTARGS_H__
#define __BIBIM_UIEVENTARGS_H__

#include <Bibim/FWD.h>
#include <Bibim/SharedObject.h>

namespace Bibim
{
    class UIEventArgs : public SharedObject
    {
        public:
            class Serializer
            {
                public:
                    virtual ~Serializer() { }

                    virtual void Push(GameComponent* value) = 0;
                    virtual void Push(bool value) = 0;
                    virtual void Push(int value) = 0;
                    virtual void Push(float value) = 0;
                    virtual void Push(const char* value) = 0;
            };

        public:
            UIEventArgs();
            explicit UIEventArgs(UIVisual* target);
            UIEventArgs(const UIEventArgs& original);
            virtual ~UIEventArgs();

            virtual UIEventArgs* Clone() const;

            virtual void Serialize(Serializer& context) const;

            inline UIVisual* GetTarget() const;

        private:
            UIVisualPtr target;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIVisual* UIEventArgs::GetTarget() const
    {
        return target;
    }
}

#endif
