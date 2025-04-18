#pragma once

#include <unordered_set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "mesh.h"

namespace POLY {
    class Sphere : public Mesh {
    private:
        int _divisions;
        float _radius;

        void _sphereVertices() {
            for (int face = 0; face < 6; face++) {
                for (int i = 0; i <= _divisions; i++) {
                    for (int j = 0; j <= _divisions; j++) {
                        float a = (float)i / _divisions;
                        float b = (float)j / _divisions;
    
                        // Calculate vertex position based on face and subdivision
                        glm::vec3 vertex;
                        switch (face) {
                            case 0: // +X face
                                vertex = glm::vec3(1.0f, -1.0f + 2.0f * a, -1.0f + 2.0f * b);
                                break;
                            case 1: // -X face

                                vertex = glm::vec3(-1.0f, -1.0f + 2.0f * a, -1.0f + 2.0f * b);
                                
                                break;
                            case 2: // -Y face
                                vertex = glm::vec3(-1.0f + 2.0f * a, -1.0f, -1.0f + 2.0f * b);
                                break;
                            case 3: // +Y face

                                vertex = glm::vec3(-1.0f + 2.0f * a, 1.0f, -1.0f + 2.0f * b);

                                break;
                            case 4: // +Z face
                                vertex = glm::vec3(-1.0f + 2.0f * a, -1.0f + 2.0f * b, 1.0f);
                                break;
                            case 5: // -Z face

                                vertex = glm::vec3(-1.0f + 2.0f * a, -1.0f + 2.0f * b, -1.0f);

                                break;
                        }
    
                        // Add the normalized, scaled vertex to the list
                        _vertices.push_back(glm::normalize(vertex) * _radius);
    
                        // Add _indices for triangles
                        if (i < _divisions && j < _divisions) {
                            int base = (face * (_divisions + 1) + i) * (_divisions + 1) + j;

                            if (face % 2 == 0) {
                                _indices.push_back(base);
                                _indices.push_back(base + (_divisions + 1));
                                _indices.push_back(base + 1);
                                _indices.push_back(base + (_divisions + 1) + 1);
                                _indices.push_back(base + 1);
                                _indices.push_back(base + (_divisions + 1));
                            } else {
                                _indices.push_back(base);
                                _indices.push_back(base + 1);
                                _indices.push_back(base + (_divisions + 1));
                                
                                _indices.push_back(base + (_divisions + 1) + 1);
                                _indices.push_back(base + (_divisions + 1));
                                _indices.push_back(base + 1);
                                
                            }
                            
                        }
                    }
                }
            }
        }
        
        void _thinVertices() {
            std::unordered_set<glm::vec3> uniqueVerts(_vertices.begin(), _vertices.end());
            
            for (auto &idx : _indices) {
                idx = std::distance(uniqueVerts.begin(), uniqueVerts.find(_vertices[idx]));
            }
            
            _vertices.assign(uniqueVerts.begin(), uniqueVerts.end());
        }
        
        void _sphereNormals() {
            for (const auto& v : _vertices) _normals.push_back(glm::normalize(v));
        }

        public:
        Sphere(glm::vec3 color, int d, float r)
            : Mesh(color), _divisions(d), _radius(r)
        {
            _sphereVertices();
            _thinVertices();
            _sphereNormals();
        }


    };
}