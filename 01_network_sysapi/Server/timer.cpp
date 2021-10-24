#include "timer.h"
#include <thread>
#include <chrono>
#include <iostream>


void Timer::start(int ms, const std::function<void()> &processing)
{
    active = true;
    th = new std::thread (&Timer::handle, this, ms);
    handl = processing;
}

void Timer::handle(int ms)
{
    while(active == true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        handl();
    }
}

void Timer::stop ()
{
    active = false;
    th->join();
    delete th;
}