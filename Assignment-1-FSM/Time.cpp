#include "Time.h"

Timer::Timer() 
{
    this->currentTime = std::chrono::system_clock::now();
    this->previousTime = currentTime;
}

Timer& Timer::instance() {
    static Timer timer;
    return timer;
}

//void Timer::startDeltaTime()
//{
//    this->currentTime = std::chrono::system_clock::now();
//}

void Timer::update()
{
    this->currentTime = std::chrono::system_clock::now();
    this->elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(this->currentTime - this->previousTime).count() / (1000000000.0); 
    this->time += this->elapsedTime;
}

double Timer::getTime()
{
    return this->time;
}

void Timer::stopDeltaTime()
{
    this->previousTime = this->currentTime;
}

double Timer::getDeltaTime()
{
    return elapsedTime;
}
