#include "mesh.h"

namespace POLYGINE {
	
	void Mesh::_define() {
		_oldPoints = _points;
		switch(_type) {
			case ST::POLYGON:
				fan2D(_vertices, _indices, _points);
				_normals = _vertices;
				break;
			case ST::CUBESPHERE:
				genCubeSphere(_vertices, _indices, _points);
				thinVertices(_vertices, _indices);
				_normals = _vertices;
				break;
			default:
				break;
		}
	}
	
	void Mesh::_bind() {
		glBindVertexArray(_VAO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, M_DIM, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);
	}
	
	void Mesh::_normalBind() {
		glBindBuffer(GL_ARRAY_BUFFER, _VNO);
		glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), _normals.data(), GL_STATIC_DRAW);
			
		glVertexAttribPointer(1, M_DIM, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(1);
	}


	Mesh::Mesh(uint points, ST type, bool verbose)
		: _points(points), _type(type) {
		if (_type == ST::CUBESPHERE && _points < 1) _points = 1;
		if (_type == ST::POLYGON && _points < 3) _points = 3;
		if (verbose) {
			cout << "I have " << _points << " points and a ";
			cout << (_type == ST::POLYGON ? "POLYGON shape.\n" : "SPHERECUBE shape.\n");
		}
		
		glGenBuffers(1, &_EBO);
		glGenBuffers(1, &_VBO);
		glGenBuffers(1, &_VNO);
		glGenVertexArrays(1, &_VAO);
	}

	Mesh::~Mesh() {
		glBindVertexArray(0);
	    glDeleteVertexArrays(1, &_VAO);
		glDeleteBuffers(1, &_VNO);
	    glDeleteBuffers(1, &_VBO);
		glDeleteBuffers(1, &_EBO);
	}
	
	void Mesh::update(float &s, glm::vec3 &p, glm::vec3 &o) {
		if (_oldPoints != _points){
			_define();
		}
		
		_modelMat = glm::mat4(1.0f);
		_modelMat = glm::translate(_modelMat, p);
		_modelMat = glm::rotate(_modelMat, glm::radians(o.x), glm::vec3(1.0f, 0.0f, 0.0f));
		_modelMat = glm::rotate(_modelMat, glm::radians(o.y), glm::vec3(0.0f, 1.0f, 0.0f));
        _modelMat = glm::rotate(_modelMat, glm::radians(o.z), glm::vec3(0.0f, 0.0f, 1.0f));
		_modelMat = glm::scale(_modelMat, glm::vec3(s));
 
	}
	
	void Mesh::o_draw(std::shared_ptr<Shader> shader) {
		shader->setVec3("objectColor", _colors);
		shader->setMat4("model", _modelMat);
		
		_bind();
		_normalBind();

		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	}
	
	void Mesh::l_draw(std::shared_ptr<Shader> shader) {
		shader->setMat4("model", _modelMat);
		
		_bind();

		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	}
	
}
