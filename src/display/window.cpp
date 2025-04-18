#include "window.h"

namespace DISPLAY {

	Window::~Window() {
		SDL_GL_DeleteContext(_context);
		//SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);

		SDL_Quit();
	}

	void Window::_createWindow() {
		
		_window = SDL_CreateWindow(
			_name,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_width, _height,
			_flags
		);

		if (!_window) {
			std::cerr << "SDL window creation failed: " << SDL_GetError() << std::endl;
			exit(1);
		}
	
	}

	/*void Window::_createRenderer() {
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

		if (!_renderer) {
			std::cerr << "SDL render creation failed: " << SDL_GetError() << std::endl;
			exit(1);
		}

		if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND) != 0) {
			std::cerr << "SDL blend mode setting failed: " << SDL_GetError() << std::endl;
			exit(1);
		}
	}*/

	void Window::_setContextVersion() {
		_context = SDL_GL_CreateContext(_window);

		if (_context == NULL) {
			cerr << "OpenGL context creation failed: " << SDL_GetError() << endl;
			exit(1);
		}
	  
		SDL_GL_MakeCurrent(_window, _context);

		if (glewInit() != GLEW_OK) {
			cerr << "Could not initialize glew!" << endl;
			exit(1);
		}

		_version = glGetString(GL_VERSION);
		if (_version == 0) {
			cerr << "OpenGL configuration failed:" << endl;
			exit(1);
		}
		
		cout << "*** OpenGL Version: " << _version << " ***" << endl;
	}

	void Window::_resize() {
		SDL_GetWindowSize(_window, &_width, &_height);
		glViewport(_utilOffset, 0, _width - _utilOffset, _height);
	}

	void Window::initDisplay(const char* name, int w, int h, int offset, unsigned int f) {
		_name = name;
		_width = w, _height = h;
		_utilOffset = offset;
		_flags = f;
		
		_createWindow();
		//_createRenderer();
		_setContextVersion();
		
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		//glShadeModel(GL_SMOOTH);
		glViewport(_utilOffset, 0, _width - _utilOffset, _height);

		cout << "Display initialized. ";
		setVsync();
	}

	void Window::handleEvents(CORE::Input* ip) {
		if (ip->isWindowAdjusted()) {
			_resize();
		}
	}

	void Window::update(uint state) {
		switch (state) {
			case 0:
				SDL_ShowCursor(SDL_DISABLE);
				SDL_WarpMouseInWindow(_window, _width / 2, _height / 2);
				SDL_SetWindowGrab(_window, SDL_TRUE);
				break;
			default:
				SDL_ShowCursor(SDL_ENABLE);
				SDL_SetWindowGrab(_window, SDL_FALSE);
				break;
		}

		glClearColor(_bgc.x, _bgc.y, _bgc.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::swap() {
		SDL_GL_SwapWindow(_window);	
	}

	void Window::setVsync(){
		static int vs = 0;
		SDL_GL_SetSwapInterval(vs);
		vs = (vs + 1 == 2 ? -1 : vs + 1);
		
		cout << "Vsync is ";
		switch (SDL_GL_GetSwapInterval()) {
			case -1:
				cout << "on and adaptive.\n";
				break;
			case 0:
				cout << "off.\n";
				break;
			case 1:
				cout << "on.\n";
				break;
		}
	}
	
}
