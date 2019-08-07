#ifndef HN_DATE_HPP_INCLUDED
#define HN_DATE_HPP_INCLUDED

    // Indispensable headers
    #include <sys/time.h>
    #include "HN_Time.hpp"

namespace hnapi
{
    namespace datetime
    {
        // Date class
        class HN_Date
        {
            public:
                // Builder
                HN_Date();

                // Static methods
                static bool isSextille(void);

                // Non static methods for getting data
                int getSecond(void);  	/* Seconds: 0-60 (to accommodate leap seconds) */
                int getMinute(void);  	/* Minutes: 0-59 */
                int getHour(void); 	/* Hours since midnight: 0-23 */
                int getDay(void); 	/* Day of the month: 1-31 */
                int getMouth(void);  	/* Months *since* January: 0-11 */
                int getYear(void); 	/* Years since 1900 */
                int getWeekDay(void); 	/* Days since Sunday (0-6) */
                int getYearDay(void); 	/* Days since Jan. 1: 0-365 */

                // Updating data

                // Setting data


                // Destroyer
                ~HN_Date();

            private:
                // Date data
                struct tm dateTM;
        };
    }
}

#endif // HN_DATE_HPP_INCLUDED
