#ifndef GAME_H
#define GAME_H

#include "polygine.h"

typedef enum class GameState{
  TITLE,    
  RUNNING,
  PAUSED,
  GAME_OVER
} GS;


class Game {
public:
	Game(float fps, cc *name, int w, int h, unsigned int f);
	~Game();
	
	void run();
	
private:
	float _fps;
	bool _isRunning;
	cc *_windowName;
	int _windowWidth;
	int _windowHeight;
	unsigned int _windowFlags;

	void _initGame();
	void _looper();
	void _input();
	void _update();
	
	std::uniform_real_distribution<float> _uni_dist;
	float _randos[3] {0,0,0};
	
	POLYGINE::Window _window;
	POLYGINE::Shader _shader;
	POLYGINE::Timer _timer;
	
	GS _state;
	
};

#endif
