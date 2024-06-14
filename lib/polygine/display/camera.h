#ifndef CAMERA_H
#define CAMERA_H

#include "shader.h"
#include "window.h"
#include "core/input.h"

namespace POLYGINE {
	
	class Camera {
	private:
	    cartesian _position {0.0, 0.0, -5.0};
		float _zoom = 45.0f;
		
	    //glm::vec3 _front;
	    //glm::vec3 _up;
	    //glm::vec3 _right;
	    //glm::vec3 _worldUp;
		
	    //float _yaw;
	    //float _pitch;
		
		glm::mat4 _projMat;
		glm::mat4 _viewMat;
		
	    //float _movementSpeed;
	    //float _mouseSensitivity;
		
	    GLuint _UBO;
		
		void _initUBO();
		
		void _updateUBO();
	public:
		Camera(std::shared_ptr<Window> _window);
		
		~Camera();
		
		void linkUBOtoShaders(std::vector<std::shared_ptr<Shader>> &shaders);
		
		void update(std::shared_ptr<Input> ip, std::shared_ptr<Window> w);
		
		glm::mat4 getViewMatrix() {return _viewMat;};
	    glm::mat4 getProjectionMatrix() {return _projMat;};
		
	};
	
}
#endif
