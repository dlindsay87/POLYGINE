#ifndef CAMERA_H
#define CAMERA_H

#include "entities/thing.h"
#include "shader.h"
#include "window.h"
#include "core/input.h"

namespace POLYGINE {
	
	class Camera {
	private:
	    glm::vec3 _position = glm::vec3(0.0f, -5.0f, 0.0f);
		glm::vec3 _targPos = glm::vec3(0.0f);
		glm::vec3 _targOri = glm::vec3(0.0f);
		glm::vec3 _worldUp = glm::vec3(0.0f, 0.0f, 1.0f);

		float _zoomFactor = 45.0f;
		float _projFactor;
		
		std::shared_ptr<Window> _win;
		std::shared_ptr<Thing> _targ;

	    glm::vec3 _PRY = glm::vec3(0.0f);

		glm::mat4 _projMat;
		glm::mat4 _viewMat;

	    float _mouseSensitivity = 0.5;
		float _wheelSensitivity = 1.0;
		
	    GLuint _UBO;
		
		void _initUBO();
		void _updateUBO();
		
		void _swivel();
		void _zoom();
		
	public:
		Camera(std::shared_ptr<Window> window);
		~Camera();

		void linkUBOtoShaders(std::vector<std::shared_ptr<Shader>> &shaders);
		
		void setTarget(std::shared_ptr<Thing> t) {
			_targ = t;
			if (_targ) _PRY = _targ->getOrientation();
			else _targPos = glm::vec3(0.0f);
		}
		
		void takeInput( std::shared_ptr<Input> ip);
		void update();
		
	};
	
}
#endif
