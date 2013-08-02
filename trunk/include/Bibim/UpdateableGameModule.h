#pragma once
#ifndef __BIBIM_UPDATEABLEGAMEMODULE_H__
#define __BIBIM_UPDATEABLEGAMEMODULE_H__

#include <Bibim/FWD.h>
#include <Bibim/GameModule.h>
#include <Bibim/IUpdateable.h>

namespace Bibim
{
    class UpdateableGameModule : public GameModule, public IUpdateable
    {
        BBAbstractModuleClass(UpdateableGameModule, GameModule);
        public:
            UpdateableGameModule();
            virtual ~UpdateableGameModule();

        protected:
            inline bool Seal(int timestamp);

        private:
            int lastTimestamp;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool UpdateableGameModule::Seal(int timestamp)
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