#pragma once

#include "glmCommon.h"

namespace MyPhysics
{
	class cIntegrator
	{
	private:
		// TODO: Define any structs used internally for specific schemes.
		//       Such as,
		struct State;
		struct Derivative;
		struct sRK4State;
		// TODO: Define any methods used interally for specific schemes.

	public:
		// Constructor
		cIntegrator();

		// TODO: Do you really want all these options? Do you want others?
		//       You really only need RK4 (or Velocity Verlet) for Project 2.

		// TODO: Fully comment the inputs/outputs of any
		//       integration method you do end up including.


		// FOURTH-ORDER RUNGE-KUTTA
		void RK4(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, float dt);
		void RK4(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, const glm::vec3& appliedAcc, float dt);
	};
}
