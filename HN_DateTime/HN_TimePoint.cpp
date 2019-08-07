
/*
 * Main base file for time pointer
 * By Henock @ Comedac
 * 22/ 11/ 2016 :: 15 h 14
 */

 #include "HN_TimePoint.hpp"
 #include "HN_Period.hpp"
 #include <cstdio>
 #include <cstring>

 using namespace hnapi::datetime;

 // Time point class
HN_TimePoint::HN_TimePoint
                (
                // Date data
                int _mday, int _mon, int _year,

                // Time data
                int _hour, int _min, int _sec
                )
{
    // Adjust time limit
    _year-= 1900;
    _mon-= 1;

    // Time data
    this->pTM.tm_sec    = _sec;
    this->pTM.tm_min    = _min;
    this->pTM.tm_hour   = _hour;

    // Data data
    this->pTM.tm_mday   = _mday;
    this->pTM.tm_mon    = _mon;
    this->pTM.tm_year   = _year;

    // Empty data
    this->pTM.tm_wday   = 0;
    this->pTM.tm_yday   = 0;
    this->pTM.tm_isdst  = 0;
}

 // Comparison methods
bool HN_TimePoint::isGreater(HN_TimePoint &t)
{
    time_t t_1 = mktime(&this->pTM),
            t_2 = mktime(&t.pTM);
    if(t_1 <= t_2)
        return false;

    return true;
}

bool HN_TimePoint::isGreaterOrEqual(HN_TimePoint &t)
{
    time_t t_1 = mktime(&this->pTM),
            t_2 = mktime(&t.pTM);
    if(t_1 < t_2)
        return false;

    return true;
}

bool HN_TimePoint::isEqual(HN_TimePoint &t)
{
    time_t t_1 = mktime(&this->pTM),
            t_2 = mktime(&t.pTM);
    if(t_1 != t_2)
        return false;

    return true;
}

bool HN_TimePoint::isLesserOrEqual(HN_TimePoint &t)
{
    time_t t_1 = mktime(&this->pTM),
            t_2 = mktime(&t.pTM);
    if(t_1 > t_2)
        return false;

    return true;
}

bool HN_TimePoint::isLesser(HN_TimePoint &t)
{
    time_t t_1 = mktime(&this->pTM),
            t_2 = mktime(&t.pTM);
    if(t_1 >= t_2)
        return false;

    return true;
}

 // Arithmetic methods
void HN_TimePoint::operator+=(HN_Interval &i)
{
    this->addInterval(i);
    return;
}

void HN_TimePoint::operator-=(HN_Interval &i)
{
    this->subInterval(i);
    return;
}

// Managing data
void HN_TimePoint::subInterval(HN_Interval &i)
{
    // Get time structure for calculate
    const struct tm &iTM = i.getInterval();

    /*
    printf
        (
            "%d %d %d :: %d %d %d\n",
            this->pTM.tm_mday,
            this->pTM.tm_mon + 1,
            this->pTM.tm_year + 1900,
            this->pTM.tm_hour + 1,
            this->pTM.tm_min + 1,
            this->pTM.tm_sec + 1
        );*/

    // Sub time data
    this->pTM.tm_sec    -= iTM.tm_sec;
        if(this->pTM.tm_sec < 0)
            {
            while(this->pTM.tm_sec < 0)
                {
                this->pTM.tm_min--;
                this->pTM.tm_sec+= 60;
            }
        }

    this->pTM.tm_min    -= iTM.tm_min;
        if(this->pTM.tm_min < 0)
            {
            while(this->pTM.tm_min < 0)
                {
                this->pTM.tm_hour--;
                this->pTM.tm_min+= 60;
            }
        }

    this->pTM.tm_hour   -= iTM.tm_hour;
        if(this->pTM.tm_hour < 0)
            {
            while(this->pTM.tm_hour < 0)
                {
                this->pTM.tm_mday--;
                this->pTM.tm_hour+= 24;
            }
        }

    // Sub day value
    this->pTM.tm_mday   -= iTM.tm_mday;
    bool end = false;
    int jump_value = 31;

    // Manage time
    while(!end)
    {
        // Detect month
        switch(this->pTM.tm_mon)
        {
            case JANUARY:
                    jump_value = JANUARY_VALUE;
                break;
            case FEBRUARY:
                    // Catch if sextil or bisextill
                    if((this->pTM.tm_year % 4) == 0)
                        jump_value = FEBRUARY_BISEXTILLE_VALUE;
                    else
                        jump_value = FEBRUARY_SEXTILLE_VALUE;
                break;
            case MARTCH:
                    jump_value = MARTCH_VALUE;
                break;
            case APRIL:
                    jump_value = APRIL_VALUE;
                break;
            case MAY:
                    jump_value = MAY_VALUE;
                break;
            case JUNE:
                    jump_value = JUNE_VALUE;
                break;
            case JULY:
                    jump_value = JULY_VALUE;
                break;
            case AUGUST:
                    jump_value = AUGUST_VALUE;
                break;
            case SEPTEMBER:
                    jump_value = SEPTEMBER_VALUE;
                break;
            case OCTOBER:
                    jump_value = OCTOBER_VALUE;
                break;
            case NOVEMBER:
                    jump_value = NOVEMBER_VALUE;
                break;
            case DECEMBER:
                    jump_value = DECEMBER_VALUE;
                break;
        }

        // Manage overflow
        if(this->pTM.tm_mday < 0)
            {
            // Day overflow
            this->pTM.tm_mon--;
            this->pTM.tm_mday+= jump_value;

            // Month overflow
            if(this->pTM.tm_mon < 0)
                {
                this->pTM.tm_year--;
                this->pTM.tm_mon+= 12;
            }
        }
        else
        end = true;
    }

    this->pTM.tm_mon    -= iTM.tm_mon;
        if(this->pTM.tm_mon < 0)
            {
            while(this->pTM.tm_mon < 0)
                {
                this->pTM.tm_year--;
                this->pTM.tm_mon+= 12;
            }
        }

    this->pTM.tm_year   -= iTM.tm_year;

        // If bissextil
        if(
           iTM.tm_year > 0      && (this->pTM.tm_year % 4) == 0
        && this->pTM.tm_mon == 1&& this->pTM.tm_mday > 29
        ){
            this->pTM.tm_mday = this->pTM.tm_mday - 29;
        }

        // If bissextil
        else if(
            iTM.tm_year > 0         && (this->pTM.tm_year % 4) != 0
        &&  this->pTM.tm_mon == 1   && this->pTM.tm_mday > 28
        ){
            this->pTM.tm_mday = 28;
        }

    /*
    printf
        (
            "%d %d %d :: %d %d %d\n",
            this->pTM.tm_mday,
            this->pTM.tm_mon + 1,
            this->pTM.tm_year + 1900,
            this->pTM.tm_hour + 1,
            this->pTM.tm_min + 1,
            this->pTM.tm_sec + 1
        );*/
}

void HN_TimePoint::addInterval(HN_Interval &i)
{
    // Get time structure for calculate
    const struct tm &iTM = i.getInterval();

    printf("%d %d %d :: %d %d %d\n", this->pTM.tm_mday, this->pTM.tm_mon + 1, this->pTM.tm_year + 1900,
                        this->pTM.tm_hour + 1, this->pTM.tm_min + 1, this->pTM.tm_sec + 1);

    // Add time data
    this->pTM.tm_sec    += iTM.tm_sec;
        if(this->pTM.tm_sec > 59)
            {
            while(this->pTM.tm_sec > 59)
                {
                this->pTM.tm_min++;
                this->pTM.tm_sec-= 60;
            }
        }

    this->pTM.tm_min    += iTM.tm_min;
        if(this->pTM.tm_min > 59)
            {
            while(this->pTM.tm_min > 59)
                {
                this->pTM.tm_hour++;
                this->pTM.tm_min-= 60;
            }
        }

    this->pTM.tm_hour   += iTM.tm_hour;
        if(this->pTM.tm_hour > 23)
            {
            while(this->pTM.tm_hour > 23)
                {
                this->pTM.tm_mday++;
                this->pTM.tm_hour-= 24;
            }
        }

    // Add day data
    this->pTM.tm_mday   += iTM.tm_mday;
    bool end = false;
    int jump_value = 31;

    // Manage time
    while(!end)
    {
        // Detect month
        switch(this->pTM.tm_mon)
        {
            case JANUARY:
                    jump_value = JANUARY_VALUE;
                break;
            case FEBRUARY:
                    // Catch if sextil or bisextill
                    if((this->pTM.tm_year % 4) == 0)
                        jump_value = FEBRUARY_BISEXTILLE_VALUE;
                    else
                        jump_value = FEBRUARY_SEXTILLE_VALUE;
                break;
            case MARTCH:
                    jump_value = MARTCH_VALUE;
                break;
            case APRIL:
                    jump_value = APRIL_VALUE;
                break;
            case MAY:
                    jump_value = MAY_VALUE;
                break;
            case JUNE:
                    jump_value = JUNE_VALUE;
                break;
            case JULY:
                    jump_value = JULY_VALUE;
                break;
            case AUGUST:
                    jump_value = AUGUST_VALUE;
                break;
            case SEPTEMBER:
                    jump_value = SEPTEMBER_VALUE;
                break;
            case OCTOBER:
                    jump_value = OCTOBER_VALUE;
                break;
            case NOVEMBER:
                    jump_value = NOVEMBER_VALUE;
                break;
            case DECEMBER:
                    jump_value = DECEMBER_VALUE;
                break;
        }

        // Manage overflow
        if(this->pTM.tm_mday > jump_value)
            {
            // Day overflow
            this->pTM.tm_mon++;
            this->pTM.tm_mday-= jump_value;

            // Month overflow
            if(this->pTM.tm_mon > 11)
                {
                this->pTM.tm_year++;
                this->pTM.tm_mon-= 12;
            }
        }
        else
        end = true;
    }

    // Add month data
    this->pTM.tm_mon    += iTM.tm_mon;
        if(this->pTM.tm_mon > 11)
            {
            while(this->pTM.tm_mon > 11)
                {
                this->pTM.tm_year++;
                this->pTM.tm_mon-= 12;
            }
        }

    // Manage added interval
    this->pTM.tm_year   += iTM.tm_year;

        // If bissextil
        if(
           iTM.tm_year > 0      && (this->pTM.tm_year % 4) == 0
        && this->pTM.tm_mon == 1&& this->pTM.tm_mday > 29
        ){
            this->pTM.tm_mon++;
            this->pTM.tm_mday = this->pTM.tm_mday - 29;
        }

        // If bissextil
        else if(
            iTM.tm_year > 0         && (this->pTM.tm_year % 4) != 0
        &&  this->pTM.tm_mon == 1   && this->pTM.tm_mday == 29
        ){
            this->pTM.tm_mday = 28;
        }

        // If ssextil
        else if(
           iTM.tm_year > 0      && (this->pTM.tm_year % 4) != 0
        && this->pTM.tm_mon == 1&& this->pTM.tm_mday > 28
        ){
            this->pTM.tm_mon++;
            this->pTM.tm_mday = this->pTM.tm_mday - 29;
        }

    printf("%d %d %d :: %d %d %d", this->pTM.tm_mday, this->pTM.tm_mon + 1, this->pTM.tm_year + 1900,
                        this->pTM.tm_hour + 1, this->pTM.tm_min + 1, this->pTM.tm_sec + 1);
}

HN_Interval HN_TimePoint::operator-=(HN_TimePoint &t_2)
{
    struct tm __iTm;

    const struct tm &__tm = t_2.getTime();
    printf(
            "pTM time: %d/ %d/ %d %d:%d:%d\n",
            this->pTM.tm_mday,
            this->pTM.tm_mon + 1,
            this->pTM.tm_year + 1900,
            this->pTM.tm_hour,
            this->pTM.tm_min,
            this->pTM.tm_sec
        );
    printf(
            "__tm time: %d/ %d/ %d %d:%d:%d\n",
            __tm.tm_mday,
            __tm.tm_mon + 1,
            __tm.tm_year + 1900,
            __tm.tm_hour,
            __tm.tm_min,
            __tm.tm_sec
        );

    // Sub
    __iTm.tm_year = this->pTM.tm_year - __tm.tm_year;
    __iTm.tm_mon  = this->pTM.tm_mon - __tm.tm_mon;
    __iTm.tm_mday = this->pTM.tm_mday - __tm.tm_mday;
    __iTm.tm_hour = this->pTM.tm_hour - __tm.tm_hour;
    __iTm.tm_min = this->pTM.tm_min - __tm.tm_min;
    __iTm.tm_sec = this->pTM.tm_sec - __tm.tm_sec;

    while(__iTm.tm_mday < 1)
        {
        __iTm.tm_mon--;
        __iTm.tm_mday+= 30;
    }

    while(__iTm.tm_mon < 0)
        {
        __iTm.tm_year--;
        __iTm.tm_mon+= 12;
    }

     while(__iTm.tm_sec < 1)
        {
        __iTm.tm_min--;
        __iTm.tm_sec+= 60;
    }

    while(__iTm.tm_min < 1)
        {
        __iTm.tm_hour--;
        __iTm.tm_min+= 60;
    }

    while(__iTm.tm_hour < 1)
        {
        __iTm.tm_mday--;
        __iTm.tm_hour+= 24;
    }

    HN_Interval __i(
                    __iTm.tm_year, __iTm.tm_mon, __iTm.tm_mday,
                    __iTm.tm_hour, __iTm.tm_min, __iTm.tm_sec
                );
    return __i;
}


 // Methods
const struct tm &HN_TimePoint::getTime(void)
{
    return this->pTM;
}

time_t HN_TimePoint::getTimeStamp(void){
    return mktime(&this->pTM);
}

std::string HN_TimePoint::getAsString(void){

    char buff[260];
    sprintf(buff, "%d-%d-%d %d:%d:%d",
        this->pTM.tm_year + 1900,   this->pTM.tm_mon + 1,   this->pTM.tm_mday,
        this->pTM.tm_hour,          this->pTM.tm_min,       this->pTM.tm_sec
    );

    return buff;
}

 // Comparison operator
bool hnapi::datetime::operator<(HN_TimePoint &t1, HN_TimePoint &t2)
{
    return t1.isLesser(t2);
}

bool hnapi::datetime::operator<=(HN_TimePoint &t1, HN_TimePoint &t2)
{
    return t1.isLesserOrEqual(t2);
}

bool hnapi::datetime::operator==(HN_TimePoint &t1, HN_TimePoint &t2)
{
    return t1.isEqual(t2);
}

bool hnapi::datetime::operator>=(HN_TimePoint &t1, HN_TimePoint &t2)
{
    return t1.isGreaterOrEqual(t2);
}

bool hnapi::datetime::operator>(HN_TimePoint &t1, HN_TimePoint &t2)
{
    return t1.isGreater(t2);
}


 // Arithmetic operator
HN_TimePoint hnapi::datetime::operator+(HN_TimePoint &t, HN_Interval &i)
{
    HN_TimePoint tempTPoint(t);
        tempTPoint.addInterval(i);
    return tempTPoint;
}

HN_TimePoint hnapi::datetime::operator-(HN_TimePoint &t, HN_Interval &i)
{
    HN_TimePoint tempTPoint(t);
        tempTPoint.subInterval(i);
    return tempTPoint;
}

HN_Interval hnapi::datetime::operator-(HN_TimePoint &t_1, HN_TimePoint &t_2)
{
    HN_Interval __i = (t_1-= t_2);
    return __i;
}


