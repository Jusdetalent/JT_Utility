/*
 * Main base file for clock management
 * By Henock @ Comedac
 * 24/ 11/ 2016 :: 12 h 48
 */

 #include "HN_Clock.hpp"
 #include <stdlib.h>
 #include <vector>
 #include <iostream>


using namespace hnapi::datetime;


 // Static methods
HN_ClockPoint HN_Clock::now(HN_ClockMode _mode)
{
    switch(_mode)
    {
            // Return Unix time stamp us year
        case 1:
            {
                time_t t;
                time(&t);
                struct tm *t_m = localtime(&t);
                HN_ClockPoint year = (HN_ClockPoint)t_m->tm_year;
                return year + 1900;
            }
            break;

            // Return Unix time stamp us mouth
        case 2:
            {
                time_t t;
                time(&t);
                struct tm *t_m = localtime(&t);
                HN_ClockPoint month = (HN_ClockPoint)t_m->tm_mon;
                return month + 1;
            }
            break;

            // Return Unix time stamp us week
        case 3:
            {
                // Manage local time
                time_t timeValue = time(NULL);

                // Build data to return
                HN_ClockPoint t_value = (HN_ClockPoint) timeValue;

                // Return time us week
                return t_value / 302400;
            }
            break;

            // Return Unix time stamp us days
        case 4:
            {
                // Manage local time
                time_t timeValue = time(NULL);

                // Build data to return
                HN_ClockPoint t_value = (HN_ClockPoint) timeValue;

                // Return time us days
                return t_value / 43200;
            }
            break;

            // Return Unix time stamp us hours
        case 5:
            {
                // Manage local time
                time_t timeValue = time(NULL);

                // Build data to return
                HN_ClockPoint t_value = (HN_ClockPoint) timeValue;

                // Return time us hours
                return t_value / 3600;
            }
            break;

            // Return Unix time stamp us minutes
        case 6:
            {
                // Manage local time
                time_t timeValue = time(NULL);

                // Build data to return
                HN_ClockPoint t_value = (HN_ClockPoint) timeValue;

                // Return time us minutes
                return t_value / 60;
            }
            break;

            // Return Unix time stamp us seconds
        case 7: return (HN_ClockPoint) time(NULL);
            break;

            // Return Unix time stamp us milliseconds
        case 8:
            {
                // Manage local time
                struct timeval timeValue;
                gettimeofday(&timeValue, NULL);

                // Build data to return
                HN_ClockPoint t_value = (HN_ClockPoint) timeValue.tv_sec;
                    t_value*= 1000000;
                    t_value+= (HN_ClockPoint) timeValue.tv_usec;

                // Return time us microseconds
                return t_value / 1000;
            }
            break;

            // Return Unix time stamp us microseconds
        case 9:
            {
                // Manage local time
                struct timeval timeValue;
                gettimeofday(&timeValue, NULL);

                // Build data to return
                HN_ClockPoint t_value = (HN_ClockPoint) timeValue.tv_sec;
                    t_value*= 1000000;
                    t_value+= (HN_ClockPoint) timeValue.tv_usec;

                // Return time us microseconds
                return t_value;
            }
            break;

            // Return Unix time stamp us nanoseconds
        case 10:
            {
                // Manage local time
                struct timeval timeValue;
                gettimeofday(&timeValue, NULL);

                // Build data to return
                HN_ClockPoint t_value = (HN_ClockPoint) timeValue.tv_sec;
                    t_value*= 1000000;
                    t_value+= (HN_ClockPoint) timeValue.tv_usec;

                // Return time us microseconds
                return t_value * 1000;
            }
            break;

            // Return Unix time stamp us seconds
        case 11: return (HN_ClockPoint) time(NULL);
            break;
    }

    // Return time stamp us long
    return -1;
}

HN_TimePoint HN_Clock::makeNowTimePoint(void)
{
    time_t t;
    time(&t);
    struct tm   *t_m = localtime(&t);
    HN_TimePoint __timePoint
                    (
                        t_m->tm_mday,   t_m->tm_mon + 1,    t_m->tm_year + 1900,
                        t_m->tm_hour,   t_m->tm_min,        t_m->tm_sec
                    );
    return __timePoint;
}

HN_TimePoint HN_Clock::makeTimePoint(

                    // Date data
                    int _mday,  int _mon,   int _year,

                    // Time data
                    int _hour,  int _min,   int _sec
                )
{
    HN_TimePoint __timePoint
                    (
                        _mday,  _mon + 1,   _year,
                        _hour,  _min,       _sec
                    );
    return __timePoint;
}

HN_TimePoint HN_Clock::makeTimePoint(std::string date_time)
{
    // Parse initial link
    int buffer_size = date_time.size(), it = 0;
    std::vector<std::string> array;
    std::string item;
    struct tm myTime;

    // Time data
    myTime.tm_sec    = 0;
    myTime.tm_min    = 0;
    myTime.tm_hour   = 0;

    // Data data
    myTime.tm_mday   = 0;
    myTime.tm_mon    = 0;
    myTime.tm_year   = 0;

    // Empty data
    myTime.tm_wday   = 0;
    myTime.tm_yday   = 0;
    myTime.tm_isdst  = 0;

    // Loop to parse link
    for(int i = 0; i <= buffer_size; i++){
        switch(date_time[i]){
            case ' ':
            case '-':
            case ':':
            case '\0': {
                    if(item.empty())
                        break;

                    switch(it){
                        case 0: myTime.tm_year  = atoi(item.c_str()); break;
                        case 1: myTime.tm_mon   = atoi(item.c_str()); break;
                        case 2: myTime.tm_mday  = atoi(item.c_str()); break;
                        case 3: myTime.tm_hour  = atoi(item.c_str()); break;
                        case 4: myTime.tm_min   = atoi(item.c_str()); break;
                        case 5: myTime.tm_sec   = atoi(item.c_str()); break;
                    }

                    item.clear();
                    it++;
                }
                break;
            default:
                item+= date_time[i];
                break;
        }
    }

    HN_TimePoint __timePoint
                    (
                        myTime.tm_mday, myTime.tm_mon,  myTime.tm_year,
                        myTime.tm_hour, myTime.tm_min,  myTime.tm_sec
                    );
    return __timePoint;
}

HN_TimePoint HN_Clock::makeTimePoint(time_t timestamp){

    struct tm *t_m = localtime(&timestamp);
    HN_TimePoint __timePoint
                    (
                        t_m->tm_mday,   t_m->tm_mon + 1,    t_m->tm_year + 1900,
                        t_m->tm_hour,   t_m->tm_min,        t_m->tm_sec
                    );
    return __timePoint;
}



