#pragma once

/** Represents the game tumer */
class Timer {
public:
    Timer();
    ~Timer();

    /** Tick the timer */
    void Tick();
    /** Set the timer */
    void Set(int minutes, int seconds);
    /** Add time to the timer */
    void Add(int minutes, int seconds);
    /** Display the game timer */
    void Draw();
    /** Check if the timer is over */
    bool IsOver();
private:
    int _minutes;
    float _seconds;
};