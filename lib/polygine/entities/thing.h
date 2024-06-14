#ifndef THING_H
#define THING_H

#include "core/input.h"
#include "mesh.h"
#include "shapes.h"

namespace POLYGINE {

	class Thing {
	private:
		float _mass, _scale;
		cartesian _position;
		cartesian _velocity;
		orientation _orient;
		
		//std::unique_ptr<Mesh> _mesh;
		std::unique_ptr<Shape> _shape;

	public:
		Thing();
		
		bool isActive = true;
		
		void update(std::shared_ptr<Input> ip);
		void draw(std::shared_ptr<Shader> shader, glm::vec3 light);

		float getMass() {return _mass;}
		float getScale() {return _scale;}
		cartesian getPosition() {return _position;}
		cartesian getVelocity() {return _velocity;}
		orientation getOrientation() {return _orient;}
		
		void setMass(float m) { _mass = m;}
		void setScale(float s) { _scale = s;}
		
		void setPosition(float x, float y, float z) {
			_position = {x, y, z};
		}
		
		void setVelocity(float x, float y, float z) {
			_velocity = {x, y, z};
		}
		
		void setOrientation(float theta, float phi) {
			_orient = {theta, phi};
		}
		
		void accelerate(float x, float y, float z) {
			_velocity.x += x;
			_velocity.y += y;
			_velocity.z += z;
		}

	};

}

#endif
