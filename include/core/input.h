#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <array>
#include <iostream>

namespace CORE {

    class Input {
    private:
        std::array<bool, SDL_NUM_SCANCODES> _keyMap{};
        std::array<bool, SDL_NUM_SCANCODES> _previousKeyMap{};

        std::array<bool, SDL_BUTTON_X2 + 1> _mouseMap{};
        std::array<bool, SDL_BUTTON_X2 + 1> _previousMouseMap{};

        glm::ivec2 _mousePos{0, 0};
        glm::ivec2 _dMouse{0, 0};

        
        float _dWheel = 0.0f;
        bool _winAdj = false;
        bool _exit = false;

        SDL_Event _event;

    public:
        void update();

        void handleEvents(SDL_Event *event);

        bool isKeyDown(unsigned int scancode) const;

        bool isKeyPressed(unsigned int scancode) const;

        bool isButtonDown(unsigned int buttonID) const;

        bool isButtonPressed(unsigned int buttonID) const;

        glm::ivec2 getMousePosition() const { return _mousePos; }
        glm::ivec2 getMouseDelta() const { return _dMouse; }
        float getWheelDelta() const { return _dWheel; }
        bool isWindowAdjusted() const { return _winAdj; }
        bool willExit() const { return _exit; }
    };
}

#endif
