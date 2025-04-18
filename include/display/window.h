#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

#include "input.h"

using std::cout;
using std::cin;
using std::cerr;

using std::endl;

namespace DISPLAY {

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
		TYPICAL = CONTEXTUAL | MOUSE_FOCUS | RESIZABLE | VISIBLE
	} WF;

	class Window {
	private:
		const char* _name;
		int _width, _height;
		unsigned int _flags;

		glm::vec3 _bgc = {0.125f, 0.25f, 0.21875f};
		
		SDL_Window* _window;
		//SDL_Renderer* _renderer;
		SDL_GLContext _context;
		const unsigned char* _version;
		int _utilOffset;

		void _createWindow();
		//void _createRenderer();
		
		void _setContextVersion();
		
		void _resize();
		
	public:
		~Window();

		void initDisplay(const char* name, int w = 640, int h = 480, int offset = 0, unsigned int f = WF::TYPICAL);
		void handleEvents(CORE::Input* ip);
		void update(uint state);

		void swap();

		//SDL_Renderer* getRenderer() const {return _renderer;}

		void setVsync();

		int getWidth() const {return _width - _utilOffset;}
		int getHeight() const {return _height;}
		float getAspectRatio() const {return (float)(_width - _utilOffset) / (float)_height;}

		void setBGC(glm::vec3 bgc) {_bgc = bgc;}
		glm::vec3 getBGC() const {return _bgc;}

		SDL_Window* getWindow() const {return _window;}
		SDL_GLContext getContext() const {return _context;}
	};
	
}

#endif
