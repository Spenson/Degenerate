#pragma once

#include "../iEntity.h"
#include "../iBehaviour.h"

namespace DegenBehaviours
{
	class cWanderAndIdle : public iBehaviour
	{
	public:
		cWanderAndIdle(iEntity* agent, iEntity* target);
		virtual ~cWanderAndIdle(void);

		virtual void Update(float dt);

	private:
		iEntity* mAgent;
		iEntity* mTarget;

		float mTime = 0.f;
		bool mIdle = false;
	};

}