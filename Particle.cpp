#include "Particle.h"

#include "ParticleEmitter.h"

void Particle::Reset()
{
	m_Pos = 0;
	m_Emitter = 0;
	m_ID = 0;
	m_Life = 0;
}

void Particle::Die()
{
	if(m_Emitter != 0)
		m_Emitter->NotifyParticleDeath(m_ID);
}