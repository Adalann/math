#include "Bernstein.h"

using namespace std;

int factorielle(int i)
{
    if (i == 0)
        return 1;
    return i * factorielle(i - 1);
}

int coef_binomial(int n, int k)
{
    return factorielle(n) / (factorielle(k) * (factorielle(n - k)));
}

double bernstein(int degre, int indice, double t)
{
    double resultat = coef_binomial(degre, indice) * pow(t, indice) * pow(1 - t, degre - indice);

    return resultat;
}