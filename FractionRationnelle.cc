#include "FractionRationnelle.h"
#include "Dessin.h"
#include "Casteljau.h"
#include <cmath>
#include <vector>
#include <iostream>

class Polynome;

using namespace std;

FractionRationnelle::FractionRationnelle()
{
    m_numerateur = Polynome();
    m_denominateur = Polynome();
    m_points_controle = vector<PointMassique>();
}

FractionRationnelle::FractionRationnelle(Polynome numerateur, Polynome denominateur)
{
    m_numerateur = numerateur;
    m_denominateur = denominateur;

    double tmp_coef[] = {0, 1, 0};
    Polynome X(tmp_coef, 3);

    vector<double> coef_X = X.passage_base_bernstein();
    vector<double> coef_Y = numerateur.passage_base_bernstein();
    vector<double> coef_Z = denominateur.passage_base_bernstein();

    for(int i = 0; i < coef_Y.size(); i++)
    {
        m_points_controle.push_back(PointMassique(coef_X[i], coef_Y[i], coef_Z[i]));
    }
}

FractionRationnelle::FractionRationnelle(const vector<double> &numerateur, const vector<double> &denominateur) : FractionRationnelle(Polynome(numerateur), Polynome(denominateur))
{

}

FractionRationnelle::FractionRationnelle(double num[], size_t taille_num, double denom[], size_t taille_denom) : FractionRationnelle(Polynome(num, taille_num), Polynome(denom, taille_denom))
{

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

    // Assymptote oblique
    if(m_numerateur.get_degre() == m_denominateur.get_degre() + 1)
    {
        Polynome oblique = Polynome::div_euclide(m_numerateur, m_denominateur);
        Point a(-100000, oblique.value_for(-100000));
        Point b(100000, oblique.value_for(100000));
        trace_segment(a, b, 0, 100, 0, 2);
    }
}

void FractionRationnelle::trace_courbe()
{
    de_casteljau(m_points_controle[0], m_points_controle[1], m_points_controle[2]);
}

string FractionRationnelle::to_s()
{
    string resultat = "";
    // resultat += m_numerateur.to_s() + " / " + m_denominateur.to_s();

    for(int i = 0; i < m_points_controle.size(); i++)
        m_points_controle[i].display();

    return resultat;
}
