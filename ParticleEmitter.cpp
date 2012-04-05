#include "ParticleEmitter.h"

#include "Particle.h"
#include "ParticleSystem.h"

#include <algorithm>

ParticleEmitter::ParticleEmitter(MObject3d * parentObject)
: MBehavior(parentObject)
, m_Count(1000)
, m_EmitPeriod(50)
, m_Positions(0)
, m_PrevEmitTime(0)
, m_Age(0)
, m_PrevTickTime(0)
, m_MinLife(0)
, m_MaxLife(100)
{
	Init();
}

ParticleEmitter::ParticleEmitter(ParticleEmitter & behavior, MObject3d * parentObject)
: MBehavior(parentObject)
, m_Count(1000)
, m_EmitPeriod(50)
, m_Positions(0)
, m_PrevEmitTime(0)
, m_Age(0)
, m_PrevTickTime(0)
, m_MinLife(0)
, m_MaxLife(100)
{
	Init();
}

ParticleEmitter::~ParticleEmitter(void)
{
	Cleanup();
}

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
	return 4;
}

MVariable ParticleEmitter::getVariable(unsigned int id)
{
	switch(id)
	{
	case 0:
		return MVariable("MaxCount", &m_Count, M_VARIABLE_INT);
		break;
	case 1:
		return MVariable("EmitPeriod", &m_EmitPeriod, M_VARIABLE_INT);
		break;
	case 2:
		return MVariable("MinLife", &m_MinLife, M_VARIABLE_INT);
		break;
	case 3:
		return MVariable("MaxLife", &m_MaxLife, M_VARIABLE_INT);
		break;
	default:
		return MVariable("NULL", NULL, M_VARIABLE_NULL);
		break;
	}
}

void ParticleEmitter::update(void)
{
	MEngine* engine = MEngine::getInstance();

	MGame* game = engine->getGame();

	GetParticleSystem()->Update();

	if(game->isRunning())
	{
		CheckToSpawnParticles();
	}
}

void ParticleEmitter::draw()
{
	MEngine* engine = MEngine::getInstance();
	MRenderingContext* render = engine->getRenderingContext();

	render->enableVertexArray();
	render->setVertexPointer(M_FLOAT, 3, m_Positions);

	render->enableColorArray();
	render->setColorPointer(M_BYTE, 4, m_Colours);

	render->drawArray(M_PRIMITIVE_POINTS, 0, m_Count);

}

void ParticleEmitter::NotifyParticleDeath(int id)
{
	m_FreeParticles.push_back(id);
	m_Positions[id] = Vec3(0,0,0);
	m_Colours[id].a = 0;
}

void ParticleEmitter::RemoveRef(EmitterRef* ref)
{
	vector<EmitterRef*>::iterator it = std::find(m_Refs.begin(), m_Refs.end(), ref);

	if(it != m_Refs.end())
	{
		m_Refs.erase(it);
	}
}

void ParticleEmitter::Init()
{
	// this is currently only called when the editor
	// creates the object, which means you can't
	// edit and then run the game to check it.
	// you have to run the game twice for the changes to
	// take effect. Meh.
	if(m_Positions == 0)
	{
		m_Positions = new Vec3[m_Count];
		m_Colours = new MColor[m_Count];

		// push the IDs in backwards
		for(int i = 0; i < m_Count; ++i)
		{
			m_FreeParticles.push_back(m_Count - i - 1);
			m_Colours[i].set(128, 128, 128, 0);
		}
	}

}

void ParticleEmitter::Cleanup()
{
	if(m_Positions != 0)
	{
		delete [] m_Positions;
		m_Positions = 0;
	}

	if(m_Colours != 0)
	{
		delete [] m_Colours;
		m_Colours = 0;
	}
		
	m_FreeParticles.clear();

	for(unsigned int i = 0; i < m_Refs.size(); ++i)
		m_Refs[i]->Clear();
	m_Refs.clear();
}

void ParticleEmitter::CheckToSpawnParticles()
{
	MEngine* engine = MEngine::getInstance();
	MSystemContext* system = engine->getSystemContext();

	int tick = system->getSystemTick();

	if(m_PrevEmitTime == 0)
	{
		m_PrevEmitTime = tick;
		m_PrevTickTime = tick;
	}

	m_Age += tick - m_PrevTickTime;

	while((m_PrevEmitTime + m_EmitPeriod < tick) &&
		(m_FreeParticles.size() > 0))
	{
		m_PrevEmitTime += m_EmitPeriod;
		EmitParticle();
	}

}

void ParticleEmitter::EmitParticle()
{
	ParticleSystem* world = GetParticleSystem();

	if(Particle* newParticle = world->GetNewParticle())
	{
		int ID = m_FreeParticles.back();
		m_Colours[ID].a = 128;
		newParticle->SetPosition(&m_Positions[ID]);
		newParticle->SetEmitter(this);
		newParticle->SetLife(m_MinLife + (rand() % (m_MaxLife - m_MinLife)));
		newParticle->SetVelocity(Vec3(0, 0, 1.0f));
		m_FreeParticles.pop_back();
	}
}