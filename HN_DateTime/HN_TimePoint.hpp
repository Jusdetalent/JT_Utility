#ifndef HN_TIMEPOINT_HPP_INCLUDED
#define HN_TIMEPOINT_HPP_INCLUDED

    // Headers
    #include <sys/time.h>
    #include <ctime>
    #include <string>
    #include "HN_Interval.hpp"


namespace hnapi
{
    namespace datetime
    {
        // Time pointer
        class HN_TimePoint
        {
            public:
                // Builder
                HN_TimePoint
                (
                    // Date data
                    int _mday = 22, int _mon = 11, int _year = 2016,

                    // Time data
                    int _hour = 0, int _min = 0, int _sec = 0
                );

                // Methods
                const struct tm &getTime(void);
                time_t getTimeStamp(void);
                std::string getAsString(void);

                // Comparison methods
                bool isGreater(HN_TimePoint &t);
                bool isGreaterOrEqual(HN_TimePoint &t);
                bool isEqual(HN_TimePoint &t);
                bool isLesserOrEqual(HN_TimePoint &t);
                bool isLesser(HN_TimePoint &t);

                // Arithmetic methods
                void operator+=(HN_Interval &i);
                void operator-=(HN_Interval &i);

                // Managing data
                void subInterval(HN_Interval &i);
                void addInterval(HN_Interval &i);
                HN_Interval operator-=(HN_TimePoint &);

            private:
                // Data
                struct tm pTM;
        };

        // Comparison operator
        bool operator<(HN_TimePoint &t1, HN_TimePoint &t2);
        bool operator<=(HN_TimePoint &t1, HN_TimePoint &t2);
        bool operator==(HN_TimePoint &t1, HN_TimePoint &t2);
        bool operator>=(HN_TimePoint &t1, HN_TimePoint &t2);
        bool operator>(HN_TimePoint &t1, HN_TimePoint &t2);

        // Arithmetic operator
        HN_TimePoint operator+(HN_TimePoint &t, HN_Interval &i);
        HN_TimePoint operator-(HN_TimePoint &t, HN_Interval &i);
        HN_Interval  operator-(HN_TimePoint &t_1, HN_TimePoint &t_2);
    }
}

#endif // HN_TIMEPOINT_HPP_INCLUDED
