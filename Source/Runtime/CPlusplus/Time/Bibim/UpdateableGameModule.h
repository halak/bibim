#pragma once
#ifndef __BIBIM_UPDATEABLEGAMECOMPONENT_H__
#define __BIBIM_UPDATEABLEGAMECOMPONENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>

    namespace Bibim
    {
        class UpdateableGameModule : public GameModule
        {
            BBAbstractObjectClass(UpdateableGameModule, GameModule);
            public:
                UpdateableGameModule();
                virtual ~UpdateableGameModule();

                virtual void Update(float dt, uint timestamp) = 0;

            protected:
                inline bool Seal(uint timestamp);

            private:
                uint lastTimestamp;
        };
    }

#    include <Bibim/UpdateableGameModule.inl>

#endif