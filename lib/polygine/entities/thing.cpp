#include "thing.h"

namespace POLYGINE {
	
	Thing::Thing()
		: _mass(1.0), _scale(1.0), _position({0.0, 0.0, 0.0}), _velocity({0.0, 0.0, 0.0}), _orient({0.0, 0.0}) {
		cout << "\nI am a thing." << endl;
		_mesh = std::make_unique<Mesh>();
	}

	void Thing::update(std::shared_ptr<Input> ip) {
		if (isActive) {
			if (ip -> isKeyPressed(SDLK_f)) {
				_mesh->printVertices();
			}
			
	        if (ip -> isKeyPressed(SDLK_KP_0) ||
			    ip -> isKeyPressed(SDLK_0)) {
				_scale = 1.0;
				_orient = {0.0, 0.0};
				_position = {0.0, 0.0, 0.0};
	        }	
		
			for (int i = M_DIM; i <= 9; i++) {
				if (ip -> isKeyPressed(SDLK_KP_3 + i - M_DIM) ||
					ip -> isKeyPressed(SDLK_3 + i - M_DIM)) {
					_mesh->setPoints(i);
	             }
		     }
	
			if (((SDL_GetModState() & KMOD_SHIFT) &&
				ip -> isKeyDown(SDLK_EQUALS)) ||
				ip -> isKeyDown(SDLK_KP_PLUS)) {
				_scale += 0.05;
			} if (ip -> isKeyDown(SDLK_MINUS) ||
				ip -> isKeyDown(SDLK_KP_MINUS)) {
				_scale -= 0.05;
			}
		
			if (ip -> isKeyDown(SDLK_q)) {
				_orient.phi += 6.0;
			} if (ip -> isKeyDown(SDLK_e)) {
				_orient.phi -= 6.0;
			}
		
			if (ip -> isKeyDown(SDLK_UP) ||
				ip -> isKeyDown(SDLK_w)) {
				_position.y += 0.1;
			} if (ip -> isKeyDown(SDLK_DOWN) ||
				ip -> isKeyDown(SDLK_s)) {
				_position.y -= 0.1;
			} if (ip -> isKeyDown(SDLK_RIGHT) ||
				ip -> isKeyDown(SDLK_d)) {
				_position.x += 0.1;
			} if (ip -> isKeyDown(SDLK_LEFT) ||
				ip -> isKeyDown(SDLK_a)) {
				_position.x -= 0.1;
			}
			_mesh->update(_scale, _position, _orient);
		}
	}
	
	void Thing::draw(std::shared_ptr<Shader> shader) {
		_mesh->draw(shader);
	}

}
