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
	if(MPhysicsContext* physics = engine->getPhysicsContext())
		m_Gravity = physics->getWorldGravity();

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

	for(int i = 0; i < m_MaxParticles; ++i)
	{
		UpdateParticleCollision(&m_Pool[i], dt);
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
		if(particle->m_Gravity)
		{
			particle->m_Velocity += (m_Gravity * dtS);
		}

		particle->m_Velocity += (particle->m_Acceleration * dtS);
	}
}

void ParticleSystem::UpdateParticleCollision(Particle* particle, int dt)
{
	if(particle && particle->IsPhysDisabled())
	{
		particle->m_DisableTime -= dt;
	}
	else if(particle && particle->IsAlive() && particle->m_Influence > 0.0f)
	{
		int i = 0;
		while(&m_Pool[i] != particle) ++i;
		++i;
		for(i; i < m_MaxParticles; ++i)
		{
			if(&m_Pool[i] != particle)
			{
				CollideParticles(particle, &m_Pool[i], dt);
			}
		}
	}
}

void ParticleSystem::CollideParticles(Particle* particle1, Particle* particle2, int dt)
{
	if( particle1 && particle2 && 
		particle1->IsAlive() && particle2->IsAlive() &&
		particle1->m_Influence > 0.0f && particle2->m_Influence > 0.0f &&
		particle1->m_Mass > 0.0f && particle2->m_Mass > 0.0f )
	{
		// get distance between 2 particles
		MVector3* pos1 = particle1->m_Pos;
		MVector3* pos2 = particle2->m_Pos;
		MVector3 dir = *pos1 - *pos2;
		float distsqu = dir.getSquaredLength();
		float sizes = (particle1->m_Size / 2.0f) + (particle2->m_Size / 2.0f);
		sizes *= sizes;
		if(distsqu <= sizes)
		{
			// billiard ball, perfectly elastic
			float CoR = 1.0f;
			float m1 = particle1->m_Mass;
			float m2 = particle2->m_Mass;
			MVector3 u1 = particle1->m_Velocity;
			MVector3 u2 = particle2->m_Velocity;

			//m1u1 + m2u2 = m1v1 + m2v2
			//C = (v2 - v1) / (u1 - u2)
			//
			//trying to find v1 and v2
			//C(u1 - u2) = (v2 - v1)
			//Cu1 - Cu2 + v1 = v2
			//
			//m1u1 + m2u2 = m1v1 + m2(Cu1 - Cu2 + v1)
			//m1u1 + m2u2 = m1v1 + m2Cu1 - m2Cu2 + m2v1
			//m1u1 + m2u2 - m2Cu1 + m2Cu2 = m1v1 + m2v1
			//m1u1 + m2(u2 - Cu1 + Cu2) = v1(m1 + m2)
			//(m1u1 + m2(u2 + C(u2 - u1))) / (m1 + m2) = v1

			MVector3 v1 = ((m1*u1) + ((((u2 - u1) * CoR) + u2) * m2)) / (m1 + m2);
			MVector3 v2 = (CoR*(u1-u2)) + v1;
			particle1->SetVelocity(v1);
			particle2->SetVelocity(v2);
		}
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