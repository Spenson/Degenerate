#pragma once

#include "../iEntity.h"
#include "../iBehaviour.h"

namespace DegenBehaviours
{
	class cEvade : public iBehaviour
	{
	public:
		cEvade(iEntity* agent, iEntity* target);
		virtual ~cEvade(void);

		virtual void Update(float dt);

	private:
		iEntity* mAgent;
		iEntity* mTarget;
	};

}