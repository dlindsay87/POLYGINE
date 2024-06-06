#ifndef RAD_H
#define RAD_H

#include <cmath>
#include "utils/typer.h"

namespace POLYGINE {
	
	#define M_DIM 3
	#define M_TAU (2 * M_PI)
	#define M_CIRCLE 360
	#define M_DEG2RAD (M_TAU / M_CIRCLE)
	#define M_RAD2DEG (M_CIRCLE / M_TAU)

	struct cartesian {float x; float y; float z;};
	struct polar {float r; float theta; float phi;};
	struct orientation {float theta; float phi;};

	void getPolFromCart(cartesian c, polar &p);
	void getCartFromPol(polar p, cartesian &c);

	void fan2D(glfltvec &arr, int tris);

	// custom transformations that are redundant
	/*void rotate(glfltvec &arr, float rx, float ry, float rz);

	void scale(glfltvec &arr, float s);

	void translate(glfltvec &arr, float tx, float ty, float tz);*/
}

#endif
