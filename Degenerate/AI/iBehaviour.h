#pragma once

namespace DegenBehaviours
{
	class iBehaviour
	{
	public:
		virtual ~iBehaviour(void) {}
		virtual void Update(float dt) = 0;

	protected:
		iBehaviour(void) {}
	};
}
