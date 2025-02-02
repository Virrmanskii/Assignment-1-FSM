#pragma once
#include <chrono>
#include <string>
class Timer
{
	public:
		static Timer& instance();
		//void startDeltaTime();
		void update();
		double getTime();
		void stopDeltaTime();
		double getDeltaTime();
		std::string getTimeString();
		std::string getTimeString(double time);
	private:
		std::chrono::system_clock::time_point previousTime;// = std::chrono::system_clock::now();
		std::chrono::system_clock::time_point currentTime;
		double elapsedTime;
		double time = 0;
		int ticksPerSecond = 60;
		Timer();
};

