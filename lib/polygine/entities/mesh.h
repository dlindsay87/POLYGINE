#ifndef H_MESH
#define H_MESH

#include "core/init.h"
#include "display/shader.h"

namespace POLYGINE {
	
	class Mesh {
	private:
		GLuint _VAO, _VBO;
		
		int _points = 99;
		
		std::uniform_real_distribution<float> _uni_dist;
		
		glfltvec _vertices;
	    glm::mat4 _modelMat;
		glm::vec3 _colors; //{1.0, 0.5, 0.2}

		void _bind();
		
	public:
		Mesh();
		~Mesh();
		
		void update(float &s, cartesian &p, orientation &o);
		void draw(std::shared_ptr<Shader> shader);
		
		void setPoints(int v) {_points = v;};
		
		void printVertices() {
			cout << endl;
			for (int i = 0; i < _vertices.size(); i++) {
				cout << _vertices[i] << (i % 3 == 2 ? "\n" : " ");
			}
		}

	};

}

#endif
