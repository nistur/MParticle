#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Util/Vector.h"

using Util::Vec3;

#include "ParticleEmitter.h"

class Particle
{
public:
	Particle() { Reset(); }
	void Reset();

	void SetEmitter(ParticleEmitter* emitter) { m_Emitter = emitter; }
	void SetID(int id) { m_ID = id; }
	void SetPosition(Vec3* pos){ m_Pos = pos; }
	void SetLife(int life){ m_Life = life; }
	void SetVelocity(const Vec3& vel){ m_Velocity = vel; }
	
	bool IsAlive() { return m_Life > 0; }

	void Die();

	friend class ParticleSystem;

private:
	Vec3*				m_Pos;
	Vec3				m_Velocity;

	EmitterRef			m_Emitter;
	int					m_ID;
	int					m_Life;
};

#endif /*__PARTICLE_H__*/