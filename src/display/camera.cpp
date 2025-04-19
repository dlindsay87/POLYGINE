#include "camera.h"

namespace DISPLAY
{

void Camera::_initUBO()
{
	glGenBuffers(1, &_UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, _UBO);
	glBufferData(GL_UNIFORM_BUFFER,
		     2 * sizeof(glm::mat4) + sizeof(glm::vec3), NULL,
		     GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, _UBO, 0,
			  2 * sizeof(glm::mat4)); // + sizeof(glm::vec3));
}

void Camera::_updateUBO()
{
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4),
			glm::value_ptr(_viewMat));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4),
			glm::value_ptr(_projMat));
	// glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4),
	// sizeof(glm::vec3), glm::value_ptr(_position));
}

void Camera::_swivel(glm::vec3 targPos)
{
	_PRY.x = glm::clamp(_PRY.x, -60.0f, 60.0f);
	UTIL::modVec3(_PRY, M_CIRCLE, M_SEMI);

	_position = targPos - UTIL::getPosFromAng(_camRadius, _PRY);
	_viewMat = glm::lookAt(_position, targPos, _worldUp);
}

void Camera::_zoom(const float &aspectRatio)
{
	_projFactor = 1.0 / tan(glm::radians(_zoomFactor) * 0.5f);

	if (aspectRatio > 1) {
		_projMat[0][0] = _projFactor / aspectRatio;
		_projMat[1][1] = _projFactor;
	} else {
		_projMat[0][0] = _projFactor;
		_projMat[1][1] = _projFactor * aspectRatio;
	}

	_projMat = glm::perspective(glm::radians(_zoomFactor), aspectRatio,
				    0.1f, 100.0f);
}

Camera::Camera(float r, float m, float wh)
    : _camRadius(r), _mouseSensitivity(m), _wheelSensitivity(wh){

					   };

void Camera::init(std::map<std::string, DISPLAY::Shader *> *shaders)
{
	_initUBO();
	for (auto &[name, shader] : *shaders) {
		linkUBOtoShader(shader);
	}
}

Camera::~Camera()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glDeleteBuffers(1, &_UBO);
};

void Camera::linkUBOtoShader(Shader *shader)
{
	GLuint uniformBlockIndex =
	    glGetUniformBlockIndex(shader->ID, "Matrices");
	glUniformBlockBinding(shader->ID, uniformBlockIndex, 0);
}

void Camera::handleEvents(CORE::Input *ip)
{
	_PRY.x -= _mouseSensitivity * ip->getMouseDelta().y;
	_PRY.z -= _mouseSensitivity * ip->getMouseDelta().x;

	static float orad = _camRadius;

	if (ip->isButtonPressed(SDL_BUTTON_MIDDLE)) {
		_camRadius = (_camRadius >= orad * 4 ? orad : _camRadius * 2);
		_zoomFactor = M_45;
	}

	_zoomFactor -= ip->getWheelDelta() * _wheelSensitivity;
	_zoomFactor = glm::clamp(_zoomFactor, 30.0f, 60.0f);
}

void Camera::update(Window *win, glm::vec3 targPos)
{
	_zoom(win->getAspectRatio());
	_swivel(targPos);
	_updateUBO();
};

} // namespace DISPLAY
