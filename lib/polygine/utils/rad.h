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
	
	void thinVertices(std::vector<glm::vec3> &vertices, gluintvec &indices);
	
	void getNormalsFromCenter(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals);
	
	void circleTweenScalar(float &init, float fin, float inc = 6.0f);
	
	//void getCubeSphereNormals(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, gluintvec &indices);

}

#endif
