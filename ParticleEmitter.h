#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include <MEngine.h>
#include <MBehavior.h>

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
	void runEvent(int param){}
};

#endif /* __PARTICLE_EMITTER_H__*/