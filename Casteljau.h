#include "PointMassique.h"

// Pour les courbes polynomiales
void de_casteljau(const Point &P0, const Point &P1, const Point &P2, int reccursion_level = 10, double t = 0.5, int reccursion_cout = 0);
void de_casteljau(const Point &P0, const Point &P1, const Point &P2, const Point &P3, int reccursion_level = 10, double t = 0.5, int reccursion_cout = 0);

// Pour les courbes rationnelles
void de_casteljau(const PointMassique &P0, const PointMassique &P1, const PointMassique &P2, int reccursion_level = 10, double t = 0.5, int reccursion_cout = 0);
void de_casteljau(const PointMassique &P0, const PointMassique &P1, const PointMassique &P2, const PointMassique &P3, int reccursion_level = 10, double t = 0.5, int reccursion_cout = 0);
