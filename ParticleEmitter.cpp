#include "ParticleEmitter.h"

#include "Particle.h"
#include "ParticleSystem.h"

#include <MMaths.h>

#include <algorithm>

ParticleEmitter::ParticleEmitter(MObject3d * parentObject)
: MBehavior(parentObject)
, m_Count(1000)
, m_EmitPeriod(50)
, m_Positions(0)
, m_Colours(0)
, m_PrevEmitTime(0)
, m_Age(0)
, m_PrevTickTime(0)
, m_MinLife(1000)
, m_MaxLife(5000)
, m_EmitDir(0.0f, 0.0f, 1.0f)
, m_Acceleration(0.0f, 0.0f, 0.0f)
, m_HasGravity(false)
, m_Angle(0.0f)
, m_Force(1.0f)
, m_Texture(0)
, m_PointSprite(false)
, m_EmmitSize(50.0f)
{
	Init();
}

ParticleEmitter::ParticleEmitter(ParticleEmitter & behavior, MObject3d * parentObject)
: MBehavior(parentObject)
, m_Count(1000)
, m_EmitPeriod(50)
, m_Positions(0)
, m_Colours(0)
, m_PrevEmitTime(0)
, m_Age(0)
, m_PrevTickTime(0)
, m_MinLife(0)
, m_MaxLife(100)
, m_EmitDir(0.0f, 0.0f, 1.0f)
, m_Acceleration(0.0f, 0.0f, 0.0f)
, m_HasGravity(false)
, m_Angle(0.0f)
, m_Force(1.0f)
, m_Texture(0)
, m_PointSprite(false)
, m_EmmitSize(50.0f)
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
	return 12;
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
	case 4:
		return MVariable("Direction", &m_EmitDir, M_VARIABLE_VEC3);
		break;
	case 5:
		return MVariable("Gravity", &m_HasGravity, M_VARIABLE_BOOL);
		break;
	case 6:
		return MVariable("Acceleration", &m_Acceleration, M_VARIABLE_VEC3);
		break;
	case 7:
		return MVariable("Spread", &m_Angle, M_VARIABLE_FLOAT);
		break;
	case 8:
		return MVariable("Force", &m_Force, M_VARIABLE_FLOAT);
		break;
	case 9:
	    return MVariable("Texture", &m_Texture, M_VARIABLE_TEXTURE_REF);
	    break;
	case 10:
	    return MVariable("PointSprite", &m_PointSprite, M_VARIABLE_BOOL);
	    break;
	case 11:
	    return MVariable("EmitSize", &m_EmmitSize, M_VARIABLE_FLOAT);
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

	render->setDepthMask(false);
	if(m_Texture && m_Texture->getTextureId() > 0)
	{
	    render->enableTexture();
		render->setBlendingMode(M_BLENDING_ADD);
		render->enableBlending();

	    m_Texture->update();
	}

	render->setPointSize(5.0f, m_EmmitSize, 60.0f);

	render->enableVertexArray();
	render->setVertexPointer(M_FLOAT, 3, m_Positions);

	//render->enableColorArray();
	//render->setColorPointer(M_BYTE, 4, m_Colours);

	render->drawArray(M_PRIMITIVE_POINTS, 0, m_Count);
	render->setDepthMask(true);

}

void ParticleEmitter::NotifyParticleDeath(int id)
{
	m_FreeParticles.push_back(id);
	m_Positions[id] = MVector3(0,0,0);
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
	    m_Positions = new MVector3[m_Count];
	if(m_Colours == 0)
	    m_Colours = new MColor[m_Count];

	m_FreeParticles.clear();
	// push the IDs in backwards
	for(int i = 0; i < m_Count; ++i)
	{
	    m_FreeParticles.push_back(m_Count - i - 1);
	    m_Colours[i].set(255, 255, 255, 0);
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
		m_Colours[ID].a = 255;
		newParticle->SetID(ID);
		if(MObject3d* obj = getParentObject())
		    m_Positions[ID] = obj->getPosition();
		newParticle->SetPosition(&m_Positions[ID]);
		newParticle->SetEmitter(this);
		newParticle->SetLife(m_MinLife + (rand() % (m_MaxLife - m_MinLife)));

		// pick a random axis, let's say X
		MVector3 axis(1.0f, 0.0f, 0.0f);
		// just check we're not going to use X itself
		if(m_EmitDir.x != 0 && m_EmitDir.y == 0 && m_EmitDir.z == 0)
			axis = MVector3(0.0f, 1.0f, 0.0f);

		float angle = m_Angle * (float)rand() / (float)RAND_MAX;
		float spread = 360.0f * (float)rand() / (float)RAND_MAX;

		MMatrix4x4 mat;
		mat.setRotationAxis(spread, m_EmitDir);
		mat.rotate(axis, angle);

		MVector3 dir = mat.getRotatedVector3(m_EmitDir).getNormalized();
		newParticle->SetVelocity(dir * m_Force);
		newParticle->SetAcceleration(m_Acceleration);
		newParticle->SetHasGravity(m_HasGravity);
		m_FreeParticles.pop_back();
	}
}
