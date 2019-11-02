#include "Damage.h"

void Damage::Update(double deltaTime)
{
	if (this->pGameObject->isVisible == true)
	{
		if (timeExisted > 0.1f)
			this->pGameObject->isVisible = false;

		timeExisted += deltaTime;
	}
}
