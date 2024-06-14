#include "camera.h"

namespace POLYGINE {
	
		void Camera::_initUBO() {
	        glGenBuffers(1, &_UBO);
	        glBindBuffer(GL_UNIFORM_BUFFER, _UBO);
	        glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	        glBindBufferRange(GL_UNIFORM_BUFFER, 0, _UBO, 0, 2 * sizeof(glm::mat4));
	    }
		
		void Camera::_updateUBO() {
	        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(_viewMat));
	        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(_projMat));
	    }
		
		Camera::Camera(std::shared_ptr<Window> w) {
			_initUBO();
			_projMat = glm::perspective(glm::radians(_zoom), w->getAspectRatio(), 0.1f, 10.0f);
			_viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, _position.y, _position.z));
		};
		
		Camera::~Camera() {
	        glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glDeleteBuffers(1, &_UBO);
		};
		
		void Camera::linkUBOtoShaders(std::vector<std::shared_ptr<Shader>> &shaders) {
	        for (const auto &shader : shaders) {
				GLuint uniformBlockIndex = glGetUniformBlockIndex(shader->ID, "Matrices");
	            glUniformBlockBinding(shader->ID, uniformBlockIndex, 0);
			}
			_updateUBO();
        }
		
		void Camera::update(std::shared_ptr<Input> ip, std::shared_ptr<Window> w) {
			static float f = 1.0 / tan(glm::radians(_zoom) * 0.5f);
			
			if (w->getAspectRatio() > 1) {
				_projMat[0][0] =  f / w->getAspectRatio();
				_projMat[1][1] = f;
			} else {
				_projMat[0][0] = f;
				_projMat[1][1] = f * w->getAspectRatio();
			}
			
			if (ip -> isKeyDown(SDLK_w)) _position.y -= 0.1;
			if (ip -> isKeyDown(SDLK_s)) _position.y += 0.1;
			if (ip -> isKeyDown(SDLK_d)) _position.x -= 0.1;
			if (ip -> isKeyDown(SDLK_a)) _position.x += 0.1;
			
			_viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, _position.y, _position.z));
				
			_updateUBO();
		};
		
}

