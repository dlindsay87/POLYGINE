#ifndef SHADER_H
#define SHADER_H

#include "utils/typer.h"
#include "utils/rad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace POLYGINE {

	class Shader {
	private:
		GLint  _success;
		GLchar _infoLog[512];
		
		cc *_vertexShaderSource;
		GLuint _vertexShader;
		
		cc *_fragmentShaderSource;
		GLuint _fragmentShader;

		GLuint _shaderProgram;
		
	    glm::mat4 _proj;
	    glm::mat4 _view;
	    glm::mat4 _model;
		glm::vec3 _color;

	    GLuint _projLoc;
	    GLuint _viewLoc;
	    GLuint _modelLoc;
		GLuint _colorLoc;
		
		void _compile_vertex();
		void _compile_fragment();
		void _link_shader();
		void _establish_matrices();
		
	public:
		Shader();
		~Shader();

		void use();
		
	    void setProjectionMatrix(const glm::mat4 &proj);
	    void setViewMatrix(const glm::mat4 &view);
	    void setModelMatrix(const glm::mat4 &model);
		void setColor(const glm::vec3 &color);
		
	};
	
}

#endif
