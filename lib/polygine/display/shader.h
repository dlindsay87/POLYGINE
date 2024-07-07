#ifndef SHADER_H
#define SHADER_H

#include "utils/iomanager.h"
#include "utils/rad.h"

namespace POLYGINE {

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
		void _establish_matrices();
		
	public:
		Shader(cc* vPath, cc* fPath);
		~Shader();
		
		GLuint ID;

		void use();
		
		int getUniformLocation(const str &name);
		
		void setMat4(const str &name, const glm::mat4 &mat);
		void setVec3(const str &name, const glm::vec3 &vec);
		
		void setVec3Array(const str &name, const glm::vec3 (&v)[5]);

	};
	
}

#endif
