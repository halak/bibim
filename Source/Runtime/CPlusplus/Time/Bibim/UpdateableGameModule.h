#pragma once
#ifndef __BIBIM_UPDATEABLEGAMECOMPONENT_H__
#define __BIBIM_UPDATEABLEGAMECOMPONENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>

    namespace Bibim
    {
        class UpdateableGameModule : public GameModule
        {
            BBAbstractModuleClass(UpdateableGameModule, GameModule);
            public:
                UpdateableGameModule();
                virtual ~UpdateableGameModule();

                virtual void Update(float dt, int timestamp) = 0;

            protected:
                inline bool Seal(int timestamp);

            private:
                int lastTimestamp;
        };
    }

#    include <Bibim/UpdateableGameModule.inl>

#endif