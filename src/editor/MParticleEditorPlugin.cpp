#include "MParticleEditorPlugin.h"
#include "MParticleEditor_npk.h"

MINGED_PLUGIN_START_IMPLEMENT(MParticleEditor)
{
    MEngine::getInstance()->loadPlugin("MParticle");
}

MINGED_PLUGIN_END_IMPLEMENT(MParticleEditor)
{
}
