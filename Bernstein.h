#ifndef BERNSTEIN_H
#define BERNSTEIN_H

#include "Polynome.h"
#include <cmath>

#include "Bernstein.h"

int factorielle(int n);
int coef_binomial(int n, int k);

float bernstein(int degre, int indice, float t);
Polynome bernstein(int degre, int indice);

#endif