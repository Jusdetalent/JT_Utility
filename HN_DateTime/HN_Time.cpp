
/*
 * Main base file for time management
 * By Henock @ Comedac
 * 21/ 11/ 2016 :: 16 h 16
 */

 #include "HN_Time.hpp"
 #include <stdio.h>

 using namespace hnapi::datetime;

 // Builder
HN_Time::HN_Time(int _mouth, int _day, int _year, int _hour,
                 int _minute, int _second)
{
    // Adjust time limit
    _year-= 1900;
    _mouth-= 1;

    // Build data
    struct tm timeStruct = {_second, _minute, _hour, _day, _mouth,
                            _year, 0, 0, 0};
    this->timeStamp = mktime(&timeStruct);
    this->type = HN_TIMESTAMP_MODE;
}

 // Destroyer
HN_Time::~HN_Time()
{

}
