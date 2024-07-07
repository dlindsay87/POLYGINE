#include "lighting.h"

namespace POLYGINE {

	Lighting::Lighting(uint points)
		: _pos_dist(-5.0f, 5.0f) {
		_mesh = std::make_unique<Mesh>(points, ST::CUBESPHERE, false);
		resetPosAndCol();
	}
	
	void Lighting::resetPosAndCol() {
		_position = glm::vec3(
			_pos_dist(mt_engine),
			_pos_dist(mt_engine),
			_pos_dist(mt_engine)
		);
			
		_lightColor = glm::vec3(
			_uni_dist(mt_engine),
			_uni_dist(mt_engine),
			_uni_dist(mt_engine)
		);
			
		_rad = _uni_dist(mt_engine);
		
		_mesh->update(_rad, _position, _orientation);
		_mesh->recolor(_lightColor);
	}
	
	void Lighting::draw(std::shared_ptr<Shader> shader) {
		shader->use();
		shader->setVec3("lightColor", _lightColor);
		_mesh->l_draw(shader);
	}
}
