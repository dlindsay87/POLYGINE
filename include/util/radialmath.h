#ifndef RADIALMATH_H
#define RADIALMATH_H

#include <cmath>
#include <glm/glm.hpp>

namespace UTIL {
  
    #define M_DIM 3
	#define M_TAU (2.0f * M_PI)
	#define M_CIRCLE 360.0f
	#define M_SEMI 180.0f
	#define M_90 90.0f
	#define M_45 45.0f
	#define M_DEG2RAD (M_PI / M_SEMI)
	#define M_RAD2DEG (M_SEMI / M_PI)

    extern void modScalar(float& f, float mod, float offset = 0.0f);
	
	extern void modVec3(glm::vec3& vec, float mod, float offset = 0.0f);

    void circleTweenScalar(float &init, float fin, float inc = 0.1f);

    extern glm::vec3 getPosFromAng(float r, glm::vec3 ang);

}

#endif
