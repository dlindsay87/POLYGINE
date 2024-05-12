#include "shader.h"

namespace POLYGINE {
	
	//vertex shader
	void Shader::_compile_vertex() {
		_vertexShaderSource = "#version 410 core\n"
		    "layout (location = 0) in vec3 aPos;\n"
		    "void main() {\n"
		    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		    "}\0";

		_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(_vertexShader, 1, (const GLchar **)&_vertexShaderSource, NULL);
		glCompileShader(_vertexShader);

		glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetShaderInfoLog(_vertexShader, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << _infoLog << std::endl;
		}
	}

	//fragment shader
	void Shader::_compile_fragment() {
		_fragmentShaderSource = "#version 410 core\n"
			"out vec4 FragColor;\n"
			"void main() {\n"
			"	FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
			"}\0";

		_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_fragmentShader, 1, (const GLchar **)&_fragmentShaderSource, NULL);
		glCompileShader(_fragmentShader);

		glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetShaderInfoLog(_fragmentShader, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << _infoLog << std::endl;
		}
	}

	//shader program
	void Shader::_link_shader() {
		_shaderProgram = glCreateProgram();

		glAttachShader(_shaderProgram, _vertexShader);
		glAttachShader(_shaderProgram, _fragmentShader);
		glLinkProgram(_shaderProgram);

		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetProgramInfoLog(_shaderProgram, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << _infoLog << std::endl;
		}
	}

	Shader::~Shader() {
		glDeleteShader(_vertexShader);
		glDeleteShader(_fragmentShader);  
	}
	
	void Shader::init() {
		glGenBuffers(1, &_VBO);
		glGenVertexArrays(1, &_VAO);
		
		_compile_vertex();
		_compile_fragment();
		_link_shader();
		
		glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void Shader::draw() {
		glUseProgram(_shaderProgram);
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	

}
