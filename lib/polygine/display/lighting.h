#ifndef LIGHTING_H
#define LIGHTING_H

#include "entities/mesh.h"

namespace POLYGINE {
	
	class Lighting {
	private:
		glm::vec3 _position = glm::vec3(1.2f, -2.0f, 1.0f);
		glm::vec3 _orientation = glm::vec3(0.0f);
		glm::vec3 _light = glm::vec3(1.0f);

		std::unique_ptr<Mesh> _mesh;
		
	public:
		Lighting(float r, uint points);

		void draw(std::shared_ptr<Shader> shader);
		glm::vec3 getLight() {return _light;}
		
	};
	
}

#endif
