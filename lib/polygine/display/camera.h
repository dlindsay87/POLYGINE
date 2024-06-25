#ifndef CAMERA_H
#define CAMERA_H

#include "entities/thing.h"
#include "shader.h"
#include "window.h"
#include "core/input.h"

namespace POLYGINE {
	
	class Camera {
	private:
	    glm::vec3 _position, _targPos;
		glm::vec3 _worldUp = glm::vec3(0.0f, 0.0f, 1.0f);
	    glm::vec3 _PRY = glm::vec3(0.0f);
		
		std::shared_ptr<Window> _win;
		std::shared_ptr<Thing> _targ;

		float _zoomFactor = M_45;
		float _projFactor;
		float _camRadius;

		glm::mat4 _projMat;
		glm::mat4 _viewMat;

	    float _mouseSensitivity;
		float _wheelSensitivity;
		
	    GLuint _UBO;
		
		void _initUBO();
		void _updateUBO();
		
		void _swivel();
		void _zoom();
		
	public:
		Camera(std::shared_ptr<Window> w, float r = 5.0, float m = 0.5, float wh = 1.0);
		~Camera();

		void linkUBOtoShaders(std::vector<std::shared_ptr<Shader>> &shaders);
		
		void setTarget(std::shared_ptr<Thing> t) {_targ = t;}
		
		void takeInput(std::shared_ptr<Input> ip);
		void update();
		
	};
	
}
#endif
