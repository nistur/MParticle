#pragma once
#ifndef __PARTICLE_PLUGIN_H__
#define __PARTICLE_PLUGIN_H__

#include <MEngine.h>

#ifdef MPLUGIN_AVAILABLE
#    include <MPlugin.h>
#else
#    include "PluginCompatibility.h"
#endif/*MPLUGIN_AVAILABLE*/

MPLUGIN_DECLARE(MParticle);

#endif /*__PARTICLE_PLUGIN_H__*/
