#include <Bibim/PCH.h>
#include <Bibim/ParticleSpace.h>
#include <Bibim/ParticleEmitter.h>

namespace Bibim
{
    ParticleSpace::ParticleSpace()
    {
    }

    ParticleSpace::~ParticleSpace()
    {
    }

    void ParticleSpace::Update(float dt, uint timestamp)
    {
        for (EmitterCollection::iterator it = emitters.begin(); it != emitters.end(); it++)
        {
            (*it)->Update(dt, timestamp);
        }
    }
}