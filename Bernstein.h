#ifndef BERNSTEIN_H
#define BERNSTEIN_H

#include "Polynome.h"
#include <cmath>

#include "Bernstein.h"

int factorielle(int n);
int coef_binomial(int n, int k);

double bernstein(int degre, int indice, double t);
Polynome bernstein(int degre, int indice);

#endif