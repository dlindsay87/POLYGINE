#ifndef WINDOW_H
#define WINDOW_H

//#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "utils/typer.h"

namespace POLYGINE {

	typedef enum WindowFlags {
		FULLSCREEN = 0x1,
		CONTEXTUAL = 0x2,
		VISIBLE = 0x4,
		INVISIBLE = 0x8,
		BORDERLESS = 0x10,
		RESIZABLE = 0x20,
		MOUSE_GRABBED = 0x100,
		INPUT_FOCUS = 0x200,
		MOUSE_FOCUS = 0x400,
		MOUSE_CAPTURE = 0x4000,
		ALWAYS_ON_TOP = 0X8000,
		NO_TASKBAR = 0x10000,
		KEY_GRABBED = 0x100000,
		TYPICAL = CONTEXTUAL | RESIZABLE | VISIBLE
	} WF;

	class Window {
	private:
	  cc *_name;
	  int _width, _height;
	  unsigned int _flags;
	  float _aspectRatio;

	  SDL_Window *_window;
	  SDL_GLContext _context;
	  const unsigned char *_version;
	  
	  void _context_version();
	  void _init_display(); 

	public:
	  ~Window();
	  
	  void create(cc *name, int w, int h, unsigned int f);
  	  void clear(float (&arr)[3]);
	  void resize(GLsizei &w, GLsizei &h);
	  void swap();

	  void is_vsynced(int vs);

	  GLsizei getScreenWidth() {return _width;}
	  GLsizei getScreenHeight() {return _height;}
	};
}

#endif
