#pragma once
/**
 * \file	cIntegrator.h
 * \path	D:\GDP\Degenerate\MyPhysics\physics\MyPhysics
 * \brief	Class Header File
 *
 * \desc	contains the description of cIntegrator
 */
#include "glmCommon.h"

namespace MyPhysics
{
	/**
	 * \class	cIntegrator
	 * \brief	integrates motion of objects
	 */
	class cIntegrator
	{
	private:
		struct State
		{
			glm::vec3 x;      // position
			glm::vec3 v;      // velocity
		};
		struct Derivative
		{
			glm::vec3 dx;      // dx/dt = velocity
			glm::vec3 dv;      // dv/dt = acceleration
		};

		Derivative evaluate(const State& initial, glm::vec3 t, float dt, const Derivative& d);
		void integrate(State& state, glm::vec3 t, float dt);
	public:
		/**
		 * \method		cIntegrator
		 * \fullname	MyPhysics::cIntegrator::cIntegrator
		 * \brief		default ctor
		 *
		 * \access		public 	
		 */
		cIntegrator() = default;
		/**
		 * \method		~cIntegrator
		 * \fullname	MyPhysics::cIntegrator::~cIntegrator
		 * \brief		default dtor
		 *
		 * \access		virtual public 
		 */
		virtual ~cIntegrator() = default;

		/**
		 * \method		Euler
		 * \fullname	MyPhysics::cIntegrator::Euler
		 * \brief		Euler integration calculation
		 *
		 * \access		public 
		 * \param		glm::vec3 & pos
		 * \param		glm::vec3 & vel
		 * \param		glm::vec3 & acc
		 * \param		const glm::vec3 & appliedAcc
		 * \param		float dt
		 * 
		 * \return		glm::vec3 & pos
		 * \return		glm::vec3 & vel
		 */
		void Euler(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, const glm::vec3& appliedAcc, float dt);


		/**
		 * \method		RK4
		 * \fullname	MyPhysics::cIntegrator::RK4
		 * \brief		FOURTH-ORDER RUNGE-KUTTA integration calculation
		 *
		 * \access		public 
		 * \param		glm::vec3 & pos
		 * \param		glm::vec3 & vel
		 * \param		glm::vec3 & acc
		 * \param		const glm::vec3 & gravity
		 * \param		float dt
		 * 
		 * \return		glm::vec3 & pos
		 * \return		glm::vec3 & vel
		 */
		void RK4(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, const glm::vec3& gravity, float dt);
	};
}
