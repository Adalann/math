#include "Bernstein.h"
#include <iostream>

using namespace std;

class Polynome;

int factorielle(int n)
{
    if (n > 1)
        return n * factorielle(n - 1);
    else
        return 1;
}

int coef_binomial(int n, int k)
{
    if(n == 0 && k == 0)
        return 1;

    return factorielle(n) / (factorielle(k) * factorielle(n - k));
}

double bernstein(int degre, int indice, double t)
{
    double resultat = coef_binomial(degre, indice) * pow(t, indice) * pow(1 - t, degre - indice);

    return resultat;
}

Polynome bernstein(int degre, int indice)
{
    Polynome b;
    int j = 0;

    for(int i = 0; i <= degre; i++)
    {
        if(i < indice)
            b.add_coef(0);
        else
        {
            int multiplicateur = (j++ % 2 == 0 ? 1 : -1);
            if (indice != 0 && indice != degre)
                multiplicateur *= degre;
                
            b.add_coef(multiplicateur * coef_binomial(degre - indice, degre - i));
        }
    }

    // b.affiche_polynome("Bern :");

    return b;
}