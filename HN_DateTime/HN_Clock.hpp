#ifndef HN_CLOCK_HPP_INCLUDED
#define HN_CLOCK_HPP_INCLUDED

    #include <sys/time.h>
    #include <string>
    #include "HN_TimePoint.hpp"

namespace hnapi
{
    namespace datetime
    {
        // Time category definition
        enum HN_ClockMode{
            HN_YEARS_MODE   = 1,
            HN_MOUTHS_MODE  = 2,
            HN_WEEKS_MODE   = 3,
            HN_DAYS_MODE    = 4,
            HN_HOURS_MODE   = 5,
            HN_MINUTES_MODE = 6,
            HN_SECONDS_MODE = 7,
            HN_MILLISECONDS_MODE = 8,
            HN_MICROSECONDS_MODE = 9,
            HN_NANOSECONDS_MODE  = 10,
            HN_TIMESTAMP_MODE    = 11
        };

        // define ticks pointer us long long
        typedef long long HN_ClockPoint;

        // Clock class
        class HN_Clock
        {
            public:
                // Static Methods
                static HN_ClockPoint now(HN_ClockMode _mode);
                static HN_TimePoint  makeNowTimePoint(void);
                static HN_TimePoint  makeTimePoint(

                    // Date data
                    int _mday,      int _mon,       int _year,

                    // Time data
                    int _hour = 0,  int _min = 0,   int _sec = 0
                );
                static HN_TimePoint makeTimePoint(std::string date_time);
                static HN_TimePoint makeTimePoint(time_t timestamp);
        };
    }
}

#endif // HN_CLOCK_H_INCLUDED
