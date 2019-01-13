#include "PointMassique.h"
#define RECURSION_LEVEL 15

// Pour les courbes polynomiales
void de_casteljau(const Point &P0, const Point &P1, const Point &P2, int recursion_level = RECURSION_LEVEL, float t = 0.5, int recursion_cout = 0);
void de_casteljau(const Point &P0, const Point &P1, const Point &P2, const Point &P3, int recursion_level = RECURSION_LEVEL, float t = 0.5, int recursion_cout = 0);

// Pour les courbes rationnelles
void de_casteljau(const PointMassique &P0, const PointMassique &P1, const PointMassique &P2, int recursion_level = RECURSION_LEVEL, float t = 0.5, int recursion_cout = 0);
void de_casteljau(const PointMassique &P0, const PointMassique &P1, const PointMassique &P2, const PointMassique &P3, int recursion_level = RECURSION_LEVEL, float t = 0.5, int recursion_cout = 0);
