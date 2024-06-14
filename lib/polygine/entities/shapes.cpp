#include "shapes.h"

namespace POLYGINE {
	
	void Shape::_bind() {
		glBindVertexArray(_VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, M_DIM, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
	}


	Shape::Shape(float r, uint subs, glm::vec3 col, ST shape) 
		: _radius(r), _subdivies(subs), _colors(col), _type(shape) {
		glGenBuffers(1, &_EBO);
		glGenBuffers(1, &_VBO);
		glGenVertexArrays(1, &_VAO);
		
		if (_type == ST::CUBESPHERE) {
			_genCubeSphere(_vertices, _indices, _subdivies, _radius);
		}

		_bind();
	}
	
	Shape::~Shape() {
		glBindVertexArray(0);
	    glDeleteVertexArrays(1, &_VAO);
	    glDeleteBuffers(1, &_VBO);
		glDeleteBuffers(1, &_EBO);
	}
	
	void Shape::update(float &s, cartesian &p, orientation &o) {
		if (_type == ST::CUBESPHERE) {
			_genCubeSphere(_vertices, _indices, _subdivies, _radius);
		}
		
		_modelMat = glm::mat4(1.0f);
		_modelMat = glm::translate(_modelMat, glm::vec3(p.x, p.y, p.z));
        _modelMat = glm::rotate(_modelMat, glm::radians(o.phi), glm::vec3(0.0f, 0.0f, 1.0f));
		_modelMat = glm::scale(_modelMat, glm::vec3(s));
 
	}
	
	void Shape::draw(std::shared_ptr<Shader> shader, glm::vec3 light) {
		shader->use();
		shader->setMat4("model", _modelMat);
		shader->setVec3("color", _colors);
		shader->setVec3("light", light);
		
		_bind();
		
	    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	}
	
}
