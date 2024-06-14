#include "game.h"

Game::Game(cc *name, int w, int h, unsigned int f) {
	POLYGINE::init();
	_timer = std::make_shared<POLYGINE::Timer>();
	_window = std::make_shared<POLYGINE::Window>(name, w, h, f);
	_camera = std::make_unique<POLYGINE::Camera>(_window);
	_lighter = std::make_unique<POLYGINE::Lighting>(0.2, 1);
	_inputter = std::make_shared<POLYGINE::Input>();
}

Game::~Game() {
	SDL_Quit();
}

void Game::run() {
	_initGame();
	_looper();
}

void Game::_initGame() {
    _shaderVec.push_back( // light shader
			std::make_shared<POLYGINE::Shader>(
			"lib/polygine/display/shaders/lightshader.vert",
			"lib/polygine/display/shaders/lightshader.frag"
		)
	);
			
	_shaderVec.push_back( // obj shader
			std::make_shared<POLYGINE::Shader>(
			"lib/polygine/display/shaders/shader.vert",
			"lib/polygine/display/shaders/shader.frag"
		)
	);
	
	_camera->linkUBOtoShaders(_shaderVec);
    _state = GS::TITLE;
}

void Game::_input() {
	_inputter->update();
	static SDL_Event event;
	while (SDL_PollEvent(&event)) {
	    switch (event.type) {
			case SDL_KEYDOWN:	
				_inputter->pressKey(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputter->releaseKey(event.key.keysym.sym);
				break;
			case SDL_WINDOWEVENT:
				_inputter->windowEvent(event.window.event);
				break;
			case SDL_QUIT:
				_state = GS::GAME_OVER;
				break;
	    }
	}
}

void Game::_foreverInput() {
	if (_inputter->isKeyPressed(SDLK_SPACE)) {
		cout << endl;
	    _state = (_state == GS::TITLE || _state == GS::PAUSED) ? GS::RUNNING : GS::PAUSED;
	}
	
	if (_inputter->isKeyPressed(SDLK_z) || _inputter->isKeyPressed(SDLK_ESCAPE)) {
	    _state = GS::GAME_OVER;
	} 
}

void Game::_runningInput() {
	if (_inputter->isAnyPressed()) {
		glClearColor(
			_uni_dist(POLYGINE::mt_engine),
			_uni_dist(POLYGINE::mt_engine),
			_uni_dist(POLYGINE::mt_engine),
			1.0
		);
   	}
	
	if (_inputter->isKeyPressed(SDLK_RETURN)) {
   		if (_thingVec.size() > 0) _thingVec.back()->isActive = false;
   		_thingVec.push_back(std::make_unique<POLYGINE::Thing>());
   	}

	for (const auto &t : _thingVec) t->update(_inputter);
	_camera->update(_inputter, _window);
}

void Game::_update() {
	_foreverInput();
	switch(_state) {
		case GS::TITLE:
			cout << "\rTitle! ";
			break;
		case GS::PAUSED:
			cout << "\rPaused! ";
			break;
		case GS::RUNNING:
			_runningInput();	
			cout << "\rRunning! ";
			break;
		case GS::GAME_OVER:
			cout << "\nKilled! ";
			break;
	}
	_window->update(_inputter);
}

void Game::_draw() {
	_lighter->draw(_shaderVec[0]);
	for (const auto &t : _thingVec) t->draw(_shaderVec[1], _lighter->getLight());
	_window->swap();
}

void Game::_looper() {
	while (_state != GS::GAME_OVER) {
		_input();
		_update();
		_draw();
		_timer->limit();
	}  
	cout << "\nGame Over! End time: ";
	_timer->timestamp();
}
