#pragma once

#include "thing.h"
#include "input.h"
#include "camera.h"
#include "radialmath.h"
#include "sphere.h"

namespace ENT {


    class Player : public Thing {
    protected:
        float _inc = 0.1f;
        glm::vec3 _face = {0.0f, 1.0f, 0.0f};
        glm::vec3 _shoulder = {1.0f, 0.0f, 0.0f};

        float _yaw = 0.0f;

    public:
        Player()
            : Thing(0.0f, 1.0f, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f))
        {
            
        }

        void init(glm::vec3 color, int divs, float rad) {
            _mesh = std::make_unique<POLY::Sphere>(color, divs, rad);
        }

        void handleEvents(CORE::Input* ip) override {

            if (ip -> isKeyDown(SDL_SCANCODE_UP) || ip -> isKeyDown(SDL_SCANCODE_W)) {
                tweenRotation(false);
                _position += _inc * _face;
            }
            if (ip -> isKeyDown(SDL_SCANCODE_DOWN) || ip -> isKeyDown(SDL_SCANCODE_S)) {
                tweenRotation(true);
                _position -= _inc * _face;
            }
            if (ip -> isKeyDown(SDL_SCANCODE_RIGHT) || ip -> isKeyDown(SDL_SCANCODE_D)) {
                tweenRotation(std::abs(_yaw * M_RAD2DEG - _orientation.z) > M_90);
                _position += _inc * _shoulder;
            }
            if (ip -> isKeyDown(SDL_SCANCODE_LEFT) || ip -> isKeyDown(SDL_SCANCODE_A)) {
                tweenRotation(std::abs(_yaw * M_RAD2DEG  - _orientation.z) > M_90);
                _position -= _inc * _shoulder;
            }
            if (ip -> isKeyDown(SDL_SCANCODE_SPACE)) {
                _position.z = 2.0f;
            }
        }

        void update(glm::vec3 camPRY) {
            _yaw = camPRY.z * M_DEG2RAD;
            _face = glm::vec3(-sin(_yaw), cos(_yaw), 0.0f);
            _shoulder  = glm::vec3(cos(_yaw), sin(_yaw), 0.0f);

            if (_position.z > 0.0f) _position.z -= 0.1f;
            else _position.z = 0.0f;

            UTIL::modVec3(_orientation, M_CIRCLE, M_SEMI);

            Thing::update();
        }

        void tweenRotation(bool flip, float inc = 6.0f) {
            // turn in the shortest distance
            float goal = _yaw * M_RAD2DEG;
            if (flip) goal += M_SEMI;
            float direction = goal - _orientation.z;
            
            UTIL::modScalar(direction, M_CIRCLE, M_SEMI);

            if (std::abs(direction) <= inc) _orientation.z = goal;
            else _orientation.z += std::copysign(inc, direction);
        }
    };
}