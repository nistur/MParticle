#include "MParticlePlugin.h"

#include "ParticleSystem.h"
#include "ParticleEmitter.h"

#include <MEngine.h>
#include <MBehaviorManager.h>

MPLUGIN_START_IMPLEMENT(MParticle)
{
    // get engine
    MEngine * engine = MEngine::getInstance();
    
    // add behaviors
    MBehaviorManager * behaviorManager = engine->getBehaviorManager();
    behaviorManager->addBehavior(ParticleEmitter::getStaticName(), M_OBJECT3D, ParticleEmitter::getNew);
    
    GetParticleSystem()->Init();
}

MPLUGIN_END_IMPLEMENT(MParticle)
{
}
