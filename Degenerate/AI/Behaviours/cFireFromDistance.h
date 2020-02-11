#pragma once

#include "../iEntity.h"
#include "../iBehaviour.h"

namespace DegenBehaviours
{
	class cFireFromDistance : public iBehaviour
	{
	public:
		cFireFromDistance(iEntity* agent, iEntity* target);
		virtual ~cFireFromDistance(void);

		virtual void Update(float dt);

	private:
		iEntity* mAgent;
		iEntity* mTarget;
	};

}