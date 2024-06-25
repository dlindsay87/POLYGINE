#include "rad.h"

namespace POLYGINE {
	
	float modScalar(float f, float mod, float offset) {
		return glm::mod(f + offset, mod) - offset;
	}
	
	void modVec3(glm::vec3 &vec, float mod, float offset) {
	    vec.x = modScalar(vec.x, mod, offset);
	    vec.y = modScalar(vec.y, mod, offset);
	    vec.z = modScalar(vec.z, mod, offset);
	}
	
	glm::vec3 getPosFromAng(float r, glm::vec3 ang) {
		ang *= M_DEG2RAD;
		return glm::vec3(
			r * sin(ang.z) * cos(ang.x),
	        r * cos(ang.x) * cos(ang.z),
			r * sin(ang.x)
		);
	}
	
	void fan2D(std::vector<glm::vec3> &vertices, gluintvec &indices, int tris) {
		vertices.clear();
		indices.clear();

		float angle = 0.0f;
		vertices.push_back(glm::vec3(0.0f));

		for (int i = 0; i < tris; i++) {
			vertices.push_back(glm::vec3(sin(angle), 0.0f, cos(angle)));

			indices.push_back(0);
			indices.push_back(i + 1);
			indices.push_back(i + 1 != tris ? i + 2 : 1);
			
			angle += (float)(M_TAU / tris);
		}
	}
	
	void genCubeSphere(std::vector<glm::vec3> &vertices, gluintvec &indices, uint subs) {
	    // Clear any existing data
	    vertices.clear();
	    indices.clear();
	    // Generate vertices and indices for each face
	    for (int face = 0; face < 6; face++) {
	        for (int i = 0; i <= subs; i++) {
	            for (int j = 0; j <= subs; j++) {
	                float a = (float)i / subs;
	                float b = (float)j / subs;

	                // Calculate vertex position based on face and subdivision
	                glm::vec3 vertex;
	                switch (face) {
	                    case 0: // +X face
	                        vertex = glm::vec3(1.0f, -1.0f + 2.0f * a, -1.0f + 2.0f * b);
	                        break;
	                    case 1: // -X face
	                        vertex = glm::vec3(-1.0f, -1.0f + 2.0f * a, -1.0f + 2.0f * b);
	                        break;
	                    case 2: // +Y face
	                        vertex = glm::vec3(-1.0f + 2.0f * a, 1.0f, -1.0f + 2.0f * b);
	                        break;
	                    case 3: // -Y face
	                        vertex = glm::vec3(-1.0f + 2.0f * a, -1.0f, -1.0f + 2.0f * b);
	                        break;
	                    case 4: // +Z face
	                        vertex = glm::vec3(-1.0f + 2.0f * a, -1.0f + 2.0f * b, 1.0f);
	                        break;
	                    case 5: // -Z face
	                        vertex = glm::vec3(-1.0f + 2.0f * a, -1.0f + 2.0f * b, -1.0f);
	                        break;
	                }

	                // Add the normalized, scaled vertex to the list
	                vertices.push_back(glm::normalize(vertex));

	                // Add indices for triangles
	                if (i < subs && j < subs) {
	                    int base = (face * (subs + 1) + i) * (subs + 1) + j;
	                    indices.push_back(base);
	                    indices.push_back(base + 1);
	                    indices.push_back(base + (subs + 1));
	                    indices.push_back(base + 1);
	                    indices.push_back(base + (subs + 1) + 1);
	                    indices.push_back(base + (subs + 1));
	                }
	            }
	        }
	    }
	}
	
	void circleTweenScalar(float &init, float fin, float inc) {
		float dir = modScalar(fin - init, M_CIRCLE, M_SEMI);

	    if (std::abs(dir) < inc) init = fin;
		else init += std::copysign(inc, dir);
	}
	
	/*void getPolFromCart(cartesian &c, polar &p) {
		p.r = sqrt(pow(c.x, 2.0) + pow(c.y, 2.0) + pow(c.z, 2.0));
		p.theta = acos(c.z/p.r);
		p.phi = atan2(c.y, c.x); //copysign(acos(c.x/sqrt(pow(c.x, 2.0) + pow(c.y, 2.0))), c.y);
	}

	void getCartFromPol(polar &p, cartesian &c) {
		c.x = p.r * sin(p.theta) * cos(p.phi);
		c.y = p.r * sin(p.theta) * sin(p.phi);
		c.z = p.r * cos(p.theta);
	}*/
	
	/*void rotate(glfltvec &arr, float rx, float ry, float rz){
		rx *= M_DEG2RAD;
		ry *= M_DEG2RAD;
		rz *= M_DEG2RAD;
		
		for (int i = M_DIM; i < arr.size(); i += M_DIM) {
			float tx = arr[i] - arr[0];
			float ty = arr[i+1] - arr[1];
			//float tz = arr[i+2] - arr[2];
			
			arr[i] = tx * cos(ry) - ty * sin(ry) + arr[0];
			arr[i+1] = tx * sin(ry) + ty * cos(ry) + arr[1];
			//arr[i+2] = + arr[2];
		}
	}

	void scale(glfltvec &arr, float s) {
		for (int i = M_DIM; i < arr.size(); i += M_DIM) {
			arr[i] = s * (arr[i] - arr[0]) + arr[0];
			arr[i+1] = s * (arr[i+1] - arr[1]) + arr[1];
			arr[i+2] = s * (arr[i+2] - arr[2]) + arr[2];
		}
	}

	void translate(glfltvec &arr, float tx, float ty, float tz) {
		for (int i = 0; i < arr.size(); i += M_DIM) {
			arr[i] += tx;
			arr[i+1] += ty;
			arr[i+2] += tz;
		}
	}*/
}