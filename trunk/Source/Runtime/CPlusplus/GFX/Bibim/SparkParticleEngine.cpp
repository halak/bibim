#include <Bibim/PCH.h>
#include <Bibim/SparkParticleEngine.h>
#pragma warning(push)
#pragma warning(disable : 4100)
#include <SPK.h>
#pragma warning(pop)
using namespace SPK;

namespace Bibim
{
    SparkParticleEngine::SparkParticleEngine()
    {
        System::setClampStep(true, 0.1f);
        System::useAdaptiveStep(0.001f, 0.01f);
    }

    SparkParticleEngine::~SparkParticleEngine()
    {
        SPKFactory& factory = SPKFactory::getInstance();

        if (factory.getNbObjects() > 0)
        {
            factory.traceAll();
            factory.destroyAll();
        }

        factory.destroyInstance();
    }
}