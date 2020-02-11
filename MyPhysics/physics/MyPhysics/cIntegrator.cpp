#include "cIntegrator.h"
/**
 * \file	cIntegrator.cpp
 * \path	D:\GDP\Degenerate\MyPhysics\physics\MyPhysics
 * \brief	Class Implementation File
 *
 * \desc	contains the implementation of cIntegrator
 */

namespace MyPhysics
{
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
	void cIntegrator::Euler(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, const glm::vec3& appliedAcc, float dt)
	{
		vel += acc * dt;
		vel += appliedAcc * dt;
		pos += vel * dt;
		acc = glm::vec3(0.f);
	}



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
	void cIntegrator::RK4(glm::vec3& pos, glm::vec3& vel, glm::vec3& acc, const glm::vec3& gravity, float dt)
	{
		State state;
		state.x = pos;
		state.v = vel;
		integrate(state, acc + gravity, dt);

		pos = state.x;
		vel = state.v;

	}

	//private
	cIntegrator::Derivative cIntegrator::evaluate(const State& initial, glm::vec3 t, float dt, const Derivative& d)
	{
		State state;
		state.x = initial.x + d.dx * dt;
		state.v = initial.v + d.dv * dt;

		Derivative output;
		output.dx = state.v;
		output.dv = t;
		return output;
	}

	//private
	void cIntegrator::integrate(State& state, glm::vec3 t, float dt)
	{
		Derivative a, b, c, d;

		a = evaluate(state, t, 0.0f, Derivative());
		b = evaluate(state, t, dt * 0.5f, a);
		c = evaluate(state, t, dt * 0.5f, b);
		d = evaluate(state, t, dt, c);

		glm::vec3 dxdt = 1.0f / 6.0f * (a.dx + 2.0f * (b.dx + c.dx) + d.dx);

		glm::vec3 dvdt = 1.0f / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);


		state.x = state.x + dxdt * dt;
		state.v = state.v + dvdt * dt;
	}
}
