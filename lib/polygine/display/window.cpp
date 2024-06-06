#include "window.h"

namespace POLYGINE {

	void Window::_context_version() {
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

	void Window::_init_display() {
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glViewport(0, 0, _width, _height);
		cout << "Display initialized. ";
	}

	void Window::_is_vsynced(){
		static int vs = 0;
		SDL_GL_SetSwapInterval(vs);
		vs = (vs + 1 == 2 ? -1: vs + 1);
		
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

	void Window::_resize() {
		static float f = 1.0 / tan(glm::radians(45.0f) * 0.5f);
		
		SDL_GetWindowSize(_window, &_width, &_height);
		glViewport(0, 0, _width, _height);
		
		if (getAspectRatio() > 1) {
			_projMat[0][0] =  f / getAspectRatio();
			_projMat[1][1] = f;
		} else {
			_projMat[0][0] = f;
			_projMat[1][1] = f * getAspectRatio();
		}
	}

	Window::Window(cc *name, int w, int h, unsigned int f) {
		_name = name;
		_width = w;
		_height = h;
		_flags = f;

		_window = SDL_CreateWindow(
			_name,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_width, _height,
			_flags
		);

		if (_window == NULL) {
			cerr << "SDL window creation failed: " << SDL_GetError() << endl;
			exit(1);
		}

		_context_version();
		_init_display();
		_is_vsynced();

		_projMat = glm::perspective(glm::radians(45.0f), getAspectRatio(), 0.1f, 10.0f);
		_viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	}
	
	Window::~Window() {
	  SDL_GL_DeleteContext(_context);
	  SDL_DestroyWindow(_window);
	}
	
	void Window::update(std::shared_ptr<Input> ip) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (ip -> isKeyPressed(SDLK_v)) {
			cout << endl;
			_is_vsynced();	
		} if (ip -> isWinAdjusted()) {
		    _resize();
		}
	}

	void Window::swap(std::shared_ptr<Shader> shader) {
		shader->use();
		shader->setProjectionMatrix(_projMat);
		shader->setViewMatrix(_viewMat);
		SDL_GL_SwapWindow(_window);
	}
	
}
