#ifndef LIGHTING_H
#define LIGHTING_H

#include "shader.h"

namespace POLYGINE {
	
	class Lighting {
	private:
		float _radius;
		uint _subdivies;

		GLuint _VAO, _VBO, _EBO;
		
		std::vector<glm::vec3> _vertices;
		gluintvec _indices;

	    glm::mat4 _modelMat = glm::mat4(1.0f);
		glm::vec3 _light = glm::vec3(1.0f);

		void _bind();
		
	public:
		Lighting(float r, uint subs);
		~Lighting();
		
		void draw(std::shared_ptr<Shader> shader);
		glm::vec3 getLight() {return _light;};
		
	};
	
}

#endif
