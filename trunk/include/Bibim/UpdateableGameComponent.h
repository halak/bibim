#pragma once
#ifndef __BIBIM_UPDATEABLEGAMECOMPONENT_H__
#define __BIBIM_UPDATEABLEGAMECOMPONENT_H__

#include <Bibim/FWD.h>
#include <Bibim/GameComponent.h>
#include <Bibim/IUpdateable.h>

namespace Bibim
{
    class UpdateableGameComponent : public GameComponent, public IUpdateable
    {
        BBAbstractComponentClass(UpdateableGameComponent, GameComponent);
        public:
            UpdateableGameComponent();
            virtual ~UpdateableGameComponent();

        protected:
            inline bool Seal(int timestamp);

        private:
            int lastTimestamp;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool UpdateableGameComponent::Seal(int timestamp)
    {
        if (lastTimestamp != timestamp)
        {
            lastTimestamp = timestamp;
            return false;
        }
        else
            return true;
    }
}

#endif