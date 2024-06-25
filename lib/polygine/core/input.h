#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include "utils/typer.h"

namespace POLYGINE {
	
	class Input {
	private:
		bool _wasKeyDown(unsigned int keyID);

	    std::unordered_map<unsigned int, bool> _keyMap;
	    std::unordered_map<unsigned int, bool> _previousKeyMap;
		
		glm::vec3 _dMouse;
		float _dWheel;
		
		bool _winAdj = false;
		
	public:
		void update();
		
	    void pressKey(unsigned int keyID);
	    void releaseKey(unsigned int keyID);

	    bool isKeyDown(unsigned int keyID);
	    bool isKeyPressed(unsigned int keyID);
		
		bool isAnyPressed();

		void detectMotion(SDL_MouseMotionEvent e);
		glm::vec3 getMotion() {return _dMouse;}
		
		void detectWheel(SDL_MouseWheelEvent e);
		float getWheel() {return _dWheel;}
		
		void windowEvent(unsigned int winID);
		bool isWinAdjusted() {return _winAdj;}
		
	};
}

#endif