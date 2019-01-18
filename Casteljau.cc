#include "Casteljau.h"
#include <iostream>

using namespace std;

void de_casteljau(const PointMassique &P0, const PointMassique &P1, const PointMassique &P2, int recursion_level, float t, int recursion_cout)
{
    PointMassique N0;
    PointMassique N1;
    
    PointMassique C;

    N0 = (P0 * (1 - t)) + (P1 * t);
    N1 = (P1 * (1 - t)) + (P2 * t);
    
    C = (N0 * (1 - t)) + (N1 * t);

    C.trace(2);

    if(recursion_cout != recursion_level)
    {
        de_casteljau(P0, N0, C, recursion_level, t, recursion_cout + 1);
        de_casteljau(C, N1, P2, recursion_level, t, recursion_cout + 1);
    }
}

void de_casteljau(const PointMassique &P0, const PointMassique &P1, const PointMassique &P2, const PointMassique &P3, int recursion_level, float t, int recursion_cout)
{
    PointMassique N0;
    PointMassique N1;
    PointMassique N2;
    
    PointMassique M0;
    PointMassique M1;

    PointMassique C;

    N0 = (P0 * (1 - t)) + (P1 * t);
    N1 = (P1 * (1 - t)) + (P2 * t);
    N2 = (P2 * (1 - t)) + (P3 * t);

    M0 = (N0 * (1 - t)) + (N1 * t);
    M1 = (N1 * (1 - t)) + (N2 * t);

    C = (M0 * (1 - t)) + (M1 * t);

    C.trace(2);

    if(recursion_cout != recursion_level)
    {
        de_casteljau(P0, N0, M0, C, recursion_level, t, recursion_cout + 1);
        de_casteljau(C, M1, N2, P3, recursion_level, t, recursion_cout + 1);
    }
}