#include "Particle.h"

#include "ParticleEmitter.h"

void Particle::Reset()
{
	m_Pos = 0;
	m_Emitter = 0;
	m_ID = 0;
	m_Life = 0;
	m_Velocity = MVector3(0.0f, 0.0f, 0.0f);
	m_Acceleration = MVector3(0.0f, 0.0f, 0.0f);
}

void Particle::Die()
{
	if(m_Emitter != 0)
		m_Emitter->NotifyParticleDeath(m_ID);
}