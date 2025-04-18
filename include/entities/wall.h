#pragma once

#include "thing.h"
#include "prism.h"

namespace ENT {
	
	class Wall : public Thing {
	private:
        glm::vec3 _dimensions;
		
	public:
		Wall(glm::vec3 color, glm::vec3 size, glm::vec3 pos)
            : Thing(0.0f, 1.0f, glm::vec3(pos), glm::vec3(0.0f), glm::vec3(0.0f)),
            _dimensions(size)
		{
			_mesh = std::make_unique<POLY::Prism>(color, size);
		}
	};
	
}