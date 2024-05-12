#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include "utils/typer.h"

namespace POLYGINE {
	
	class Shader {
	private:
		GLint  _success;
		GLchar _infoLog[512];

		GLfloat _vertices[9] {
			-0.5, -0.5, 0.0,
			 0.5, -0.5, 0.0,
			 0.0,  0.5, 0.0
		};

		GLuint _VBO;
		GLuint _VAO;

		cc *_vertexShaderSource;
		GLuint _vertexShader;

		cc *_fragmentShaderSource;
		GLuint _fragmentShader;

		GLuint _shaderProgram;
		
		void _compile_vertex();
		void _compile_fragment();
		void _link_shader();
		
	public:
		~Shader();
		
		void init();	
		void draw();	
		
	};
	
}

#endif
