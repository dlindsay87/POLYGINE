#include "init.h"

namespace POLYGINE {
	
	std::random_device rd;
	std::mt19937 mt_engine(rd());

	void init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			cerr << "SDL initialization failed: " << SDL_GetError() << endl;
			exit(1);
		}
		cout << "SDL Initialized. ";
	
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE) != 0 ||
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0 || 
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1) != 0) {
			cerr << "SDL GL set context failed: " << SDL_GetError() << endl;
			exit(1);
		}
		cout << "SDL GL context set." << endl;
		
	    if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) != 0 ||
	        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) != 0 ||
	        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) != 0 ||
	        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) != 0) {
	        cerr << "SDL GL set color buffer size failed: " << SDL_GetError() << endl;
	        exit(1);
	    }
	    cout << "SDL GL color buffer size attributes set." << endl;
		
		if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32) != 0 ||
		    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0) {
	        cerr << "SDL GL set color buffer size failed: " << SDL_GetError() << endl;
	        exit(1);
		}
		cout << "SDL GL buffer and depth attributes set." << endl;
	}

}
