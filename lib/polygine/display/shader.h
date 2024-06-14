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
		
		void _compile_vertex();
		void _compile_fragment();
		void _link_shader();
		void _establish_matrices();
		
	public:
		Shader(cc* vPath, cc* fPath);
		~Shader();
		
		GLuint ID;

		void use();
		
		void setMat4(const std::string &name, const glm::mat4 &mat);
		void setVec3(const std::string &name, const glm::vec3 &vec);

	};
	
}

#endif
