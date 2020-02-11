#pragma once

#include "../iEntity.h"
#include "../iBehaviour.h"
#include <vector>

namespace DegenBehaviours
{
	class cPursueAndEvade : public iBehaviour
	{
	public:
		cPursueAndEvade(iEntity* agent, iEntity* target);
		virtual ~cPursueAndEvade(void);

		virtual void Update(float dt);

		static void AddEvade(iEntity* evade);
		static void RemoveEvade(iEntity* evade);

	private:
		iEntity* mAgent;
		iEntity* mTarget;
		static std::vector<iEntity*> mEvade;
	};

}