#include "radialmath.h"

namespace UTIL
{

void modScalar(float &f, float mod, float offset)
{
	f = glm::mod(f + offset, mod) - offset;
}

void modVec3(glm::vec3 &vec, float mod, float offset)
{
	modScalar(vec.x, mod, offset);
	modScalar(vec.y, mod, offset);
	modScalar(vec.z, mod, offset);
}

void circleTweenScalar(float &init, float fin, float inc)
{
	float dir = init;
	modScalar(dir, M_CIRCLE, M_SEMI);

	if (std::abs(dir) < inc)
		init = fin;
	else
		init += std::copysign(inc, dir);
}

glm::vec3 getPosFromAng(float r, glm::vec3 ang)
{
	ang *= M_DEG2RAD;
	return glm::vec3(r * -sin(ang.z) * cos(ang.x),
			 r * cos(ang.x) * cos(ang.z), r * sin(ang.x));
}

} // namespace UTIL
