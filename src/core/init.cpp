#include "init.h"

namespace CORE {
	
	void initSDL() {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			cerr << "SDL initialization failed: " << SDL_GetError() << endl;
			exit(1);
		}
		cout << "SDL Initialized. ";
	
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE) != 0 ||
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0 || 
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6) != 0) {
			cerr << "SDL GL set context failed: " << SDL_GetError() << endl;
			exit(1);
		}
		cout << "SDL GL context set." << endl;
		
	    if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 2) != 0 ||
	        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 2) != 0 ||
	        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 2) != 0 ||
	        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 2) != 0) {
	        cerr << "SDL GL set color buffer size failed: " << SDL_GetError() << endl;
	        exit(1);
	    }
	    cout << "SDL GL color buffer size attributes set." << endl;
		
		if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8) != 0 ||
		    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0) {
	        cerr << "SDL GL set color buffer size failed: " << SDL_GetError() << endl;
	        exit(1);
		}
		cout << "SDL GL buffer and depth attributes set." << endl;
	}

}
