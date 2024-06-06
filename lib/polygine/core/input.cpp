#include "input.h"

namespace POLYGINE {
	
	bool Input::_wasKeyDown(unsigned int keyID) {
	    auto it = _previousKeyMap.find(keyID);
		return (it != _previousKeyMap.end() ? it -> second : false);
	}
	
	void Input::update() {
	    for (auto &it : _keyMap) _previousKeyMap[it.first] = it.second;
		_winAdj = false;
	}
	
	void Input::pressKey(unsigned int keyID) {
	    _keyMap[keyID] = true;
	}

	void Input::releaseKey(unsigned int keyID) {
	    _keyMap[keyID] = false;
	}

	bool Input::isKeyDown(unsigned int keyID) {
	    auto it = _keyMap.find(keyID);
		return (it != _keyMap.end() ? it -> second : false);
	}

	bool Input::isKeyPressed(unsigned int keyID) {
	    return isKeyDown(keyID) && !_wasKeyDown(keyID);
	}
	
	bool Input::isAnyPressed() {
	    for (auto &it : _keyMap) if (it.second && !_previousKeyMap[it.first]) return true;
	    return false;
	}
	
	void Input::windowEvent(unsigned int winID) {
		if (winID == SDL_WINDOWEVENT_SIZE_CHANGED ||
			winID == SDL_WINDOWEVENT_RESIZED) {
			_winAdj = true;
		}
	}

}