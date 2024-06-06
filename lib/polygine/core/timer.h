#ifndef TIMER_H
#define TIMER_H

#include "utils/typer.h"

namespace POLYGINE {
	
	#ifndef FPS
	#define FPS 60
	#endif
	
	class Timer {
	private:
		float _frameTimes[FPS];
		tp_sc _cTime, _pTime, _sTime;

		float _ftAveCalc();

	public:
		Timer();

		float delta(tp_sc t);
		void limit();

		str format(int s_count);

		void timestamp() {
		  const std::time_t t_c = sys_c::to_time_t(sys_c::now());
		  cout << ctime(&t_c);
		}
	  
	};
}

#endif
