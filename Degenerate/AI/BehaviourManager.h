#pragma once

#include <map>
#include "iEntity.h"
#include "iBehaviour.h"

namespace DegenBehaviours
{
	class BehaviourManager
	{
	public:
		BehaviourManager(void);
		~BehaviourManager(void);

		void SetBehaviour(iEntity* agent, iBehaviour* behaviour);
		void RemoveAgent(iEntity* agent);

		void Update(float dt);

	private:
		std::map<iEntity*, iBehaviour*> mBehaviourMap;

		typedef std::map<iEntity*, iBehaviour*>::iterator behaviour_iterator;
	};

}