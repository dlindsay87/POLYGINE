#include "lighting.h"

namespace POLYGINE {
	
	void Lighting::_bind() {
		glBindVertexArray(_VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, M_DIM, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
	}
	
	Lighting::Lighting(float r, uint subs)
		: _radius(r), _subdivies(subs) {
			
		_genCubeSphere(_vertices, _indices, _subdivies, _radius);
		_modelMat = glm::translate(_modelMat, glm::vec3(1.2f, 1.0f, 2.0f));
			
		glGenBuffers(1, &_EBO);
		glGenBuffers(1, &_VBO);
		glGenVertexArrays(1, &_VAO);			
		
		_bind();
	}
	
	Lighting::~Lighting() {
		glBindVertexArray(0);
	    glDeleteVertexArrays(1, &_VAO);
	    glDeleteBuffers(1, &_VBO);
		glDeleteBuffers(1, &_EBO);
	}
	
	void Lighting::draw(std::shared_ptr<Shader> shader) {		
		shader->use();
		shader->setMat4("model", _modelMat);
		shader->setVec3("light", _light);

		_bind();

	    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	}
}
