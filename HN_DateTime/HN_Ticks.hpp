#ifndef HN_TICKS_HPP_INCLUDED
#define HN_TICKS_HPP_INCLUDED

    #include "HN_Clock.hpp"

namespace hnapi
{
    namespace datetime
    {
        // //Ticks state
        enum TICKS_STATE{BEFORE_TICKS, TICKSING, AFTER_TICKS, NO_TICKS};

        // Ticks class
        class HN_Ticks
        {
            public:
                // Builder
                HN_Ticks();

                // Ticks methods
                void now(void);
                void setInterval(HN_ClockPoint _micro);
                void addInterval(HN_ClockPoint _micro);
                void subInterval(HN_ClockPoint _micro);

                // Get methods for BSD platform only
                HN_ClockPoint getRest(void);
                HN_ClockPoint getCurrent(void);
                enum TICKS_STATE &getState(void);

                // Destroyer
                ~HN_Ticks();
            private:
                // Time pointer
                HN_ClockPoint beginTime;
                HN_ClockPoint currentRest;
                HN_ClockPoint endTime;

                // Ticks state
                enum TICKS_STATE state;
        };
    }
}

#endif // HN_TICKS_HPP_INCLUDED
