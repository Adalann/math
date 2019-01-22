#include "PointMassique.h"
#include <vector>
#define RECURSION_LEVEL 15

// Pour les courbes rationnelles
void de_casteljau(const PointMassique &P0, const PointMassique &P1, const PointMassique &P2, int recursion_level = RECURSION_LEVEL, float t = 0.5, int recursion_cout = 0);
void de_casteljau(const PointMassique &P0, const PointMassique &P1, const PointMassique &P2, const PointMassique &P3, int recursion_level = RECURSION_LEVEL, float t = 0.5, int recursion_cout = 0);

void trace_courbe_3(std::vector<PointMassique> points);