#ifndef HN_PERIOD_HPP_INCLUDED
#define HN_PERIOD_HPP_INCLUDED

    // Important headers
    #include <sys/time.h>
    #include "HN_TimePoint.hpp"

namespace hnapi
{
    namespace datetime
    {
        // Definition for mouth value
        #define JANUARY_VALUE       31
        #define FEBRUARY_SEXTILLE_VALUE     28
        #define FEBRUARY_BISEXTILLE_VALUE   29
        #define MARTCH_VALUE        31
        #define APRIL_VALUE         30
        #define MAY_VALUE           31
        #define JUNE_VALUE          30
        #define JULY_VALUE          31
        #define AUGUST_VALUE        31
        #define SEPTEMBER_VALUE     30
        #define OCTOBER_VALUE       31
        #define NOVEMBER_VALUE      30
        #define DECEMBER_VALUE      31

        // Year type
        enum YEAR_TYPE{SEXTILLE, BISEXTILLE};

        // Enumerate mouth
        enum MOUTH
        {
            JANUARY = 0,    FEBRUARY    = 1,    MARTCH      = 2,
            APRIL   = 3,    MAY         = 4,    JUNE        = 5,
            JULY    = 6,    AUGUST      = 7,    SEPTEMBER   = 8,
            OCTOBER = 9,    NOVEMBER    = 10,   DECEMBER    = 11
        };

        // Period class
        class HN_Period
        {
            public:
                // Builder
                HN_Period();
                HN_Period(const HN_TimePoint &_beginTime, const HN_TimePoint &_endTime);

                // Arithmetic operator
                HN_Period& operator+=(const HN_Period &_period);
                HN_Period& operator-=(const HN_Period &_period);

                // Getting data
                HN_Interval getInterval(void);

                // Setting data
                void setBeginTime(const HN_TimePoint &_beginTime);
                void setEndTime(const HN_TimePoint &_endTime);

                // Updating data
                void incrementBeginTime(const HN_Interval &i);
                void incrementEndTime(const HN_Interval &i);
                void decrementBeginTime(const HN_Interval &i);
                void decrementEndTime(const HN_Interval &i);

                // Destroyer
                ~HN_Period();
            private:
                // Period data
                HN_TimePoint beginTime, endTime;
        };
    }
}

#endif // HN_PERIODE_HPP_INCLUDED
