#ifndef LTIMER_H
#define LTIMER_H

#include "Function.h"
class LTimer
{
    public:
        LTimer();

        void start();
        void stop();
        void pause();
        void unpause();

        int getTicks();
        bool isStarted();
        bool isPaused();

    private:
        int mStartTicks;
        int mPausedTicks;

        bool mPaused;
        bool mStarted;
};

#endif