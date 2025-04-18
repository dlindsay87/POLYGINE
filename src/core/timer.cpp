#include "timer.h"

namespace CORE {

    void Timer::_calcFrameTime() {
        static int cnt = 0, cf = 0;
        
        float frameTimeTotal = 0.0f;

        // we add to frame array the total time it took to loop
        _frameTimes[cf] = _delta(_currentTime);
        _currentTime = std::chrono::steady_clock::now();
        
        for (const float& f : _frameTimes) frameTimeTotal += f;
        
        cf = (cf + 1 == TARGET_FPS ? 0: cf + 1);
        cnt = (cnt == TARGET_FPS ? TARGET_FPS : cnt + 1);
        
        // if the average frame time is larger than the target frametime
        // (the frames are long, i.e. the fps is slow)
        // then that's the best we can do and there's your fps
        // (inverse average frametime)

        float aveFPS = cnt / frameTimeTotal;

        if (aveFPS < static_cast<float>(TARGET_FPS)) _fps =  aveFPS;
        else _fps = static_cast<float>(TARGET_FPS);
    }

    void Timer::_limitFrameTime() {
        if (SDL_GL_GetSwapInterval() == 0) {
            // take difference between ideal frametime and duration from start of frame
            float sleepTime = 1.0 / static_cast<float>(TARGET_FPS) - _delta(_frameStartTime);
            // if delta is smaller, we sleep
            if (sleepTime > 0) SDL_Delay(sleepTime * 1000.0); // needs ms
        }  _frameStartTime = std::chrono::steady_clock::now();
    }

    float Timer::_delta(tp_sc& t) {
        return dd(sc::now() - t).count();
    }

    void Timer::init() {
        _startTime = _currentTime = _frameStartTime = sc::now();
    }

    void Timer::limit() {
        _calcFrameTime();
        _limitFrameTime();
        std::cout << std::fixed << std::setprecision(3) << _fps << std::flush;
    }

}

