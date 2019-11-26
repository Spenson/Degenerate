#pragma once
// cParticleEmitter
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>

class cParticle
{
public:
	cParticle();
	glm::vec3 location;
	glm::vec3 velocity;
	float lifeTime;
	glm::vec4 colourRGBA;	// Colour and transparency
	// 
	// glm::vec orientation
	float scale;
	// glm::vec3 acceleration;	// For each particle
};

class cParticleEmitter
{
public:
	cParticleEmitter();
	glm::vec3 acceleration;
	glm::vec3 location;
	void Initialize(glm::vec3 minVelocity, glm::vec3 maxVelocity,
			  glm::vec3 minDeltaPosition, glm::vec3 maxDeltaPosition, 
			  float minLifeSeconds, float maxLifeSeconds,
			  int minParticlesPerFrame, int maxParticlesPerFrame);
	// Called every frame
	void Step(float deltaTime);
	// This will be called when we want to draw them
	// Note: returns nothing and passed by reference ("&")
	void getParticles( std::vector<cParticle*> &vec_pParticles );
private:
	// Static consts can be set here, static can't
	static const unsigned int DEFAULT_NUM_PARTICLES = 1000;

	std::vector<cParticle*> m_vec_pParticles;

	// Taken from line 229 of the DebugRenderer:
	template <class T>
	T randInRange(T min, T max)
	{
		double value =
			min + static_cast <double> (rand())
			/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
		return static_cast<T>(value);
	};

	// Creates a single particle (called by Initialize and Step)
	void m_CreateNewParticle(glm::vec3 minVelocity, glm::vec3 maxVelocity,
							 glm::vec3 minDeltaPosition, glm::vec3 maxDeltaPosition,
							 float minLifeSeconds, float maxLifeSeconds);

	// Saved for when we call Step()
	// These are set when we call Initialize();
	glm::vec3 m_minVelocity;
	glm::vec3 m_maxVelocity;
	glm::vec3 m_minDeltaPosition;
	glm::vec3 m_maxDeltaPosition;
	float m_minLifeSeconds;
	float m_maxLifeSeconds;
	int m_minParticlesPerFrame;
	int m_maxParticlesPerFrame;
};