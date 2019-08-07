
/*
 * Main base file for interval management
 * By Henock @ Comedac
 * 22/ 11/ 2016 :: 14 h 04
 */

 #include "HN_Interval.hpp"

using namespace hnapi::datetime;

 // Time point class
HN_Interval::HN_Interval
                (
                // Date data
                int _year, int _mon, int _mday,

                // Time data
                int _hour, int _min, int _sec
                )
{
    // Time data
    this->iTM.tm_sec    = _sec;
    this->iTM.tm_min    = _min;
    this->iTM.tm_hour   = _hour;

    // Data data
    this->iTM.tm_mday   = _mday;
    this->iTM.tm_mon    = _mon;
    this->iTM.tm_year   = _year;

    // Empty data
    this->iTM.tm_wday   = 0;
    this->iTM.tm_yday   = 0;
    this->iTM.tm_isdst  = 0;
}

 // Methods
const struct tm &HN_Interval::getInterval(void)
{
    return this->iTM;
}
