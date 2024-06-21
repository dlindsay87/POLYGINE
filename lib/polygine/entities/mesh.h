#ifndef MESH_H
#define MESH_H

#include "core/init.h"
#include "display/shader.h"

namespace POLYGINE {
	
	typedef enum class ShapeType {
		POLYGON,
		TETRAHEDRON,
		ICOSPHERE,
		CUBESPHERE,
		DODECAHEDRON
	} ST;
	
	class Mesh {
	private:
		std::uniform_real_distribution<float> _uni_dist;
		
		uint _points, _oldPoints;
		ST _type;

		GLuint _VAO, _VBO, _EBO;
		
		std::vector<glm::vec3> _vertices;
		gluintvec _indices;

	    glm::mat4 _modelMat;
		glm::vec3 _colors; // Legacy colors {1.0, 0.5, 0.2}

		void _define();
		void _bind();
		
	public:
		Mesh();
		Mesh(uint points, ST type);
		~Mesh();
		
		void setPoints(uint p) {_points = p;}
		ST getType() {return _type;}
		
		void update(float &s, glm::vec3 &p, glm::vec3 &o);
		void draw(std::shared_ptr<Shader> shader, glm::vec3 light);
		
		void printVertices() {
			cout << endl;
			for (auto &v : _vertices) {
				cout << v.x << " ";
				cout << v.y << " ";
				cout << v.z << endl;
			}
		};
		
	};
}

#endif