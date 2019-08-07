
/*
 * Main base file for ticks functions
 * By Henock @ Comedac
 * 21/ 11/ 2016 :: 21 h 52
 */

 #include "HN_Ticks.hpp"
 #include <stdio.h>

 using namespace hnapi::datetime;

 // Ticks methods
HN_Ticks::HN_Ticks()
{
    this->state = BEFORE_TICKS;
}

// Ticks methods
void HN_Ticks::now(void)
{
    // Pass ticks to now
    this->beginTime = HN_Clock::now(HN_MICROSECONDS_MODE);
    this->endTime = this->beginTime;
    this->state = AFTER_TICKS;
}

void HN_Ticks::setInterval(long long _micro)
{
    // Reset interval
    this->beginTime = HN_Clock::now(HN_MICROSECONDS_MODE);
    this->endTime = this->beginTime + _micro;
    this->state = TICKSING;
}

void HN_Ticks::addInterval(long long _micro)
{
    // Increment to end time
    this->endTime+= _micro;
}

void HN_Ticks::subInterval(long long _micro)
{
    // Sub to end time
    this->endTime-= _micro;
}

// Get methods :: BSD platform
HN_ClockPoint HN_Ticks::getRest(void)
{
    return this->currentRest;
}

HN_ClockPoint HN_Ticks::getCurrent(void)
{
    return this->endTime;
}

enum TICKS_STATE &HN_Ticks::getState(void)
{
    // Only BSD platform
    if(HN_Clock::now(HN_MICROSECONDS_MODE) < this->endTime)
        this->state = TICKSING;
    else{

        // Run ticks
        if(this->state == BEFORE_TICKS)
            return this->state;

        if(this->state != NO_TICKS)
            this->state = AFTER_TICKS;
    }

    return this->state;
}

HN_Ticks::~HN_Ticks()
{

}

