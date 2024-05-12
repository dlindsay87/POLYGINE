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
	  glShadeModel(GL_SMOOTH);
  	  glViewport(0, 0, _width, _height);
	  cout << "Display initialized." << endl;
	}

	void Window::create(cc *name, int w, int h, unsigned int f){
	  _name = name;
	  _width = w;
	  _height = h;
	  _flags = f;
	  _aspectRatio = (float)_width / (float)_height;

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
	}

	void Window::clear(float (&arr)[3]) {
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  glClearColor(arr[0], arr[1], arr[2], 1.0);
	}
	
	void Window::resize(GLsizei &w, GLsizei &h) {
		static GLsizei w_calc, h_calc;

		if (w > h) {
			w_calc = (GLsizei)(h * _aspectRatio);
			_width = w_calc, _height = h;
			glViewport((w - w_calc) / 2, 0, w_calc, h);
		} else {
			h_calc = (GLsizei)(w / _aspectRatio);
			_width = w, _height = h_calc;
			glViewport(0, (h - h_calc) / 2, w, h_calc);
		}
	}
	
	void Window::swap() {
		SDL_GL_SwapWindow(_window);
	}
	
	void Window::is_vsynced(int vs){
		SDL_GL_SetSwapInterval(vs);
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

	Window::~Window() {
	  SDL_GL_DeleteContext(_context);
	  SDL_DestroyWindow(_window);
	}
	
}
