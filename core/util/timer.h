#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace muon {

	typedef std::chrono::high_resolution_clock hrclock;
	typedef std::chrono::duration<float, std::milli> milli_t;

	class Timer 
	{
	private:
		std::chrono::time_point<hrclock> _start;

	public:
		Timer();
		void reset();
		float elapsed();
		float elapsedMillis();
	};

}


#endif // !TIMER_H
