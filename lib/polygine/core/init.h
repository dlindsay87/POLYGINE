#ifndef INIT_H
#define INIT_H

//#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <random>

//#define GLEW_STATIC
//#define GL_GLEXT_PROTOTYPES

#include "utils/typer.h"

namespace POLYGINE {

	static constexpr SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;

	extern std::mt19937 mt_engine;
	
	extern void init();
	
}

#endif
