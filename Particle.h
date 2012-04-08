#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "ParticleEmitter.h"

class Particle
{
public:
	Particle() { Reset(); }
	void Reset();

	void SetEmitter(ParticleEmitter* emitter) { m_Emitter = emitter; }
	void SetID(int id) { m_ID = id; }
	void SetPosition(MVector3* pos){ m_Pos = pos; }
	void SetLife(int life){ m_Life = life; }
	void SetVelocity(const MVector3& vel){ m_Velocity = vel; }
	void SetAcceleration(const MVector3& acc){ m_Acceleration = acc; }
	void SetHasGravity(bool val){ m_Gravity = val; }
	
	bool IsAlive() { return m_Life > 0; }

	void Die();

	friend class ParticleSystem;

private:
	MVector3*			m_Pos;
	MVector3			m_Velocity;
	MVector3			m_Acceleration;

	EmitterRef			m_Emitter;
	int					m_ID;
	int					m_Life;
	bool				m_Gravity;
};

#endif /*__PARTICLE_H__*/