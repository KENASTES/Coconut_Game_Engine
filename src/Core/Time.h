#ifndef TIME_H
#define TIME_H

#include <windows.h>

class Time {
    private:
    static LARGE_INTEGER frequency;
    static LARGE_INTEGER Time_Start;
    static LARGE_INTEGER Time_End;
    static double Delta_Time;

    public:
    static void Initialize();
    static void Update();
    static double Get_Delta_Time();
};

#endif