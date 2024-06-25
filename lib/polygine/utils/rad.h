#ifndef RAD_H
#define RAD_H

#include <cmath>

#include "utils/typer.h"

namespace POLYGINE {
	
	#define M_DIM 3
	#define M_TAU (2.0f * M_PI)
	#define M_CIRCLE 360.0f
	#define M_SEMI 180.0f
	#define M_90 90.0f
	#define M_45 45.0f
	#define M_DEG2RAD (M_PI / M_SEMI)
	#define M_RAD2DEG (M_SEMI / M_PI)

	float modScalar(float f, float mod, float offset = 0.0f);
	void modVec3(glm::vec3 &vec, float mod, float offset = 0.0f);

	glm::vec3 getPosFromAng(float r, glm::vec3 ang);

	void fan2D(std::vector<glm::vec3> &vertices, gluintvec &indices, int tris);
	void genCubeSphere(std::vector<glm::vec3> &vertices, gluintvec &indices, uint subs);
	
	void circleTweenScalar(float &init, float fin, float inc = 6.0f);

	//legacy code I'm not sure is useful or even correct
	/*struct cartesian {float x; float y; float z;};
	struct polar {float r; float theta; float phi;};
	void getPolFromCart(cartesian &c, polar &p);
	void getCartFromPol(polar &p, cartesian &c);*/

	// custom transformations that are redundant
	/*void rotate(glfltvec &arr, float rx, float ry, float rz);
	void scale(glfltvec &arr, float s);
	void translate(glfltvec &arr, float tx, float ty, float tz);*/
}

#endif
