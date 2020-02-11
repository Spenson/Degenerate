#pragma once

#include "../iEntity.h"
#include "../iBehaviour.h"

namespace DegenBehaviours
{
	class cSeekAndFlee : public iBehaviour
	{
	public:
		cSeekAndFlee(iEntity* agent, iEntity* target);
		virtual ~cSeekAndFlee(void);

		virtual void Update(float dt);

	private:
		iEntity* mAgent;
		iEntity* mTarget;
	};

}