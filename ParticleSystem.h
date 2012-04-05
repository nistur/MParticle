#ifndef __PARTICLE_SYSTEM_H__
#define __PARTICLE_SYSTEM_H__

#include <vector>

class Particle;

class ParticleSystem
{
public:
	static ParticleSystem* GetInstance();

	void Init(int maxParticles = 1000);
	void Update();

	Particle* GetNewParticle();

private:
	ParticleSystem();
	ParticleSystem(const ParticleSystem& ps);
	~ParticleSystem();
	
	void MoveParticle(Particle* particle, int dt);
	void UpdateLife(Particle* particle, int dt);

	typedef std::vector<Particle*> particleVec;

	Particle*	m_Pool;
	int			m_MaxParticles;
	particleVec	m_FreeParticles;

	int			m_PrevTick;
};

inline ParticleSystem* GetParticleSystem() { return ParticleSystem::GetInstance(); }

#endif /*__PARTICLE_SYSTEM_H__*/