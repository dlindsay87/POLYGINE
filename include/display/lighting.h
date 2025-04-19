#ifndef LIGHTING_H
#define LIGHTING_H

#include <glm/glm.hpp>
#include <memory>

#include "sphere.h"

namespace DISPLAY
{

class Light
{
      private:
	glm::vec3 _position;
	glm::vec3 _objColor;
	glm::vec3 _lightColor;

	std::unique_ptr<POLY::Mesh> _mesh;

      public:
	void init(glm::vec3 p = {0.0f, -2.0f, 4.0f},
		  glm::vec3 mesh_c = {0.1f, 0.4, 0.15f},
		  glm::vec3 light_c = glm::vec3(1.0f))
	{
		_position = p;
		_objColor = mesh_c;
		_lightColor = light_c;
		_mesh = std::make_unique<POLY::Sphere>(_objColor, 1, 0.4f);
		_mesh->update(1.0, _position, {0.0f, 0.0f, 0.0f});
	}

	void draw(Shader *shader)
	{
		shader->use();
		shader->setVec3("lightColor", _lightColor);
		_mesh->draw(shader);
	}

	const glm::vec3 &getColor() const { return _lightColor; }
	const glm::vec3 &getPosition() const { return _position; }
};

} // namespace DISPLAY

#endif
