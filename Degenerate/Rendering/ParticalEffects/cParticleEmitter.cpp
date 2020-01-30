#include "cParticleEmitter.h"
#include <algorithm>		// for std::copy()


cParticle::cParticle()
{
	// Note: we aren't really using these default values...
	this->location = glm::vec3(0.0f,0.0f,0.0f);
	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->lifeTime = 0.0f;
	this->colourRGBA = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	// 
	// glm::vec orientation
	// float scale
	// glm::vec3 acceleration;	// For each particle

	return;
}

cParticleEmitter::cParticleEmitter()
{
	// NOTE: I'm NOT setting up the particles here.
	// That will happen in initialize()
	this->location = glm::vec3(0.0f,0.0f,0.0f);
	this->acceleration = glm::vec3(0.0f,0.0f,0.0f);
	return;
}


void cParticleEmitter::Step(float deltaTime)
{
	// Loop through the particles:
	// - Decrease the life by "deltaTime"
	// - If "still alive" (lifeTime > 0.0):
	//    - Move the particle

	for ( std::vector<cParticle*>::iterator itPart = this->m_vec_pParticles.begin();
		  itPart != this->m_vec_pParticles.end();  itPart++ )
	{
		cParticle* pCurParticle = *itPart;	// Dereference iterator, giving us the original type

		pCurParticle->lifeTime -= deltaTime;

		// Is it dead, Jim? (Star Trek reference)
		if ( pCurParticle->lifeTime > 0.0f )
		{ 
			// Update velocity from acceler
			pCurParticle->velocity += ( this->acceleration * deltaTime );

			// Update position from velocity
			pCurParticle->location += ( pCurParticle->velocity * deltaTime );

		}// if ( pCurParticle->lifeTime > 0.0f )

	}//for ( std::vector<cParticle*>::iterator itPart

	// How many new particles should we create this frame? 
	int numParticleToCreate = randInRange<int>(this->m_minParticlesPerFrame, this->m_maxParticlesPerFrame);

	for (int count = 0; count != numParticleToCreate; count++)
	{
		this->m_CreateNewParticle( this->m_minVelocity, this->m_maxVelocity, 
								   this->m_minDeltaPosition, this->m_maxDeltaPosition,
								   this->m_minLifeSeconds, this->m_maxLifeSeconds );
	}//for (int count = 0;

	return;
}

void cParticleEmitter::Initialize(glm::vec3 minVelocity, glm::vec3 maxVelocity,
								  glm::vec3 minDeltaPosition, glm::vec3 maxDeltaPosition,
								  float minLifeSeconds, float maxLifeSeconds,
								  int minParticlesPerFrame, int maxParticlesPerFrame)
{
	// In case we are calling Initialize() again... 
	// Clear all the existing particles
	// TODO: 
	// - If the new size is LARGER than the current vector, 
	//   allocate the extra space and call new
	// - If the new size is SMALLER than the current vector, 
	//   go though and call delete on all the "extra" particles. 

//	this->m_vec_pParticles.clear();

	// Load the vector with the maximum number of particles
	// Reserve doesn't create the objects, it just sets asside space in 1 step
	this->m_vec_pParticles.reserve( cParticleEmitter::DEFAULT_NUM_PARTICLES );

	for (int count = 0; count != cParticleEmitter::DEFAULT_NUM_PARTICLES; count++)
	{
		// TODO: If we are calling Initialize() AGAIN, 
		//       then we DON'T want to call new
		cParticle* pNewParticle = new cParticle();

		// Set the lifetime to 0.0 for all of them
		pNewParticle->lifeTime = 0.0f;

		this->m_vec_pParticles.push_back( pNewParticle );

	}

	//// Or you could do it a silly way... 
	//for ( std::vector<cParticle*>::iterator itParticle = this->m_vec_pParticles.begin();
	//	  itParticle != this->m_vec_pParticles.end(); itParticle++ )
	//{
	//	(*itParticle)->lifeTime = 0.0f;
	//}

	this->m_minVelocity = minVelocity;
	this->m_maxVelocity = maxVelocity;
	this->m_minDeltaPosition = minDeltaPosition;
	this->m_maxDeltaPosition = maxDeltaPosition;
	this->m_minLifeSeconds = minLifeSeconds;
	this->m_maxLifeSeconds = maxLifeSeconds;
	this->m_minParticlesPerFrame = minParticlesPerFrame;
	this->m_maxParticlesPerFrame = maxParticlesPerFrame;


	return;
}



void cParticleEmitter::m_CreateNewParticle(
	glm::vec3 minVelocity, glm::vec3 maxVelocity,
	glm::vec3 minDeltaPosition, glm::vec3 maxDeltaPosition,
	float minLifeSeconds, float maxLifeSeconds)
{
	// Find the 1st particle that has life <= 0.0f
	for (std::vector<cParticle*>::iterator itPart = this->m_vec_pParticles.begin();
		 itPart != this->m_vec_pParticles.end();  itPart++)
	{
		// Is this particle "dead"? 
		cParticle* pCurParticle = *itPart;

		if (pCurParticle->lifeTime <= 0.0f)
		{
			// Make it "alive" and set to some values
			pCurParticle->lifeTime = randInRange<float>(minLifeSeconds, maxLifeSeconds);

			// Set the initial velocity
			pCurParticle->velocity.x = randInRange<float>(minVelocity.x, maxVelocity.x);
			pCurParticle->velocity.y = randInRange<float>(minVelocity.y, maxVelocity.y);
			pCurParticle->velocity.z = randInRange<float>(minVelocity.z, maxVelocity.z);
			//pCurParticle->velocity = randInRange<glm::vec3>(minVelocity, maxVelocity);

			// TODO: Adjust position based on Max and Min delta postiion
			// (For now, just make the particle the same as the emitter)
			pCurParticle->location = this->location;
		}
	}
	return;
}


void cParticleEmitter::getParticles(std::vector<cParticle*>& vec_pParticles)
{
	// Copy the internal vector of particles to the one that is passed.

	vec_pParticles.clear();
	vec_pParticles.reserve( this->m_vec_pParticles.size() );
//	// Sets the pointer values to zero (NULL)
//	vec_pParticles.resize( this->m_vec_pParticles.size(), 0 );

	// NOTE: There has to be space there, 
	// AND the objects have to be initialized already
//	std::copy( this->m_vec_pParticles.begin(), 
//			   this->m_vec_pParticles.end(), 
//			   vec_pParticles.begin() );

	for (std::vector<cParticle*>::iterator itPart = this->m_vec_pParticles.begin();
		 itPart != this->m_vec_pParticles.end(); itPart++)
	{
		// If alive, copy over
		cParticle* pCurPart = *itPart;

		if (pCurPart->lifeTime > 0.0f)
		{
			vec_pParticles.push_back( pCurPart );
		}
	}

	return;
}
