#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(MObject3d * parentObject):
MBehavior(parentObject)
{}

ParticleEmitter::ParticleEmitter(ParticleEmitter & behavior, MObject3d * parentObject):
MBehavior(parentObject)
{}

ParticleEmitter::~ParticleEmitter(void)
{}

void ParticleEmitter::destroy(void) { delete this; }

MBehavior * ParticleEmitter::getNew(MObject3d * parentObject)
{
	return new ParticleEmitter(parentObject);
}

MBehavior * ParticleEmitter::getCopy(MObject3d * parentObject)
{
	return new ParticleEmitter(*this, parentObject);
}

unsigned int ParticleEmitter::getVariablesNumber(void){
	return 0;
}

MVariable ParticleEmitter::getVariable(unsigned int id)
{
	switch(id)
	{
	default:
		return MVariable("NULL", NULL, M_VARIABLE_NULL);
		break;
	}
}

void ParticleEmitter::update(void)
{
}

