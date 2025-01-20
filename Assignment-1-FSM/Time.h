#pragma once
#include <chrono>
class Timer
{
	public:
		static Timer& instance();
		//void startDeltaTime();
		void update();
		double getTime();
		void stopDeltaTime();
		double getDeltaTime();
	private:
		std::chrono::system_clock::time_point previousTime;// = std::chrono::system_clock::now();
		std::chrono::system_clock::time_point currentTime;
		double elapsedTime;
		double time;
		int ticksPerSecond = 60;
		Timer();
};

