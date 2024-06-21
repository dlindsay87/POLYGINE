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
		
		void Camera::_swivel() {
			_PRY.x = glm::clamp(_PRY.x, -60.0f, 60.0f);
			modByComponent(_PRY.y, M_CIRCLE);
			modByComponent(_PRY.z, M_CIRCLE);
			_targPos = (_targ ? _targPos = _targ->getPosition() : glm::vec3(0.0f));
			_position = _targPos - getPosFromAng(5.0, _PRY);
			_viewMat = glm::lookAt(_position, _targPos, _worldUp);
			
			if (_targ) {
				_targOri = _targ->getOrientation();
				_targ->setOrientation(_targOri.x, _targOri.y, _PRY.z);
			}	
		}
		
		void Camera::_zoom() {
			_zoomFactor = glm::clamp(_zoomFactor, 7.5f, 120.0f);
			_projFactor = 1.0 / tan(glm::radians(_zoomFactor) * 0.5f);
			
			if (_win->getAspectRatio() > 1) {
				_projMat[0][0] = _projFactor / _win->getAspectRatio();
				_projMat[1][1] = _projFactor;
			} else {
				_projMat[0][0] = _projFactor;
				_projMat[1][1] = _projFactor * _win->getAspectRatio();
			}
		}
		
		Camera::Camera(std::shared_ptr<Window> w)
			: _win(w) {
			_viewMat = glm::lookAt(_position, _targPos, _worldUp);
			_projMat = glm::perspective(glm::radians(_zoomFactor), _win->getAspectRatio(), 0.1f, 100.0f);
			_initUBO();
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
		
		void Camera::takeInput(std::shared_ptr<Input> ip) {
			_PRY += ip->getMotion() * _mouseSensitivity;
			_zoomFactor += ip->getWheel() * _wheelSensitivity;
		}
		
		void Camera::update() {
			_swivel();
			_zoom();
			_updateUBO();
		};
		
}

