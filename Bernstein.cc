#include "Bernstein.h"
#include <iostream>

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

Polynome bernstein(int degre, int indice)
{
    int coef_pascal[degre + 1][degre + 1];
    for (int i = 0; i <= degre - indice; i++)
    {
        coef_pascal[i][0] = 1;
        for(int j = 1; j < i; j++)
        {
            coef_pascal[i][0] = coef_pascal[i - 1][j] + coef_pascal[i - 1][j - 1];
            cout << coef_pascal[i][0] << " ";
        }
        cout << endl;
    }

    return Polynome();
}