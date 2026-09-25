#include "../headers/timer.h"
#include "../lib/raylib6/include/raylib.h"

void UpdateTimer_Tickdown(Timer *timer)
{
    int old_seconds = (int)timer->lifetime;

    timer->lifetime -= GetFrameTime();
    if (timer->lifetime <= timer->max_lifetime)
    {
        timer->isDone = true;
    }

    int new_seconds = (int)timer->lifetime;

    if (new_seconds < old_seconds)
    {
        timer->second_passed = true;
    }
}

void UpdateTimer_Tickup(Timer *timer)
{
    int old_seconds = (int)timer->lifetime;

    timer->lifetime += GetFrameTime();
    if (timer->lifetime >= timer->max_lifetime)
    {
        timer->isDone = true;
    }

    int new_seconds = (int)timer->lifetime;

    if (new_seconds > old_seconds)
        timer->second_passed = true;
}

bool Is_Timer_Done(Timer *timer)
{
    return timer->isDone;
}

void Reset_seconds_passed(Timer *timer)
{
    timer->second_passed = false;
}

void Set_Timer(Timer *timer, float currentTime, float endTime){
    timer->lifetime = currentTime;
    timer->max_lifetime = endTime;
    timer->isDone = false;
    timer->second_passed = false;
}