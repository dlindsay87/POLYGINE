#include "timer.h"

namespace POLYGINE {

	float Timer::_ftAveCalc() {
	    _ftAve = 0.0;

		if (_cnt < FRAMES_TO_AVE) {_cnt++;}

		_cf %= FRAMES_TO_AVE;
		
		_frameTimes[_cf++] = delta(_cTime);
        _cTime = sc::now();

		for (float &f : _frameTimes) _ftAve += f;

		_ftAve /= _cnt;
			
		return (_ftAve > 1.0 / _fpsTarget && _ftAve > 0) ?  1.0 / _ftAve : _fpsTarget;
	}

	void Timer::init(float fps) {
		_fpsTarget = fps;
		cout << "Timer initialized." << endl;
		_cTime = _pTime = _sTime = sc::now();
    }
	
	float Timer::delta(tp_sc t) {
		// the s between frames, ideal 0.016667
		return dd(sc::now() - t).count();
	}
	
	void Timer::limit(bool run) {
		if (run) {
			// 0.0167 spf - (delta which unlimited is ~0.010 spf)
			cout << "Ave fps: " << _ftAveCalc() << ", ";
			if (SDL_GL_GetSwapInterval() == 0) {
				_sleepTime = 1.0 / _fpsTarget - delta(_pTime);
				if (_sleepTime > 0) {
					SDL_Delay(_sleepTime * 1000.0); // needs ms
					cout << "sleep time: " << _sleepTime << "s, ";
				}
			}
		}
		cout << "run time: " << format((int)delta(_sTime));
		cout << flush;
		_pTime = sc::now();		
	}
	
	str Timer::format(int s_count) {
		ss os;

		int sss = s_count % 60;
		s_count -= sss;
		int mm = (s_count / 60) % 60;
		s_count -= mm;
		int hh = (s_count / (60 * 60)) % 60;

	    os << hh << "h:"
	        << fill<double>(2, '0', mm) << "m:"
	        << fill<double>(2, '0', sss) << "s";
		
		return os.str();

	}
	
}
