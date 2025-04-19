#pragma once

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "mesh.h"

#include "lighting.h"
#include "window.h"

namespace ENT
{
class Thing
{
      protected:
	float _mass, _scale;
	glm::vec3 _position;
	glm::vec3 _velocity;
	glm::vec3 _orientation;

	std::unique_ptr<POLY::Mesh> _mesh;

      public:
	Thing(float m, float s, glm::vec3 p, glm::vec3 v, glm::vec3 o)
	    : _mass(m), _scale(s), _position(p), _velocity(v), _orientation(o)
	{
	}

	virtual ~Thing() {}

	virtual void handleEvents(CORE::Input *ip) {}

	void update() { _mesh->update(_scale, _position, _orientation); }

	void draw(DISPLAY::Shader *shader, DISPLAY::Light *light,
		  DISPLAY::Window *window, glm::vec3 camPos)
	{
		shader->use();

		shader->setVec3("bgc", window->getBGC());
		shader->setVec3("lightColor", light->getColor());
		shader->setVec3("lightPos", light->getPosition());
		shader->setVec3("camPos", camPos);

		_mesh->draw(shader);
	}

	void reflect(DISPLAY::Shader *shader, DISPLAY::Light *light,
		     DISPLAY::Window *window, POLY::Mesh *mesh)
	{
		shader->use();

		shader->setVec3("bgc", window->getBGC());
		shader->setVec3("lightColor", light->getColor());
		shader->setVec3("lightPos", light->getPosition());
		shader->setMat4("objReflectModel", mesh->getModel().first);
		shader->setVec3("objReflectColor", mesh->getModel().second);

		_mesh->draw(shader);
	}

	void setMass(float m) { _mass = m; }
	const float getMass() const { return _mass; }

	void setScale(float s) { _scale = s; }
	const float getScale() const { return _scale; }

	void setPosition(glm::vec3 p) { _position = p; }
	void adjPosition(glm::vec3 v) { _position += v; }
	const glm::vec3 getPosition() const { return _position; }

	void setVelocity(glm::vec3 v) { _velocity = v; }
	void adjVelocity(glm::vec3 a) { _velocity += a; }
	const glm::vec3 getVelocity() const { return _velocity; }

	void setOrientation(glm::vec3 o) { _orientation = o; }
	void adjOrientation(glm::vec3 o) { _orientation += o; }
	const glm::vec3 getOrientation() const { return _orientation; }

	POLY::Mesh *getMesh() { return _mesh.get(); }
};

} // namespace ENT