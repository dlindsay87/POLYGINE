#include "lighting.h"

namespace POLYGINE {

	Lighting::Lighting(float r, uint points) {
		_mesh = std::make_unique<Mesh>(points, ST::CUBESPHERE);
		_mesh->update(r, _position, _orientation);
	}

	void Lighting::draw(std::shared_ptr<Shader> shader) {		
		_mesh->draw(shader, _light);
	}
}
