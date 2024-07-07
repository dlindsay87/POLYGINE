#ifndef LIGHTING_H
#define LIGHTING_H

#include "core/init.h"
#include "entities/mesh.h"

namespace POLYGINE {
	
	#ifndef NUM_LIGHTS
	#define NUM_LIGHTS 5
	#endif
	
	class Lighting {
	private:
		glm::vec3 _position;
		glm::vec3 _orientation = glm::vec3(0.0f);
		glm::vec3 _lightColor;
		
		float _rad;

		std::unique_ptr<Mesh> _mesh;
		
		std::uniform_real_distribution<float> _pos_dist;
		std::uniform_real_distribution<float> _uni_dist;
		
	public:
		Lighting(uint points);
		
		void resetPosAndCol();

		void draw(std::shared_ptr<Shader> shader);
		
		glm::vec3 getColor() {return _lightColor;}
		glm::vec3 getPosition() {return _position;}
		
	};
	
}

#endif
