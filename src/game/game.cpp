#include "game.h"

namespace GAME
{

Game::Game(bool shaderDev) : _state(State::PAUSED)
{
	if (shaderDev) {
		_imgUtil = new UTIL::ImguiUtil();
		_utilWidth = 160;
	}
	_init();
}

void Game::_init()
{
	CORE::initSDL();

	_window.initDisplay("Poly", 640 + _utilWidth, 480, _utilWidth,
			    DISPLAY::WF::TYPICAL);

	if (_imgUtil)
		_imgUtil->init(&_window);

	_timer.init();

	_shaders = {{"light", new DISPLAY::Shader("shaders/lightshader.vert",
						  "shaders/lightshader.frag")},
		    {"obj", new DISPLAY::Shader("shaders/shader.vert",
						"shaders/shader.frag")}};

	_player.init({1.0, 0.5, 0.2}, 2, 1.0f);

	_walls.insert(_walls.end(),
		      {new ENT::Wall({1.0f, 0.3f, 0.3f}, {1.0f, 8.0f, 8.0f},
				     {2.0f, -4.0f, 0.0f}),
		       new ENT::Wall({1.0f, 0.3f, 0.3f}, {1.0f, 4.0f, 4.0f},
				     {-2.0f, -7.0f, -2.0f})});

	_light.init();
	_camera.init(&_shaders);
}

void Game::_handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (_imgUtil)
			ImGui_ImplSDL2_ProcessEvent(&event);
		_input.handleEvents(&event);
	}

	if (!_imgUtil || (_imgUtil && !_imgUtil->isCaptured())) {
		if (_input.isKeyPressed(SDL_SCANCODE_P))
			_state =
			    (_state == State::PAUSED || _state == State::TITLE)
				? State::RUNNING
				: State::PAUSED;

		if (_input.isKeyPressed(SDL_SCANCODE_Z) ||
		    _input.isKeyPressed(SDL_SCANCODE_ESCAPE))
			_state = State::GAME_OVER;

		if (_input.isKeyPressed(SDL_SCANCODE_V)) {
			cout << endl;
			_window.setVsync();
		}
	}

	if (_input.willExit())
		_state = State::GAME_OVER;

	_window.handleEvents(&_input);

	switch (_state) {
	case State::RUNNING:
		_camera.handleEvents(&_input);
		_player.handleEvents(&_input);
		cout << "\rRunning! ";
		break;
	case State::TITLE:
		cout << "\rTitle! ";
		break;
	case State::PAUSED:
		cout << "\rPaused! ";
		break;
	case State::GAME_OVER:
		cout << "\nKilled! ";
		break;
	}
}

void Game::_update()
{
	_window.update((uint)_state);
	for (const auto &wall : _walls)
		wall->update();
	_camera.update(&_window, _player.getPosition());
	_player.update(_camera.getPRY());
	_input.update();
}

void Game::_draw()
{
	if (_imgUtil) {
		_imgUtil->begin();
		_imgUtil->fragBox({0, 0}, {_utilWidth, _window.getHeight()},
				  _shaders.at("obj"));
		_imgUtil->end();
	}

	_light.draw(_shaders.at("light"));
	_player.draw(_shaders.at("obj"), &_light, &_window, _camera.getPos());
	for (const auto &wall : _walls)
		wall->draw(_shaders.at("obj"), &_light, &_window,
			   _camera.getPos());

	_window.swap();
}

void Game::run()
{
	while (_state != State::GAME_OVER) {
		_handleEvents();
		_update();
		_draw();
		_timer.limit();
	}
	std::cout << "\nGame Over!" << std::endl;
}

} // namespace GAME