#include "thing.h"

namespace POLYGINE {
	
	Thing::Thing()
	: _mass(1.0), _scale(1.0), _position(glm::vec3(0.0f)), _orientation(glm::vec3(0.0f)) {
		cout << "\nI am a thing." << endl;
		_mesh = std::make_unique<Mesh>();
	}
	
	Thing::Thing(uint p, ST m)
	: _mass(1.0), _scale(1.0), _position(glm::vec3(0.0f)), _orientation(glm::vec3(0.0f)) {
		cout << "\nI am a thing." << endl;
		_mesh = std::make_unique<Mesh>(p, m);
	}

	void Thing::takeInput(std::shared_ptr<Input> ip) {
        if (ip -> isKeyPressed(SDLK_KP_0) ||
		    ip -> isKeyPressed(SDLK_0)) {
			setScale(1.0);
			setOrientation(0.0f, 0.0f, 0.0f);
			setPosition(0.0f, 0.0f, 0.0f);
        }
		
		for (int i = 0; i < 9; i++) {
			if (ip -> isKeyPressed(SDLK_KP_1 + i) ||
				ip -> isKeyPressed(SDLK_1 + i)) {
				if (!(_mesh->getType() == ST::POLYGON && i + 1 < M_DIM)) {
					_mesh->setPoints(i + 1);
				}
             }
	     }
		
		if (ip -> isKeyPressed(SDLK_f)) {
			_mesh->printVertices();
		}

		if (((SDL_GetModState() & KMOD_SHIFT) &&
			ip -> isKeyDown(SDLK_EQUALS)) ||
			ip -> isKeyDown(SDLK_KP_PLUS)) {
			_scale += 0.05;
		} if (ip -> isKeyDown(SDLK_MINUS) ||
			ip -> isKeyDown(SDLK_KP_MINUS)) {
			_scale -= 0.05;
		}
		
		modVec3(_orientation, M_CIRCLE);
		_scale = glm::clamp(_scale, 0.05f, 100.0f);

		_radYaw = glm::radians(_orientation.z);
		_forward = glm::vec3(sin(_radYaw), cos(_radYaw), 0.0f);
		_right  = glm::vec3(cos(_radYaw), -sin(_radYaw), 0.0f);
			
		if (ip -> isKeyDown(SDLK_UP) || ip -> isKeyDown(SDLK_w)) _position += _forward * 0.1f;
		if (ip -> isKeyDown(SDLK_DOWN) || ip -> isKeyDown(SDLK_s)) _position -= _forward * 0.1f;
		if (ip -> isKeyDown(SDLK_RIGHT) || ip -> isKeyDown(SDLK_d)) _position += _right * 0.1f;
		if (ip -> isKeyDown(SDLK_LEFT) || ip -> isKeyDown(SDLK_a)) _position -= _right * 0.1f;
	}
	
	void Thing::update() {
		_mesh->update(_scale, _position, _orientation);
	}
	
	void Thing::draw(std::shared_ptr<Shader> shader, glm::vec3 light) {
		_mesh->draw(shader, light);
	}

}
