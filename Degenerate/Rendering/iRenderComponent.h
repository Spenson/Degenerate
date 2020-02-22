#pragma once
#include "../GLCommon.h"
#include "eRendType.h"


namespace DegenRendering
{
	class iRenderComponent
	{
	public:
		virtual ~iRenderComponent() = default;
		
		iRenderComponent() = delete;
		iRenderComponent(const iRenderComponent& other) = delete;
		iRenderComponent& operator=(const iRenderComponent& other) = delete;
		
		inline const eRendType& GetComponentType() { return mComponentType; }

		virtual void SetTransform(const glm::mat4& transform) = 0;

	protected:
		iRenderComponent(eRendType componentType)
			: mComponentType(componentType)
		{
		}
	private:
		eRendType mComponentType;

	};
};