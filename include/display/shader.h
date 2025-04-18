#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <iostream>
#include <string>

#include "iomanager.h"

typedef std::string str;

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

namespace DISPLAY {

	class Shader {
	private:
		GLint  _success;
		GLchar _infoLog[512];
		
		const GLchar* _vertSource;
		GLuint _vertexShader;
		
		const GLchar* _fragSource;
		GLuint _fragmentShader;
		
		std::unordered_map<str, int> _uniformLocationCache;
		
		void _compile_vertex();
		void _compile_fragment();
		void _link_shader();
		
	public:
		Shader(const char* vPath, const char* fPath);
		~Shader();

		GLuint ID;

		void testFrag(const GLchar* fragInfo);

		void reloadFrag(const char* fPath);

		void use();
		
		int getUniformLocation(const str& name);

		void setFloat(const str& name, const float& mat);
		
		void setMat4(const str& name, const glm::mat4& mat);
		void setVec3(const str& name, const glm::vec3& vec);
		
		void setVec3Array(const str& name, const glm::vec3 (&v)[5]);

	};
	
}

#endif
