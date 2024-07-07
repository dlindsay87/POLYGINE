#ifndef MESH_H
#define MESH_H

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
		uint _points, _oldPoints;
		ST _type;

		GLuint _VAO, _VBO, _VNO, _EBO;
		
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec3> _normals;
		gluintvec _indices;

	    glm::mat4 _modelMat;
		glm::vec3 _colors; // Legacy colors {1.0, 0.5, 0.2}

		void _define();
		void _bind();
		void _normalBind();
		
	public:
		Mesh(uint points, ST type, bool verbose = true);
		~Mesh();
		
		void setPoints(uint p) {_points = p;}
		void recolor(glm::vec3 c) {_colors = c;}
		ST getType() {return _type;}
		
		void update(float &s, glm::vec3 &p, glm::vec3 &o);
		
		void o_draw(std::shared_ptr<Shader> shader);
		void l_draw(std::shared_ptr<Shader> shader);
		
		void printVertices() {
			cout << endl;
			for (auto &v : _vertices) {
				cout << v.x << " ";
				cout << v.y << " ";
				cout << v.z << endl;
			}
		}
		
		void printNormals() {
			cout << endl;
			for (auto &n : _normals) {
				cout << n.x << " ";
				cout << n.y << " ";
				cout << n.z << endl;
			}
		}
		
		void printIndices() {
			cout << endl;
			for (uint i = 0; i < _indices.size(); i += M_DIM) {
				cout << _indices[i] << " ";
				cout << _indices[i + 1] << " ";
				cout << _indices[i + 2] << endl;
			}
		}
		
	};
}

#endif