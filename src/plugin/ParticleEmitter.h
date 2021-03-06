#ifndef __PARTICLE_EMITTER_H__
#define __PARTICLE_EMITTER_H__

#include <MEngine.h>
#include <MBehavior.h>
#include <MTextureRef.h>

#include <vector>

using std::vector;

class EmitterRef;

class ParticleEmitter : public MBehavior
{
public:
	ParticleEmitter(MObject3d * parentObject);
	ParticleEmitter(ParticleEmitter & behavior, MObject3d * parentObject);
	~ParticleEmitter(void);

	void destroy(void);

	static MBehavior * getNew(MObject3d * parentObject);
	MBehavior * getCopy(MObject3d * parentObject);

	static const char * getStaticName(void){ return "ParticleEmitter"; }
	const char * getName(void){ return getStaticName(); }

	unsigned int getVariablesNumber(void);
	MVariable getVariable(unsigned int id);

	void update(void);
	void draw();
	void runEvent(int param){}

	void NotifyParticleDeath(int id);

	void AddRef(EmitterRef* ref) { m_Refs.push_back(ref); }
	void RemoveRef(EmitterRef* ref);

private:
	void Init();
	void Cleanup();

	void CheckToSpawnParticles();

	void EmitParticle();

	//----------------------------------------
	// Exposed values
	//----------------------------------------
	int			m_Count;
	int			m_EmitPeriod;
	int			m_MinLife;
	int			m_MaxLife;
	MVector3	m_EmitDir;
	MVector3	m_Acceleration;
	bool		m_HasGravity;
	float		m_Angle;
	float		m_Force;
	MTextureRef*    m_Texture;
	bool            m_PointSprite;
	float			m_EmmitSize;
	float			m_Influence;
	float			m_Mass;
	int				m_PhysDisableTime;
	bool			m_PointEmitter;
	MVector3		m_EmitterSize;

	//----------------------------------------
	// Runtime members
	//----------------------------------------
	MVector3*	m_Positions;
	MColor*		m_Colours;
	vector<int>	m_FreeParticles;

	int			m_PrevEmitTime;
	int			m_PrevTickTime;
	int			m_Age;

	vector<EmitterRef*> m_Refs;
};

// make a semi-smart reference count thingy
class EmitterRef
{
public:
	EmitterRef() : m_Emitter(0) {}
	EmitterRef(ParticleEmitter* emitter) : m_Emitter(emitter) { m_Emitter->AddRef(this); }
	~EmitterRef() { if(m_Emitter) m_Emitter->RemoveRef(this); }

	ParticleEmitter& operator*() { return *m_Emitter; }
	ParticleEmitter* operator->() { return m_Emitter; }
	EmitterRef& operator=(ParticleEmitter* rhs)
	{
		if(m_Emitter)
			m_Emitter->RemoveRef(this);
		m_Emitter = rhs;
		if(m_Emitter)
			m_Emitter->AddRef(this); 
		return *this; 
	}
	bool operator==(ParticleEmitter* rhs) { return m_Emitter == rhs; }
	bool operator!=(ParticleEmitter* rhs) { return m_Emitter != rhs; }

	void Clear() { m_Emitter = 0; }

private:
	ParticleEmitter* m_Emitter;
};

#endif /* __PARTICLE_EMITTER_H__*/
