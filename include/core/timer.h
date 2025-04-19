#pragma once

#include <SDL2/SDL.h>
#include <chrono>
#include <iomanip>
#include <iostream>

namespace CORE
{

typedef std::chrono::steady_clock sc;
typedef std::chrono::system_clock sys_c;
typedef std::chrono::time_point<sc> tp_sc;
typedef std::chrono::duration<double> dd;

class Timer
{
      private:
	tp_sc _startTime, _currentTime, _frameStartTime;

	static const int TARGET_FPS = 60;
	float _fps = 60.0f;

	float _frameTimes[TARGET_FPS];

	void _calcFrameTime();

	void _limitFrameTime();

	float _delta(tp_sc &t);

      public:
	void init();

	void limit();
	float getFPS() { return _fps; }

	float getTime() { return _delta(_startTime); }
};
} // namespace CORE
