#include "MParticlePlugin.h"

#include "ParticleEmitter.h"

#include <MEngine.h>
#include <MBehaviorManager.h>

void StartPlugin()
{
	// get engine
	MEngine * engine = MEngine::getInstance();

	// add behaviors
	MBehaviorManager * behaviorManager = engine->getBehaviorManager();
	behaviorManager->addBehavior(ParticleEmitter::getStaticName(), M_OBJECT3D, ParticleEmitter::getNew);
}

void EndPlugin()
{
}
