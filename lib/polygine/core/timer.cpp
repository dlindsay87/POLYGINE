#include "timer.h"

namespace POLYGINE {

	float Timer::_ftAveCalc() {
  	    static int cnt = 0;
	  	static int cf = 0;
	    static float ftTot;
		
		ftTot = 0.0;

		_frameTimes[cf] = delta(_cTime);
		_cTime = sc::now();
		
		for (const float &f : _frameTimes) ftTot += f;
		
		cf = (cf + 1 == FPS ? 0: cf + 1);
		cnt = (cnt == FPS ? FPS : cnt + 1);
		
		return ftTot > cnt / (float)FPS ?  cnt / ftTot : (float)FPS;
	}

	Timer::Timer() {
		_cTime = _pTime = _sTime = sc::now();
		cout << "Timer initialized. Start time: ";
		timestamp();
    }
	
	float Timer::delta(tp_sc t) {
		// the s between frames, ideal 0.016667
		return dd(sc::now() - t).count();
	}
	
	void Timer::limit() {
		// 0.0167 spf - (delta which unlimited is ~0.010 spf)
		cout << fixed << setprecision(3) << "Ave fps: " << _ftAveCalc() << ", ";
		if (SDL_GL_GetSwapInterval() == 0) {
	  	    static float sleepTime;
			sleepTime = 1.0 / (float)FPS - delta(_pTime);
			if (sleepTime > 0) {
				SDL_Delay(sleepTime * 1000.0); // needs ms
				cout << "sleep time: " << sleepTime << "s, ";
			}
		}
		cout << "run time: " << format((int)delta(_sTime)) << flush;
		_pTime = sc::now();		
	}
	
	str Timer::format(int s_count) {
		ss os;

		int sss = s_count % 60;
		s_count -= sss;
		int mm = (s_count / 60) % 60;
		s_count -= mm * 60;
		int hh = (s_count / (60 * 60)) % 60;

	    os << hh << "h:"
			<< std::setw(2) << std::setfill('0') << mm << "m:"
	        << std::setw(2) << std::setfill('0') << sss << "s";
		
		return os.str();
	}
	
}
