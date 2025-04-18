#include "input.h"

namespace CORE {

    void Input::update() {
        _previousKeyMap = _keyMap;
        _previousMouseMap = _mouseMap;
        _dMouse = {0, 0};
        _dWheel = 0.0f;
        _winAdj = false;
    }

    void Input::handleEvents(SDL_Event *event) {
        switch (event->type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                _keyMap[event->key.keysym.scancode] = (event->type == SDL_KEYDOWN);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                _mouseMap[event->button.button] = (event->type == SDL_MOUSEBUTTONDOWN);
                break;
            case SDL_MOUSEMOTION:
                _mousePos = glm::ivec2(event->motion.x, event->motion.y);
                _dMouse = glm::ivec2(event->motion.xrel, event->motion.yrel);
                break;
            case SDL_MOUSEWHEEL:
                _dWheel = event->wheel.preciseY;
                break;
            case SDL_WINDOWEVENT:
                if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
                    event->window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    _winAdj = true;
                }
                break;
            case SDL_QUIT:
                _exit = true;
                break;
        }
    }

    bool Input::isKeyDown(unsigned int scancode) const {
        return _keyMap[scancode];
    }

    bool Input::isKeyPressed(unsigned int scancode) const {
        return _keyMap[scancode] && !_previousKeyMap[scancode];
    }

    bool Input::isButtonDown(unsigned int buttonID) const {
        return _mouseMap[buttonID];
    }

    bool Input::isButtonPressed(unsigned int buttonID) const {
        return _mouseMap[buttonID] && !_previousMouseMap[buttonID];
    }
}
