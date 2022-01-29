#include "timer.hpp"
#include <cmath>
#include <sstream>
#include <raylib.h>

Timer::Timer(): _minutes(0), _seconds(0) {}

Timer::~Timer() {}

/** Tick the timer */
void Timer::Tick() {
    _seconds -= GetFrameTime();
    if (ceil(_seconds) < 0.0) {
        _minutes--;
        _seconds = 59;
    }
}

/** Set the timer */
void Timer::Set(int minutes, int seconds) {
    _minutes = minutes;
    _seconds = (float)seconds;
}

/** Add time to the timer */
void Timer::Add(int minutes, int seconds) {
    _minutes += minutes;
    _seconds += (float)_seconds;
}

/** Display the game timer */
void Timer::Draw() {
    std::ostringstream text;
    if (ceil(_seconds) < 10) {
        text << _minutes << ":0" << (unsigned int) ceil(_seconds);
    } else {
        text << _minutes << ":" << (unsigned int) ceil(_seconds);
    }
    DrawText(text.str().c_str(), 0.0, 0.0, 32, WHITE);
}

/** Check if the timer is over */
bool Timer::IsOver() {
    return _minutes == 0 && _seconds < 0.0;
}