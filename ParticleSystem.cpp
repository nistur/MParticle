#include "ParticleSystem.h"

#include <MEngine.h>
#include "Particle.h"

ParticleSystem* ParticleSystem::GetInstance()
{
	static ParticleSystem instance;
	return &instance;
}

void ParticleSystem::Init(int maxParticles)
{
	if(m_Pool)
	{
		delete [] m_Pool;
		m_Pool = 0;
	}
	

	m_Pool = new Particle[maxParticles];
	m_MaxParticles = maxParticles;
	for(int i = 0; i < maxParticles; ++i)
		m_FreeParticles.push_back(&m_Pool[i]);
}

void ParticleSystem::Update()
{
	
	MEngine* engine = MEngine::getInstance();
	MSystemContext* system = engine->getSystemContext();
	int tick = system->getSystemTick();

	if((m_PrevTick == 0) || (m_PrevTick == tick))
	{
		m_PrevTick = tick;
		return;
	}

	int dt = tick - m_PrevTick;
	m_PrevTick = tick;

	for(int i = 0; i < m_MaxParticles; ++i)
	{
		MoveParticle(&m_Pool[i], dt);
		UpdateLife(&m_Pool[i], dt);
		UpdateVelocity(&m_Pool[i], dt);
	}
}

void ParticleSystem::MoveParticle(Particle* particle, int dt)
{
	if(particle && particle->IsAlive())
	{
		float dtS = (float)dt / 1000.0f;
		*particle->m_Pos += (particle->m_Velocity * dtS);
	}
}

void ParticleSystem::UpdateLife(Particle* particle, int dt)
{
	if(particle && particle->IsAlive())
	{
		particle->m_Life = max(0, particle->m_Life - dt);
		if(!particle->IsAlive())
		{
			particle->Die();
			m_FreeParticles.push_back(particle);
		}
	}
}

void ParticleSystem::UpdateVelocity(Particle* particle, int dt)
{
	if(particle && particle->IsAlive())
	{
		float dtS = (float)dt / 1000.0f;
		static MVector3 gravity(0.0f, 0.0f, -0.98f);
		if(particle->m_Gravity)
		{
			particle->m_Velocity += (gravity * dtS);
		}

		particle->m_Velocity += (particle->m_Acceleration * dtS);
	}
}

Particle* ParticleSystem::GetNewParticle()
{
	if(m_FreeParticles.empty())
		return 0;
	Particle* rtn = m_FreeParticles.back();
	m_FreeParticles.pop_back();
	rtn->Reset();
	return rtn;
}

ParticleSystem::ParticleSystem()
: m_Pool(0)
, m_PrevTick(0)
{
}

ParticleSystem::ParticleSystem(const ParticleSystem& ps)
: m_Pool(0)
, m_PrevTick(0)
{
}

ParticleSystem::~ParticleSystem()
{
	if(m_Pool)
	{
		delete [] m_Pool;
		m_Pool = 0;
	}
}