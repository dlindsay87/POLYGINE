#include "shader.h"

namespace POLYGINE {
	
	//vertex shader
	void Shader::_compile_vertex() {
		_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(_vertexShader, 1, &_vertSource, NULL);
		glCompileShader(_vertexShader);

		glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetShaderInfoLog(_vertexShader, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << _infoLog;
		}
	}

	//fragment shader
	void Shader::_compile_fragment() {
		_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_fragmentShader, 1, &_fragSource, NULL);	
		glCompileShader(_fragmentShader);

		glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetShaderInfoLog(_fragmentShader, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << _infoLog;
		}
	}

	//shader program
	void Shader::_link_shader() {
		ID = glCreateProgram();

		glAttachShader(ID, _vertexShader);
		glAttachShader(ID, _fragmentShader);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &_success);
		if (_success == GL_FALSE) {
		    glGetProgramInfoLog(ID, 512, NULL, _infoLog);
		    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << _infoLog;
		}
		glDeleteShader(_vertexShader);
		glDeleteShader(_fragmentShader);
	}

	Shader::Shader(cc* vPath, cc* fPath) {
		_vertSource = fileReader(vPath);
		_fragSource = fileReader(fPath);
		
		_compile_vertex();
		_compile_fragment();
		_link_shader();
		
		cout << "Shaders initialized." << endl;
	}
	
	Shader::~Shader() {
	    glDeleteProgram(ID);
	    delete[] _vertSource;
        delete[] _fragSource;
	}
	
	void Shader::use() {
		glUseProgram(ID);
	}
	
	void Shader::setMat4(const std::string &name, const glm::mat4 &mat) {
        glUniformMatrix4fv(
			glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)
		);
    }
	
	void Shader::setVec3(const std::string &name, const glm::vec3 &vec) {
        glUniform3fv(
			glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec)
		);
    }

}
