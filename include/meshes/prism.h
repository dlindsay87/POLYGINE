#pragma once

#include "mesh.h"

namespace POLY {
    class Prism : public Mesh {
    private:
        // width, length, height
        glm::vec3 _dimensions;

        void _generatePrism() {
            float x0 = -_dimensions.x / 2.0f;
            float x1 = _dimensions.x / 2.0f;
            float y0 = 0.0f;
            float y1 = _dimensions.y;
            float z0 = 0.0f;
            float z1 = _dimensions.z;
        
            // The four vertices v0, v1, v2, v3 should be specified in order (clockwise or counter-clockwise)
            auto addFace = [this](glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
                GLuint startIndex = _vertices.size();

                _vertices.insert(_vertices.end(), {v0, v1, v2, v2, v3, v0});
                for (GLuint i = startIndex; i < startIndex + 6; i++) _indices.push_back(i);

            };
        
            // Front face (z=z1)
            addFace(glm::vec3(x0, y0, z1), glm::vec3(x1, y0, z1),
                    glm::vec3(x1, y1, z1), glm::vec3(x0, y1, z1));
        
            // Back face (z=z0) -- note winding order is reversed to have the normal point outward.
            addFace(glm::vec3(x1, y0, z0), glm::vec3(x0, y0, z0),
                    glm::vec3(x0, y1, z0), glm::vec3(x1, y1, z0));
        
            // Left face (x=x0)
            addFace(glm::vec3(x0, y0, z0), glm::vec3(x0, y0, z1),
                    glm::vec3(x0, y1, z1), glm::vec3(x0, y1, z0));
        
            // Right face (x=x1)
            addFace(glm::vec3(x1, y0, z1), glm::vec3(x1, y0, z0),
                    glm::vec3(x1, y1, z0), glm::vec3(x1, y1, z1));
        
            // Top face (y=y1)
            addFace(glm::vec3(x0, y1, z1), glm::vec3(x1, y1, z1),
                    glm::vec3(x1, y1, z0), glm::vec3(x0, y1, z0));
        
            // Bottom face (y=y0)
            addFace(glm::vec3(x0, y0, z0), glm::vec3(x1, y0, z0),
                    glm::vec3(x1, y0, z1), glm::vec3(x0, y0, z1));
        
            // Generate normals for each triangle for flat shading.
            for (GLuint i = 0; i < _indices.size(); i += 3) {
                glm::vec3 normal = glm::triangleNormal(
                    _vertices[_indices[i]],
                    _vertices[_indices[i + 1]],
                    _vertices[_indices[i + 2]]
                );

                _normals.insert(_normals.end(), {normal, normal, normal});
            }
        }

        public:
        Prism(glm::vec3 color, glm::vec3 size)
            : Mesh(color), _dimensions(size)
        {
            _generatePrism();
        }


    };
}