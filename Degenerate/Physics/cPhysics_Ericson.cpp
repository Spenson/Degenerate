#include "cPhysics.h"

// Taken from Ericson's book:
cPhysics::Point cPhysics::ClosestPtPointTriangle(Point p, Point a, Point b, Point c)
{
	Vector ab = b - a;
	Vector ac = c - a;
	Vector bc = c - b;

	// Compute parametric position s for projection P' of P on AB,
	// P' = A + s*AB, s = snom/(snom+sdenom)
	float snom = glm::dot(p - a, ab), sdenom = glm::dot(p - b, a - b);

	// Compute parametric position t for projection P' of P on AC,
	// P' = A + t*AC, s = tnom/(tnom+tdenom)
	float tnom = glm::dot(p - a, ac), tdenom = glm::dot(p - c, a - c);

	if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out

	// Compute parametric position u for projection P' of P on BC,
	// P' = B + u*BC, u = unom/(unom+udenom)
	float unom = glm::dot(p - b, bc), udenom = glm::dot(p - c, b - c);

	if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
	if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out


	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
	Vector n = glm::cross(b - a, c - a);
	float vc = glm::dot(n, glm::cross(a - p, b - p));
	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab;

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
	float va = glm::dot(n, glm::cross(b - p, c - p));
	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc;

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
	float vb = glm::dot(n, glm::cross(c - p, a - p));
	// If P outside CA and within feature region of CA,
	// return projection of P onto CA
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac;

	// P must project inside face region. Compute Q using barycentric coordinates
	float u = va / (va + vb + vc);
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v; // = vc / (va + vb + vc)
	return u * a + v * b + w * c;
}



int cPhysics::TestSphereTriangle(Sphere s, Point a, Point b, Point c, Point& p)
{
	// Find point P on triangle ABC closest to sphere center
	p = this->ClosestPtPointTriangle(s.c, a, b, c);

	// Sphere and triangle intersect if the (squared) distance from sphere
	// center to point p is less than the (squared) sphere radius
	Vector v = p - s.c;
	return glm::dot(v, v) <= s.r * s.r;
}

float cPhysics::ScalarTriple(Vector u, Vector v, Vector w)
{
	// = (u × v) · w

	return glm::dot(glm::cross(u, v), w);
}

bool SameSign(float u, float v)
{
	if ((u < 0) ^ (v < 0))
		return false;

	return true;
}

// Given line pq and ccw triangle abc, return whether line pierces triangle. If
// so, also return the barycentric coordinates (u,v,w) of the intersection point
bool cPhysics::IntersectLineTriangle(Point p, Point q, Point a, Point b, Point c,
									 float& u, float& v, float& w,
									 Point& collisionPoint)
{
	Vector pq = q - p;
	Vector pa = a - p;
	Vector pb = b - p;
	Vector pc = c - p;

	// Test if pq is inside the edges bc, ca and ab. Done by testing
	// that the signed tetrahedral volumes, computed using scalar triple
	// products, are all positive
	
	//Vector m = glm::cross(pq, pc); 
	//u = glm::dot(pb, m); // ScalarTriple(pq, pc, pb); 
	//v = -glm::dot(pa, m); // ScalarTriple(pq, pa, pc); 
	//if (!SameSign(u, v)) return 0; 
	//w = ScalarTriple(pq, pb, pa); 
	//if (!SameSign(u, w)) return 0;
	
	u = ScalarTriple(pq, pc, pb);
	if (u < 0.0f) { return false; }
	v = ScalarTriple(pq, pa, pc);
	if (v < 0.0f) { return false; }
	w = ScalarTriple(pq, pb, pa);
	if (w < 0.0f) { return false; }

	// Compute the barycentric coordinates (u, v, w) determining the
	// intersection point r, r = u*a + v*b + w*c
	float denom = 1.0f / (u + v + w);
	u *= denom;
	v *= denom;
	w *= denom; // w = 1.0f - u - v;

	// Compute collision point from barycentric coordinates
	collisionPoint = u * a + v * b + w * c;


	// Added Because Above calculation is as if the line p, q is extened infinately
	if(glm::distance(p, collisionPoint) > glm::distance(p, q)
	   || glm::distance(q, collisionPoint) > glm::distance(p, q))
		return false;


	return true;
}
