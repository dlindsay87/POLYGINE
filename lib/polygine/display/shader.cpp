#include "shader.h"

namespace POLYGINE {
	
	//vertex shader
	void Shader::_compile_vertex() {
		_vertexShaderSource = "#version 410 core\n"
		    "layout (location = 0) in vec3 aPos;\n"
		    "uniform mat4 _proj;\n"
		    "uniform mat4 _view;\n"
		    "uniform mat4 _model;\n"
		    "void main() {\n"
		    "   gl_Position = _proj * _view * _model * vec4(aPos, 1.0);\n"
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
			"uniform vec3 _color;\n"
			"void main() {\n"
			"	FragColor = vec4(_color, 1.0);\n"
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
		glDeleteShader(_vertexShader);
		glDeleteShader(_fragmentShader);
	}


	void Shader::_establish_matrices() {
		_projLoc = glGetUniformLocation(_shaderProgram, "_proj");
		_viewLoc = glGetUniformLocation(_shaderProgram, "_view");
		_modelLoc = glGetUniformLocation(_shaderProgram, "_model");
		_colorLoc = glGetUniformLocation(_shaderProgram, "_color");
	}
	
	Shader::Shader() {
		_compile_vertex();
		_compile_fragment();
		_link_shader();
		_establish_matrices();

		cout << "Shaders initialized." << endl;
	}
	
	Shader::~Shader() {
	    glDeleteProgram(_shaderProgram);
	}
	
	void Shader::use() {
		glUseProgram(_shaderProgram);
	}
	
    void Shader::setProjectionMatrix(const glm::mat4 &proj) {
        _proj = proj;
        glUniformMatrix4fv(_projLoc, 1, GL_FALSE, glm::value_ptr(_proj));
    }

    void Shader::setViewMatrix(const glm::mat4 &view) {
        _view = view;
        glUniformMatrix4fv(_viewLoc, 1, GL_FALSE, glm::value_ptr(_view));
    }

    void Shader::setModelMatrix(const glm::mat4 &model) {
		_model = model;
        glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
    }
	
	void Shader::setColor(const glm::vec3 &color) {
		_color = color;
		glUniform3fv(_colorLoc, 1, glm::value_ptr(_color));
	}

}
