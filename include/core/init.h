#pragma once

#include <SDL2/SDL.h>

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

namespace CORE {
	
	static constexpr SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;
	
	extern void initSDL();
	
}
