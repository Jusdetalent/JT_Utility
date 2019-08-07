
/*
 * Main base file for Period management
 * By Henock @ Comedac
 * 22/ 11/ 2016 :: 12 h 44
 */

 #include "HN_Period.hpp"
 #include <stdio.h>

 using namespace hnapi::datetime;

 // Builder
HN_Period::HN_Period()
{
    // Nothing to do here
}

HN_Period::HN_Period(const HN_TimePoint &_beginTime, const HN_TimePoint &_endTime)
{
    // Initialize time pointer
    this->beginTime     = _beginTime;
    this->endTime       = _endTime;
}

 // Arithmetic operator
HN_Period& HN_Period::operator+=(const HN_Period &_period)
{
    return *this;
}

HN_Period& HN_Period::operator-=(const HN_Period &_period)
{
    return *this;
}

 // Destroyer
HN_Period::~HN_Period()
{

}

