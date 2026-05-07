#include "Time.h"

LARGE_INTEGER Time::frequency;
LARGE_INTEGER Time::Time_Start;
LARGE_INTEGER Time::Time_End;
double Time::Delta_Time;

void Time::Initialize() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&Time_Start);
}

void Time::Update() {
    QueryPerformanceCounter(&Time_End);
    Delta_Time = (double)(Time_End.QuadPart - Time_Start.QuadPart) / frequency.QuadPart;
    Time_Start = Time_End;
}

double Time::Get_Delta_Time() {
    return Delta_Time;
}