#include "game.h"

Game::Game(cc *name, int w, int h, unsigned int f) {
	POLYGINE::init();
	_timer = std::make_shared<POLYGINE::Timer>();
	_window = std::make_shared<POLYGINE::Window>(name, w, h, f);
	_lighter = std::make_shared<POLYGINE::Lighting>(0.2, 2);
	_inputter = std::make_shared<POLYGINE::Input>();
	_camera = std::make_unique<POLYGINE::Camera>(_window);
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
			case SDL_MOUSEMOTION:
				_inputter->detectMotion(event.motion);
				break;
			case SDL_MOUSEWHEEL:
				_inputter->detectWheel(event.wheel);
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
	_window->takeInput(_inputter);
}

void Game::_runningInput() {
	if (_inputter->isAnyPressed()) {
		glClearColor(
			_uni_dist(POLYGINE::mt_engine),
			_uni_dist(POLYGINE::mt_engine),
			_uni_dist(POLYGINE::mt_engine),
			1.0f
		);
   	}
	
	if (_inputter->isKeyPressed(SDLK_RETURN)) {
   		_thingVec.push_back(std::make_shared<POLYGINE::Thing>());
		_camera->setTarget(_thingVec.back());
   	}
	
	if (_inputter->isKeyPressed(SDLK_DELETE)) {
		_thingVec.clear();
		_camera->setTarget(nullptr);
	}
	
	_camera->takeInput(_inputter);
	if (_thingVec.size() > 0) _thingVec.back()->takeInput(_inputter);
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
			for (const auto &t : _thingVec) t->update();
			cout << "\rRunning! ";
			break;
		case GS::GAME_OVER:
			cout << "\nKilled! ";
			break;
	}
	_camera->update();
	_window->update(static_cast<uint>(_state));
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
