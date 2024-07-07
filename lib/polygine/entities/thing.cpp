#include "thing.h"

namespace POLYGINE {
	
	Thing::Thing()
	: _mass(1.0), _scale(1.0), _position(glm::vec3(0.0f)), _orientation(glm::vec3(0.0f)) {
		uint points = (uint)(_thing_dist(mt_engine) * 10);
		ST type = _thing_dist(mt_engine) < 0.5 ? ST::POLYGON : ST::CUBESPHERE;
		
		glm::vec3 colors = glm::vec3(
			_thing_dist(mt_engine),
			_thing_dist(mt_engine),
			_thing_dist(mt_engine)
		);
		
		cout << "\nI am a thing." << endl;
		_mesh = std::make_unique<Mesh>(points, type);
		_mesh->recolor(colors);
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
		
		if (ip -> isKeyPressed(SDLK_m)) {
			_mesh->printVertices();
		}
		if (ip -> isKeyPressed(SDLK_n)) {
			_mesh->printNormals();
		}
		if (ip -> isKeyPressed(SDLK_i)) {
			_mesh->printIndices();
		}

		if (((SDL_GetModState() & KMOD_SHIFT) &&
			ip -> isKeyDown(SDLK_EQUALS)) ||
			ip -> isKeyDown(SDLK_KP_PLUS)) {
			_scale += 0.05;
		} if (ip -> isKeyDown(SDLK_MINUS) ||
			ip -> isKeyDown(SDLK_KP_MINUS)) {
			_scale -= 0.05;
		}
		
		modVec3(_orientation, M_CIRCLE, M_SEMI);
		_scale = glm::clamp(_scale, 0.05f, 100.0f);

		_radYaw = glm::radians(_camYaw);
		_forward = glm::vec3(-sin(_radYaw), cos(_radYaw), 0.0f);
		_right  = glm::vec3(cos(_radYaw), sin(_radYaw), 0.0f);
			
		if (ip -> isKeyDown(SDLK_UP) || ip -> isKeyDown(SDLK_w)) {
			circleTweenScalar(_orientation.z, _camYaw);
			_position += _forward * 0.1f;
		}
		if (ip -> isKeyDown(SDLK_DOWN) || ip -> isKeyDown(SDLK_s)) {
			circleTweenScalar(_orientation.z, _camYaw + M_SEMI);
			_position -= _forward * 0.1f;
		}
		if (ip -> isKeyDown(SDLK_RIGHT) || ip -> isKeyDown(SDLK_d)) {
	        if (std::abs(_camYaw - _orientation.z) > M_90) {
	            circleTweenScalar(_orientation.z, _camYaw + M_SEMI);
	        } else circleTweenScalar(_orientation.z, _camYaw);

			_position += _right * 0.1f;
		}
		if (ip -> isKeyDown(SDLK_LEFT) || ip -> isKeyDown(SDLK_a)) {
	        if (std::abs(_camYaw - _orientation.z) > M_90) {
	            circleTweenScalar(_orientation.z, _camYaw + M_SEMI);
	        } else circleTweenScalar(_orientation.z, _camYaw);
			
			_position -= _right * 0.1f;
		}
	}
	
	void Thing::update() {
		_mesh->update(_scale, _position, _orientation);
	}
	
	void Thing::draw(std::shared_ptr<Shader> shader, std::vector<std::shared_ptr<Lighting>> lights, glm::vec3 bgc) {
		glm::vec3 nearLightColors[NUM_LIGHTS];
		glm::vec3 nearLightPositions[NUM_LIGHTS];

		for (int i = 0; i < NUM_LIGHTS; i++) {
			nearLightColors[i] = lights[i]->getColor();
			nearLightPositions[i] = lights[i]->getPosition();
		}
		
		shader->use();
		shader->setVec3("bgc", bgc);
		shader->setVec3Array("lightColors", nearLightColors);
		shader->setVec3Array("lightPositions", nearLightPositions);

		_mesh->o_draw(shader);
	}

}
