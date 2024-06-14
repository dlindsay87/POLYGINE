#ifndef SHAPES_H
#define SHAPES_H

#include "display/shader.h"

namespace POLYGINE {
	
	typedef enum class ShapeType {
		TETRAHEDRON,
		ICOSPHERE,
		CUBESPHERE,
		DODECAHEDRON
	} ST;
	
	class Shape {
	private:
		float _radius;
		uint _subdivies;

		GLuint _VAO, _VBO, _EBO;
		
		std::vector<glm::vec3> _vertices;
		gluintvec _indices;

	    glm::mat4 _modelMat;
		glm::vec3 _colors;
		
		ST _type;

		void _bind();
		
	public:
		Shape(float r, uint subs, glm::vec3 col, ST shape=ST::CUBESPHERE);
		~Shape();
		
		void setSubdivies(uint subs) {_subdivies = subs;};
		
		void update(float &s, cartesian &p, orientation &o);
		void draw(std::shared_ptr<Shader> shader, glm::vec3 light);
		
	};
}

#endif