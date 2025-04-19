#pragma once

#include "init.h"

#include "camera.h"
#include "lighting.h"
#include "shader.h"
#include "window.h"

#include "input.h"
#include "timer.h"

#include "imguiUtil.h"

#include "player.h"
#include "wall.h"

#include <iostream>
#include <memory>

namespace GAME
{

class Game
{
      private:
	enum class State : uint {
		RUNNING = 0,
		TITLE = 1,
		PAUSED = 2,
		GAME_OVER = 3
	};

	State _state;

	DISPLAY::Window _window;

	std::map<std::string, DISPLAY::Shader *> _shaders;
	DISPLAY::Light _light;
	DISPLAY::Camera _camera;

	CORE::Timer _timer;
	CORE::Input _input;

	UTIL::ImguiUtil *_imgUtil = nullptr;
	int _utilWidth = 0;

	ENT::Player _player;
	std::vector<ENT::Wall *> _walls;

	void _init();
	void _handleEvents();
	void _update();
	void _draw();

      public:
	Game(bool shaderDev);

	~Game()
	{
		if (_imgUtil)
			delete _imgUtil;
		for (auto *wall : _walls)
			delete wall;
		for (auto &[name, shader] : _shaders)
			delete shader;
		_shaders.clear();
		SDL_Quit();
	}

	void run();
};
} // namespace GAME
