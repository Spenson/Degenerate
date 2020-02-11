#pragma once

#include "../iEntity.h"
#include "../iBehaviour.h"

namespace DegenBehaviours
{
	class cSeek : public iBehaviour
	{
	public:
		cSeek(iEntity* agent, iEntity* target);
		virtual ~cSeek(void);

		virtual void Update(float dt);

	private:
		iEntity* mAgent;
		iEntity* mTarget;
	};

}