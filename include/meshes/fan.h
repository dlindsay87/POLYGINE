#pragma once

#include "mesh.h"

namespace POLY {
    class Fan : public Mesh {
    private:
        int _points;
        float _radius;
        float _offset;

        void _fanVertices() {
            float angle = 0.0f;
            _vertices.push_back({0.0f, _offset, 0.0f});

            for (int i = 0; i < _points; i++) {
                _vertices.push_back(glm::vec3(sin(angle), 0.0f, cos(angle)) * _radius);

                _indices.push_back(0);
                _indices.push_back(i + 1);
                _indices.push_back(i + 1 != _points ? i + 2 : 1);
                
                angle += (float)(2 * M_PI / _points);
            }

        }

        void _fanNormals() {
            for (size_t i = 0; i < _indices.size(); i += 3) {
                glm::vec3 normal = glm::triangleNormal(
                    _vertices[_indices[i]],
                    _vertices[_indices[i + 1]],
                    _vertices[_indices[i + 2]]
                );

                _normals.insert(_normals.end(), {normal, normal, normal});
            }
        }
    
    public:
        Fan(glm::vec3 color, int p, float r, float offset=0.5f)
            : Mesh(color), _points(p), _radius(r), _offset(offset)
        {
            _fanVertices();
            _fanNormals();
            
        }

    };
}