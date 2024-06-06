#ifndef WINDOW_H
#define WINDOW_H

#include "display/shader.h"
#include "core/input.h"

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

		SDL_Window *_window;
		SDL_GLContext _context;
		const unsigned char *_version;
		
		glm::mat4 _projMat;
		glm::mat4 _viewMat;

		void _context_version();
		void _init_display();
		void _is_vsynced();
		void _resize();

	public:
  	  Window(cc *name, int w, int h, unsigned int f);
	  ~Window();
	  
	  void update(std::shared_ptr<Input> ip);
  	  void swap(std::shared_ptr<Shader> shader);

	  int getScreenWidth() {return _width;}
	  int getScreenHeight() {return _height;}
	  float getAspectRatio() {return (float)_width / (float)_height;}
	  
	  void setScreenWidth(int w) {_width = w;}
	  void setScreenHeight(int h) {_height = h;}
	};
	
}

#endif
