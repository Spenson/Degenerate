#pragma once
#include "../GLCommon.h"
#include "eType.h"


namespace DegenRendering
{
	class iRenderComponent
	{
	public:
		virtual ~iRenderComponent() = default;
		
		iRenderComponent() = delete;
		iRenderComponent(const iRenderComponent& other) = delete;
		iRenderComponent& operator=(const iRenderComponent& other) = delete;
		
		inline const eType& GetComponentType() { return mComponentType; }

		virtual void SetTransform(const glm::mat4& transform) = 0;

	protected:
		iRenderComponent(eType componentType)
			: mComponentType(componentType)
		{
		}
	private:
		eType mComponentType;

	};
};