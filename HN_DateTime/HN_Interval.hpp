#ifndef HN_INTERVAL_HPP_INCLUDED
#define HN_INTERVAL_HPP_INCLUDED

    // Important header
    #include <sys/time.h>
    #include <ctime>

namespace hnapi
{
    namespace datetime
    {
        // Interval class
        class HN_Interval
        {
            public:
                // Builder
                HN_Interval
                (
                    // Date data
                    int _year = 0, int _mon = 0, int _mday = 0,

                    // Time data
                    int _hour = 0, int _min = 0, int _sec = 0
                );

                // Methods
                const struct tm &getInterval(void);
            private:
                // Data
                struct tm iTM;
        };
    }
}

#endif // HN_INTERVAL_HPP_INCLUDED
