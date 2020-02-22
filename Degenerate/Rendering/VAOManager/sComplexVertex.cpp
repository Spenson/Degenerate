
#include "sComplexVertex.h"
#include <vector>


sComplexVertex::sComplexVertex() :
	x(0.0f), y(0.0f), z(0.0f), w(1.0f),
	r(0.0f), g(0.0f), b(0.0f), a(1.0f),		// Note alpha is 1.0
	nx(0.0f), ny(0.0f), nz(0.0f), nw(1.0f),
	u0(0.0f), v0(0.0f), u1(0.0f), v1(0.0f),
	tx(0.0f), ty(0.0f), tz(0.0f), tw(1.0f),
	bx(0.0f), by(0.0f), bz(0.0f), bw(1.0f)
{
	//#ifdef _DEBUG
	memset(this->boneID, 0, sizeof(unsigned int) * NUMBEROFBONES);
	memset(this->boneWeights, 0, sizeof(float) * NUMBEROFBONES);


	return;
}
