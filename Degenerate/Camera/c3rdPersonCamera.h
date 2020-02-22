#pragma once

#include "../GLCommon.h"
#include "../Rendering/iCamera.h"

class c3rdPersonCamera : public DegenRendering::iCamera
{
	glm::vec3 mOffset;
	float mPitch;
	float mYaw;
	float mDistance;

	glm::vec3 mPos;
	glm::vec3 mTarget;
	glm::vec3 mUp;

public:
	c3rdPersonCamera() :mOffset(glm::vec3(0.f, 0.f, -1.f)),
		mPitch(0.f), mYaw(0.f), mDistance(10.f),
		mPos(glm::vec3(0.f, 0.f, 0.f)),
		mTarget(glm::vec3(0.f, 0.f, 0.f)),
		mUp(glm::vec3(0.f, 1.f, 0.f))
	{
	}
	//void SetTargetTransform(glm::mat4& transform);
	void Update(glm::mat4 transform);

	void SetOffset(glm::vec3 offset);

	void AddYaw(float degrees);
	void AddPitch(float degrees);
	void SetYaw(float degrees);
	void SetPitch(float degrees);
	void AddZoom(float dist);

	glm::vec3 Position() override;
	glm::vec3 Target() override;
	glm::vec3 UpVector() override;
};
