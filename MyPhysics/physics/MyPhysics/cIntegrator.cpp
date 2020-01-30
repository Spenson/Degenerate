#include "cIntegrator.h"

namespace MyPhysics
{
	cIntegrator::cIntegrator()
	{
	}

	cIntegrator::Derivative cIntegrator::evaluate(const State& initial, double t, float dt, const Derivative& d)
	{
		State state;
		state.pos = initial.pos + d.dx * dt;
		state.vel = initial.vel + d.dv * dt;

		Derivative output;
		output.dx = state.vel;
		output.dv = acceleration(state, t + dt);
		return output;
	}

	void cIntegrator::integrate(State& state, double t, float dt)
	{
		Derivative a, b, c, d;

		a = evaluate(state, t, 0.0f, Derivative());
		b = evaluate(state, t, dt * 0.5f, a);
		c = evaluate(state, t, dt * 0.5f, b);
		d = evaluate(state, t, dt, c);

		glm::vec3 dxdt = 1.0f / 6.0f * (a.dx + 2.0f * (b.dx + c.dx) + d.dx);

		glm::vec3 dvdt = 1.0f / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);

		state.pos = state.pos + dxdt * dt;
		state.vel = state.vel + dvdt * dt;
	}
}
