#include "game.h"

Game::Game(float fps, cc *name, int w, int h, unsigned int f)
	: _fps(fps), _windowName(name), _windowWidth(w), _windowHeight(h), _windowFlags(f) {
	_isRunning = true;
	POLYGINE::init();
}

Game::~Game() {
	SDL_Quit(); 
}

void Game::run() {
	_initGame();
	_looper();
}

void Game::_initGame() {
	_window.create(_windowName, _windowWidth, _windowHeight, _windowFlags);
	_fps == 60.0 ? _window.is_vsynced(-1) : _window.is_vsynced(0);
    _state = GS::TITLE;
	_shader.init();
	_timer.init(_fps);
}

void Game::_input() {
	static int vs = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
	    switch (event.type) {
			case SDL_KEYDOWN:
			    for (float &f : _randos) f = _uni_dist(POLYGINE::mt_engine);
			    cout << endl;
		        if (event.key.keysym.sym == SDLK_SPACE) {
			        _state = (_state == GS::TITLE || _state == GS::PAUSED) ? GS::RUNNING : GS::PAUSED;
		        } if (event.key.keysym.sym == SDLK_z)  {
			        _state = GS::GAME_OVER;
		        } if (event.key.keysym.sym == SDLK_v && _fps == 60.0)  {
					vs %= 3;
					_window.is_vsynced(1 - vs++);
					
			    }
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				    _window.resize(event.window.data1, event.window.data2);
				}
				break;
			case SDL_QUIT:
				cout << endl;
				_state = GS::GAME_OVER;
				break;
	    }
	}
}

void Game::_update() {
	cout << "\r" << fixed << setprecision(3);
	switch(_state) {
		case GS::TITLE:
			cout << "Title! ";
			break;
		case GS::PAUSED:
			cout << "Paused! ";
			break;
		case GS::RUNNING:
			cout << "Running! ";
			break;
		case GS::GAME_OVER:
			cout << "Killed, ";
			_isRunning = false;
			break;
	}
}

void Game::_looper() {
	while (_state != GS::GAME_OVER) {
		_input();
		_update();
		_window.clear(_randos);
		_shader.draw();
		_window.swap();
		_timer.limit(_isRunning);
	}  
	cout << "\nGame Over!" << endl;
}
