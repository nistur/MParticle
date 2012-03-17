#pragma once
#ifndef __PARTICLE_PLUGIN_H__
#define __PARTICLE_PLUGIN_H__

#ifdef WIN32
	#include <windows.h>
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

	DLLEXPORT void StartPlugin();
	DLLEXPORT void EndPlugin();
	
#ifdef __cplusplus
}
#endif

#endif /*__PARTICLE_PLUGIN_H__*/