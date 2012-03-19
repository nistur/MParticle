#include "ParticleEmitter.h"

using namespace PAPI;

ParticleEmitter::ParticleEmitter(MObject3d * parentObject):
MBehavior(parentObject)
{
	Init();
}

ParticleEmitter::ParticleEmitter(ParticleEmitter & behavior, MObject3d * parentObject):
MBehavior(parentObject)
{
	Init();
}

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
	MEngine* engine = MEngine::getInstance();

	MGame* game = engine->getGame();

	if(game->isRunning())
	{
		// Set up the state.
		m_Context.Velocity(PDCylinder(pVec(0.0f, -0.01f, 0.25f), pVec(0.0f, -0.01f, 0.27f), 0.021f, 0.019f));
		m_Context.Color(PDLine(pVec(0.8f, 0.9f, 1.0f), pVec(1.0f, 1.0f, 1.0f)));

		// Generate particles along a very small line in the nozzle.
		m_Context.Source(100, PDLine(pVec(0, 0, 0), pVec(0, 0, 0.4f)));

		// Gravity.
		m_Context.Gravity(pVec(0, 0, -0.01f));

		// Bounce particles off a disc of radius 5.
		m_Context.Bounce(-0.05f, 0.35f, 0, PDDisc(pVec(0, 0, 0), pVec(0, 0, 1), 5));

		// Kill particles below Z=-3.
		m_Context.Sink(false, PDPlane(pVec(0,0,-3), pVec(0,0,1)));

		// Move particles to their new positions.
		m_Context.Move(true, false);
	}
}

void ParticleEmitter::draw()
{
	MEngine* engine = MEngine::getInstance();
	MGame* game = engine->getGame();
	MRenderingContext* render = engine->getRenderingContext();

	if(game->isRunning())
	{
		size_t cnt = m_Context.GetGroupCount();
		if(cnt < 1) return;

		float *ptr;
		size_t flstride, pos3Ofs, posB3Ofs, size3Ofs, vel3Ofs, velB3Ofs, color3Ofs, alpha1Ofs, age1Ofs, up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs;

		cnt = m_Context.GetParticlePointer(ptr, flstride, pos3Ofs, posB3Ofs,
			size3Ofs, vel3Ofs, velB3Ofs, color3Ofs, alpha1Ofs, age1Ofs,
			up3Ofs, rvel3Ofs, upB3Ofs, mass1Ofs, data1Ofs);
		if(cnt < 1) return;
		
		render->enableColorArray();
		render->setColorPointer(M_FLOAT, int(flstride) * sizeof(float), ptr + color3Ofs);
		
		render->enableVertexArray();
		render->setVertexPointer(M_FLOAT, int(flstride) * sizeof(float), ptr + pos3Ofs);
		
		render->drawArray(M_PRIMITIVE_POINTS, 0, cnt);
		render->disableVertexArray();
		render->disableColorArray();
	}
}

void ParticleEmitter::Init()
{
	int handle = m_Context.GenParticleGroups(1, 10000);

	m_Context.CurrentGroup(handle);
}

