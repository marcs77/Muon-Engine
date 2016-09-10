#include "timer.h"
namespace muon {
	Timer::Timer()
	{
		reset();
	}

	void Timer::reset()
	{
		_start = hrclock::now();
	}

	float Timer::elapsed()
	{
		return elapsedMillis() * 0.001;
	}

	float Timer::elapsedMillis() {
		return std::chrono::duration_cast<milli_t>(hrclock::now() - _start).count();
	}
}

