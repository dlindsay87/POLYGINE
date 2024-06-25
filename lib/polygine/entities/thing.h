#ifndef THING_H
#define THING_H

#include "core/input.h"
#include "mesh.h"

namespace POLYGINE {

	class Thing {
	private:
		float _mass, _scale;
		glm::vec3 _position;
		glm::vec3 _orientation;
		
		glm::vec3 _forward;
		glm::vec3 _right;
		float _radYaw, _camYaw;
		
		std::unique_ptr<Mesh> _mesh;

	public:
		Thing();
		Thing(uint p, ST m);

		void takeInput(std::shared_ptr<Input> ip);
		void update();
		void draw(std::shared_ptr<Shader> shader, glm::vec3 light);

		float getMass() {return _mass;}
		float getScale() {return _scale;}
		glm::vec3 getPosition() {return _position;}
		glm::vec3 getOrientation() {return _orientation;}
		
		void setMass(float m) {_mass = m;}
		void setScale(float s) {_scale = s;}
		
		void setCamYaw(float f) {_camYaw = f;}
		
		void setPosition(glm::vec3 &p) {_position = p;}
		void setPosition(float x, float y, float z) {
			_position.x = x;
			_position.y = y;
			_position.z = z;
		}
		
		void setOrientation(glm::vec3 &o) {_orientation = o;}
		void setOrientation(float pitch, float roll, float yaw) {
			_orientation.x = pitch;
			_orientation.y = roll;
			_orientation.z = yaw;
		}
		
	};

}

#endif
