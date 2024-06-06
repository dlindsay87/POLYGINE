#include "mesh.h"

namespace POLYGINE {

	void Mesh::_bind() {
		glBindVertexArray(_VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(GLfloat), _vertices.data(), GL_STATIC_DRAW);
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(int), _indices.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, M_DIM, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

	}
	
	Mesh::Mesh() {
		//glGenBuffers(1, &_EBO);
		glGenBuffers(1, &_VBO);
		glGenVertexArrays(1, &_VAO);
		
		_colors.x = _uni_dist(mt_engine);
		_colors.y = _uni_dist(mt_engine);
		_colors.z = _uni_dist(mt_engine);
		
		fan2D(_vertices, _points);
		
		_bind();
	}
	
	Mesh::~Mesh() {
		glBindVertexArray(0);
	    glDeleteVertexArrays(1, &_VAO);
	    glDeleteBuffers(1, &_VBO);
	}
	
	void Mesh::update(float &s, cartesian &p, orientation &o) {
		fan2D(_vertices, _points);
		
		_modelMat = glm::mat4(1.0f);
		_modelMat = glm::translate(_modelMat, glm::vec3(p.x, p.y, p.z));
        _modelMat = glm::rotate(_modelMat, glm::radians(o.phi), glm::vec3(0.0f, 0.0f, 1.0f));
		_modelMat = glm::scale(_modelMat, glm::vec3(s, s, s));
 
	}
	
	void Mesh::draw(std::shared_ptr<Shader> shader) {
		shader->use();
		shader->setModelMatrix(_modelMat);
		shader->setColor(_colors); // {1.0, 0.5, 0.2} // fun lil color from the tutorial
		
		_bind();
		
	    glDrawArrays(GL_TRIANGLE_FAN, 0, _points + 2);
	}
	
}