#ifndef CAMERA_H
#define CAMERA_H

#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "input.h"
#include "radialmath.h"
#include "shader.h"
#include "thing.h"
#include "window.h"

namespace DISPLAY
{

class Camera
{
      private:
	glm::vec3 _position;
	glm::vec3 _worldUp = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 _PRY = glm::vec3(0.0f);

	float _zoomFactor = 45.0f;
	float _projFactor;
	float _camRadius;

	glm::mat4 _projMat;
	glm::mat4 _viewMat;

	float _mouseSensitivity;
	float _wheelSensitivity;

	GLuint _UBO;

	void _initUBO();
	void _updateUBO();

	void _swivel(glm::vec3 targPos);
	void _zoom(const float &aspectRatio);

      public:
	Camera(float r = 5.0, float m = 0.5, float wh = 1.5);
	~Camera();

	void init(std::map<std::string, DISPLAY::Shader *> *shaders);

	void linkUBOtoShader(Shader *shader);

	void handleEvents(CORE::Input *ip);

	void update(Window *win, glm::vec3 targPos);

	const glm::vec3 getPos() const { return _position; }
	const glm::vec3 getPRY() const { return _PRY; }
};

} // namespace DISPLAY
#endif
