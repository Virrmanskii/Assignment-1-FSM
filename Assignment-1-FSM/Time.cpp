#include "Time.h"
#include <iostream>

Timer::Timer() 
{
    this->currentTime = std::chrono::system_clock::now();
    this->previousTime = currentTime;
}

Timer& Timer::instance() {
    static Timer timer;
    return timer;
}


void Timer::update()
{
    this->currentTime = std::chrono::system_clock::now();
    this->elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(this->currentTime - this->previousTime).count() / (1000000000.0); 
    this->time += 3*this->elapsedTime;
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

std::string Timer::getTimeString()
{
    std::string returnString;

    int hours = getTime() / 3600;
    std::string h = std::to_string(hours);

    int minutes = (int(getTime()) % 3600) / 60;
    std::string m = std::to_string(minutes);

    if (h.size() == 1)
    {
        h = "0" + h;
    }
    if (m.size() == 1)
    {
        m = "0" + m;
    }

    returnString = "[" + h + ":" + m + "] ";

    return returnString;
}

std::string Timer::getTimeString(double time)
{
    std::string returnString;

    int hours = time / 3600;
    std::string h = std::to_string(hours);

    int minutes = (int(time) % 3600) / 60;
    std::string m = std::to_string(minutes);

    if (h.size() == 1)
    {
        h = "0" + h;
    }
    if (m.size() == 1)
    {
        m = "0" + m;
    }

    returnString = "[" + h + ":" + m + "] ";

    return returnString;
}
