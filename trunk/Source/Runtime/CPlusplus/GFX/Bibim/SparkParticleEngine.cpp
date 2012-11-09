#include <Bibim/PCH.h>
#include <Bibim/SparkParticleEngine.h>
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
        if (SPKFactory::getInstance().getNbObjects() > 0)
        {
            SPKFactory::getInstance().traceAll();
            SPKFactory::getInstance().destroyAll();
        }

        SPKFactory::getInstance().destroyInstance();
    }
}