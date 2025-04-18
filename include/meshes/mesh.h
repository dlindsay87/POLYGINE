#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <glm/gtx/normal.hpp>

#include <vector>

#include "shader.h"

typedef std::vector<GLuint> gluintvec;

namespace POLY {

    class Mesh {
    protected:
        GLuint _VAO, _VBO, _VNO, _EBO;

        std::vector<glm::vec3> _vertices;
		std::vector<glm::vec3> _normals;
		gluintvec _indices;

        glm::mat4 _modelMat;
		glm::vec3 _colors; // Legacy colors {1.0, 0.5, 0.2}

        void _bind() {
            glBindVertexArray(_VAO);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW);
            
            glBindBuffer(GL_ARRAY_BUFFER, _VBO);
            glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);
            
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(0);
        }
	
		void _normalBind() {
            glBindBuffer(GL_ARRAY_BUFFER, _VNO);
            glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), _normals.data(), GL_STATIC_DRAW);
                
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
            glEnableVertexAttribArray(1);
        }

    public:
        Mesh(glm::vec3 color)
            : _modelMat(1.0f), _colors(color)
        
        {
            glGenBuffers(1, &_EBO);
            glGenBuffers(1, &_VBO);
            glGenBuffers(1, &_VNO);
            glGenVertexArrays(1, &_VAO);
        }

        virtual ~Mesh() {
            glBindVertexArray(0);
            glDeleteVertexArrays(1, &_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glDeleteBuffers(1, &_VNO);
            glDeleteBuffers(1, &_VBO);
            glDeleteBuffers(1, &_EBO);
        }

        void update(float s, glm::vec3 p, glm::vec3 o) {
            _modelMat = glm::mat4(1.0f);
            _modelMat = glm::translate(_modelMat, p);
            _modelMat = glm::rotate(_modelMat, glm::radians(o.x), glm::vec3(1.0f, 0.0f, 0.0f));
            _modelMat = glm::rotate(_modelMat, glm::radians(o.y), glm::vec3(0.0f, 1.0f, 0.0f));
            _modelMat = glm::rotate(_modelMat, glm::radians(o.z), glm::vec3(0.0f, 0.0f, 1.0f));
            _modelMat = glm::scale(_modelMat, glm::vec3(s));
        }

        void draw(DISPLAY::Shader* shader) {
            shader->setVec3("objectColor", _colors);
            shader->setMat4("model", _modelMat);
            
            _bind();
            _normalBind();

            glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (void*)0);
        }

        std::pair<glm::mat4, glm::vec3> getModel() {
            return {_modelMat, _colors};
        }

    };

}

#endif
