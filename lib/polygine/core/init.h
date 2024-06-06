#ifndef INIT_H
#define INIT_H

#include <random>

#include "utils/typer.h"

namespace POLYGINE {
	
	extern std::mt19937 mt_engine;

	static constexpr SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;
	
	extern void init();
	
}

#endif
