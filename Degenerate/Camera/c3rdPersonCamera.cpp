#include "c3rdPersonCamera.h"



void c3rdPersonCamera::Update(glm::mat4 transformIn)
{
	// dir for ratation
	glm::vec3 up(0.f, 1.f, 0.f);
	glm::vec3 right(1.f, 0.f, 0.f);

	// pos of object
	mTarget = glm::vec3(transformIn[3].x, 0.f, transformIn[3].z);

	// eye position calculation based off pitch, yaw and distance
	glm::vec4 offset(mOffset, 0.f);

	//Changed to ignore rotation
	//glm::mat4 transform(glm::rotate(transformIn, glm::radians(mYaw), up));
	glm::mat4 transform(glm::rotate(glm::mat4(1.f), glm::radians(mYaw), up));
	transform = glm::rotate(transform, glm::radians(mPitch), right);

	offset = transform * offset;

	offset = glm::normalize(offset) * mDistance;

	mPos = (mTarget + glm::vec3(offset));


}

void c3rdPersonCamera::AddYaw(float degrees)
{
	mYaw += degrees;
	if (mYaw < 0) mYaw += 360;
	if (mYaw > 360) mYaw -= 360;
}

void c3rdPersonCamera::AddPitch(float degrees)
{
	mPitch += degrees;
	if (mPitch < -20.0) mPitch = -20.0;
	if (mPitch > 89.9) mPitch = 89.9;
}

void c3rdPersonCamera::SetYaw(float degrees)
{
	mYaw += degrees;
	while (mYaw < 0) mYaw += 360;
	while (mYaw > 360) mYaw -= 360;

}

void c3rdPersonCamera::SetPitch(float degrees)
{
	mPitch += degrees;
	if (mPitch < -20.0) mPitch = -20.0;
	if (mPitch > 89.9) mPitch = 89.9;
}

void c3rdPersonCamera::AddZoom(float dist)
{
	mDistance += dist;
	if (mDistance < 5.f) mDistance = 5.f;
	if (mDistance > 50.f) mDistance = 50.f;

}


glm::vec3 c3rdPersonCamera::Position()
{
	return mPos;
}
glm::vec3 c3rdPersonCamera::Target()
{
	return mTarget;
}
glm::vec3 c3rdPersonCamera::UpVector()
{
	return mUp;
}