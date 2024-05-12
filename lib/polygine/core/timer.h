#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include "utils/typer.h"

namespace POLYGINE {
	
	#ifndef FRAMES_TO_AVE
	#define FRAMES_TO_AVE 60
	#endif

	class Timer {
	private:
	  float _fpsTarget;
	  float _ftAve;
	  float _frameTimes[FRAMES_TO_AVE] = {};
	  int _cnt = 0;
	  int _cf = 0;
	  
	  tp_sc _cTime, _pTime, _sTime;
	  float _sleepTime;
	  
	  float _ftAveCalc();

	public:
	  void init(float fps);
	  float delta(tp_sc t);
  	  void limit(bool run);
	  str format(int s_count);
	  
	};
}

#endif
