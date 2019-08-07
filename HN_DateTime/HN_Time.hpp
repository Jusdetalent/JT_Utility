#ifndef HN_TIME_HPP_INCLUDED
#define HN_TIME_HPP_INCLUDED

    #include "HN_Ticks.hpp"

namespace hnapi
{
    namespace datetime
    {
        // Time general class
        class HN_Time
        {
            public:
                // Builder
                HN_Time(int _mouth = 1, int _day = 1, int _year = 2016,
                        int _hour = 0, int _minute = 0, int _second = 0);

                // Destroyer
                ~HN_Time();
            private:
                // Data enumeration
                int type;
                time_t timeStamp;
                HN_ClockPoint atomicTimeStamp;
        };
    }
}

#endif // HN_TIME_HPP_INCLUDED
