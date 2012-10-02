#include "MParticlePlugin.h"

#include "ParticleSystem.h"
#include "ParticleEmitter.h"

#include <MEngine.h>
#include <MBehaviorManager.h>

#ifdef MEMBED_AVAILABLE
# include <MEmbedFile.h>
# include "MParticle_npk.h"
#endif/*MEMBED_AVAILABLE*/


MPLUGIN_START_IMPLEMENT(MParticle)
{
    // get engine
    MEngine * engine = MEngine::getInstance();
    
    // add behaviors
    MBehaviorManager * behaviorManager = engine->getBehaviorManager();
    behaviorManager->addBehavior(ParticleEmitter::getStaticName(), M_OBJECT3D, ParticleEmitter::getNew);
    
    GetParticleSystem()->Init();


#ifdef MEMBED_AVAILABLE
    if(engine->getEmbedFileManager())
	engine->getEmbedFileManager()->AddEmbeddedFile("MParticle.npk", 
						       MParticle_npk, 
						       MParticle_npkSize());
#endif/*MEMBED_AVAILABLE*/
    // try to load the package anyway,
    // who knows, we might find it
    if(engine->getPackageManager())
	engine->getPackageManager()->loadPackage("MParticle.npk");
}

MPLUGIN_END_IMPLEMENT(MParticle)
{
}
