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
			r * -sin(ang.z) * cos(ang.x),
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

	void genCubeSphere(std::vector<glm::vec3>& vertices, gluintvec& indices, uint subs) {
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
	                    case 2: // -Y face
	                        vertex = glm::vec3(-1.0f + 2.0f * a, -1.0f, -1.0f + 2.0f * b);
	                        break;
	                    case 3: // +Y face
	                        vertex = glm::vec3(-1.0f + 2.0f * a, 1.0f, -1.0f + 2.0f * b);
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
						indices.push_back(base + (subs + 1));
	                    indices.push_back(base + 1);
						indices.push_back(base + (subs + 1) + 1);
						indices.push_back(base + 1);
						indices.push_back(base + (subs + 1));
	                    
	                }
	            }
	        }
	    }
	}
	
	void thinVertices(std::vector<glm::vec3> &vertices, gluintvec &indices) {
		std::unordered_set<glm::vec3> uniqueVerts(vertices.begin(), vertices.end());
		
		for (auto &idx : indices) {
			idx = std::distance(uniqueVerts.begin(), uniqueVerts.find(vertices[idx]));
		}
		
		vertices.assign(uniqueVerts.begin(), uniqueVerts.end());
	}
	
	// Maybe redundant because I can just asign the normals as the vertices in use?
	void getNormalsFromCenter(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals) {
		normals.assign(vertices.begin(), vertices.end());
	}
	
	void circleTweenScalar(float &init, float fin, float inc) {
		float dir = modScalar(fin - init, M_CIRCLE, M_SEMI);

	    if (std::abs(dir) < inc) init = fin;
		else init += std::copysign(inc, dir);
	}
	
	// I went cuckoo trying to calculate normals for the cubsphere
	// Cross products wouldn't always point outward or average correctly
	// Had to remove redundant vertices and map the right indices
	// Turns out since a cubsphere is a uniform polyhedron, my vertices are my normals
	// I already normalized my vertices around the object's center :(
	// Code kept for legacy, in case it may serve a purpose later
	/*void getCubeSphereNormals(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, gluintvec &indices) {
		// Initialize normals to zero
		int faces = vertices.size() - 2;
		normals.clear();
	    normals.resize(vertices.size(), glm::vec3(0.0f));
		
	    // Iterate over each triangle and calculate the normals
	    for (size_t i = 0; i < indices.size(); i += M_DIM) {
	        // Get the indices of the triangle vertices
	        GLuint idx00 = indices[i]; // center point
	        GLuint idx01 = indices[i + 1];
	        GLuint idx02 = indices[i + 2];
			
	        // Get the triangle vertices
	        glm::vec3 v00 = vertices[idx00];
	        glm::vec3 v01 = vertices[idx01];
	        glm::vec3 v02 = vertices[idx02];

			glm::vec3 a1 = v01 - v00;
			glm::vec3 b1 = v02 - v00;

			if ((i / faces) % 2 != 0) {
				a1 = v02 - v00;
				b1 = v01 - v00;
			}

	        // Calculate the normal for the current triangle
			glm::vec3 normal1 = glm::cross(a1, b1);

	        // Accumulate the normal for each vertex of the triangle
	        normals[idx00] += normal1;
	        normals[idx01] += normal1 / 2.0f;
	        normals[idx02] += normal1 / 2.0f;
	    }

	    // Normalize the accumulated normals for each vertex
	    for (auto &n : normals) {
	        n = glm::normalize(n);
	    }
	}*/
	
}
