#pragma once
#ifndef __BIBIM_SPARKPARTICLEENGINE_H__
#define __BIBIM_SPARKPARTICLEENGINE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   pragma warning(push)
#   pragma warning(disable : 4100)
#   include <SPK.h>
#   pragma warning(pop)

    namespace Bibim
    {
        class SparkParticleEngine : public GameModule
        {
            BBModuleClass(SparkParticleEngine, GameModule, 'S', 'P', 'A', 'K');
            public:
                SparkParticleEngine();
                virtual ~SparkParticleEngine();
        };
    }

#   include <Bibim/SparkParticleEngine.inl>

#endif