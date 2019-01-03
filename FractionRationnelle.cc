#include "FractionRationnelle.h"
#include "Dessin.h"
#include <cmath>
#include <vector>
#include <iostream>

class Polynome;

using namespace std;

FractionRationnelle::FractionRationnelle()
{
    m_numerateur = Polynome();
    m_denominateur = Polynome();
}

FractionRationnelle::FractionRationnelle(Polynome numerateur, Polynome denominateur)
{
    m_numerateur = numerateur;
    m_denominateur = denominateur;
}

FractionRationnelle::FractionRationnelle(const vector<double> &numerateur, const vector<double> &denominateur)
{
    m_numerateur = Polynome(numerateur);
    m_denominateur = Polynome(denominateur);
}

FractionRationnelle::FractionRationnelle(double num[], size_t taille_num, double denom[], size_t taille_denom)
{
    m_numerateur = Polynome(num, taille_num);
    m_denominateur = Polynome(denom, taille_denom);
}

void FractionRationnelle::assymptote_h()
{
    double res = 0;
}

void FractionRationnelle::trace_assymptotes()
{
    // Assymptote verticale(s)
    double x1(0), x2(0);
    int nb_racine = m_denominateur.solve(x1, x2);
    if(nb_racine == 1)
        trace_segment(x1, -100000, x1, 100000, 0, 200, 0, 2);
    else if(nb_racine == 2)
    {
        trace_segment(x1, -100000, x1, 100000, 0, 200, 0, 2);
        trace_segment(x2, -100000, x2, 100000, 0, 200, 0, 2);
    }

    // Assymptote horizontale
    if (m_numerateur.get_degre() == m_denominateur.get_degre())
    {
        double y = m_numerateur.get_last_coef() / m_denominateur.get_last_coef();
        trace_segment(-100000, y, 100000, y, 0, 100, 0, 2);
    }
}

string FractionRationnelle::to_s()
{
    string resultat = "";
    resultat += m_numerateur.to_s() + " / " + m_denominateur.to_s();

    return resultat;
}
