#ifndef RAD_H
#define RAD_H

#include <cmath>

#include "utils/typer.h"

namespace POLYGINE {
	
	#define M_DIM 3
	#define M_TAU (2 * M_PI)
	#define M_CIRCLE 360.0f
	#define M_DEG2RAD (M_TAU / M_CIRCLE)
	#define M_RAD2DEG (M_CIRCLE / M_TAU)

	struct cartesian {float x; float y; float z;};
	struct polar {float r; float theta; float phi;};
	
	void modVec3(glm::vec3 &vec, float mod);
	void modByComponent(float &f, float mod);

	void getPolFromCart(cartesian &c, polar &p);
	void getCartFromPol(polar &p, cartesian &c);
	glm::vec3 getPosFromAng(float r, glm::vec3 ang);

	void fan2D(std::vector<glm::vec3> &vertices, gluintvec &indices, int tris);
	void genCubeSphere(std::vector<glm::vec3> &vertices, gluintvec &indices, uint subs);

	// custom transformations that are redundant
	/*void rotate(glfltvec &arr, float rx, float ry, float rz);

	void scale(glfltvec &arr, float s);

	void translate(glfltvec &arr, float tx, float ty, float tz);*/
}

#endif
