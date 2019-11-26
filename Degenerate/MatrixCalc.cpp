#include "MatrixCalc.h"
#include <glm/gtc/type_ptr.hpp>


// This is JUST the transformation lines from the DrawObject call
glm::mat4 calculateWorldMatrix(GameObject* pCurrentObject, glm::mat4 matWorld)
{

	// ******* TRANSLATION TRANSFORM *********
	glm::mat4 matTrans
		= glm::translate(glm::mat4(1.0f),
						 glm::vec3(pCurrentObject->position.x,
								   pCurrentObject->position.y,
								   pCurrentObject->position.z));
	matWorld = matWorld * matTrans;
	// ******* TRANSLATION TRANSFORM *********


	// ******* ROTATION TRANSFORM *********
	glm::mat4 matRotation = glm::mat4(pCurrentObject->getQOrientation());
	matWorld = matWorld * matRotation;
	// ******* ROTATION TRANSFORM *********


	// ******* SCALE TRANSFORM *********
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
								 glm::vec3(pCurrentObject->scale.x,
										   pCurrentObject->scale.y,
										   pCurrentObject->scale.z));
	matWorld = matWorld * scale;
	// ******* SCALE TRANSFORM *********


	return matWorld;
}