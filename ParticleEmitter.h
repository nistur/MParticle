#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include <MEngine.h>
#include <MBehavior.h>

#include "ParticleLib/pAPI.h"

class ParticleEmitter : public MBehavior
{
public:
	ParticleEmitter(MObject3d * parentObject);
	ParticleEmitter(ParticleEmitter & behavior, MObject3d * parentObject);
	~ParticleEmitter(void);

	void destroy(void);

	static MBehavior * getNew(MObject3d * parentObject);
	MBehavior * getCopy(MObject3d * parentObject);

	static const char * getStaticName(void){ return "ParticleEmitter"; }
	const char * getName(void){ return getStaticName(); }

	unsigned int getVariablesNumber(void);
	MVariable getVariable(unsigned int id);

	void update(void);
	void draw();
	void runEvent(int param){}

private:
	void Init();


	PAPI::ParticleContext_t m_Context;
};

#endif /* __PARTICLE_EMITTER_H__*/