#include "FractionRationnelle.h"
#include "Dessin.h"
#include "Casteljau.h"
#include "Bernstein.h"
#include <cmath>
#include <vector>
#include <iostream>

#define PAS 0.0001

class Polynome;

using namespace std;

FractionRationnelle::FractionRationnelle()
{
    m_numerateur = Polynome();
    m_denominateur = Polynome();
    m_points_controle = vector<PointMassique>();
}

FractionRationnelle::FractionRationnelle(PointMassique p1, PointMassique p2, PointMassique p3, PointMassique p4) : FractionRationnelle()
{
    m_points_controle.push_back(p1);
    m_points_controle.push_back(p2);
    m_points_controle.push_back(p3);
    m_points_controle.push_back(p4);
}

FractionRationnelle::FractionRationnelle(Polynome numerateur, Polynome denominateur)
{
    m_numerateur = numerateur;
    m_denominateur = denominateur;
    m_points_controle = vector<PointMassique>();
    vector<vector<double>> coefs;

    Polynome X = Polynome();
    for (int i = 0; i < 2; i++)
    {
        double c = (i == 1 ? 1. : 0.);
        X.add_coef(c);
    }
    X.affiche_polynome("X avant :");
    X = X * m_denominateur;
    m_denominateur.affiche_polynome("Z :");
    X.affiche_polynome("X apres:");

    int degre_max = (m_numerateur.get_degre() >= m_denominateur.get_degre() ? m_numerateur.get_degre() : m_denominateur.get_degre());
    degre_max = (X.get_degre() >= degre_max ? X.get_degre() : degre_max);

    Polynome Y(numerateur);
    while(Y.get_degre() < degre_max)
        Y.add_coef(0.);

    Polynome Z(denominateur);
    while(Z.get_degre() < degre_max)
        Z.add_coef(0.);

    coefs.push_back(X.passage_base_bernstein());
    coefs.push_back(Y.passage_base_bernstein());
    coefs.push_back(Z.passage_base_bernstein());

    for(int i = 0; i <= degre_max; i++)
    {
        PointMassique p(PointMassique(coefs[0][i], coefs[1][i], coefs[2][i]));
        m_points_controle.push_back(p);
        p.display();
    }
}

FractionRationnelle::FractionRationnelle(const vector<double> &numerateur, const vector<double> &denominateur) : FractionRationnelle(Polynome(numerateur), Polynome(denominateur))
{

}

FractionRationnelle::FractionRationnelle(double num[], size_t taille_num, double denom[], size_t taille_denom) : FractionRationnelle(Polynome(num, taille_num), Polynome(denom, taille_denom))
{

}

void FractionRationnelle::assymptote_h() const
{
    double res = 0;
}

void FractionRationnelle::trace_assymptotes() const
{
    // Assymptote(s) verticale(s)
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

// double FractionRationnelle::w_f(double t) const
// {
//     double res = 0;

//     for(int i = 0; i < m_points_controle.size(); i++)
//     {

//     }
// }

void FractionRationnelle::trace_courbe() const
{
    
    for(int i = 0; i < m_points_controle.size(); i++)
    {
        trace_point(m_points_controle[i], 0., 0., 0., 5);
        if(i < m_points_controle.size() - 1)
            trace_segment(m_points_controle[i], m_points_controle[i + 1], 0., 255., 100., 2.);
    }

    // de_casteljau(m_points_controle[0], m_points_controle[1], m_points_controle[2]);
    int degre_max = (m_numerateur.get_degre() >= m_denominateur.get_degre() ? m_numerateur.get_degre() : m_denominateur.get_degre());
    degre_max = (degre_max >= m_denominateur.get_degre() + 1 ? degre_max : m_denominateur.get_degre() + 1);

    for (double t = PAS; t < 1; t += PAS)
    {
        double x(0), y(0);

        for (int i = 0; i < m_points_controle.size(); i++)
        {
            double B = bernstein(degre_max, i).value_for(t);
            if (m_points_controle[i].getW() != 0)
            {
                x += (m_points_controle[i].getW() * B * m_points_controle[i].getX());
                y += (m_points_controle[i].getW() * B * m_points_controle[i].getY());
            }
            else
            {
                x += (B * m_points_controle[i].getX());
                y += (B * m_points_controle[i].getY());
            }
        }

        double diviseur(1);
        for (int i = 0; i < m_points_controle.size(); i++)
            diviseur += bernstein(degre_max, i).value_for(t) * m_points_controle[i].getW();

        x /= diviseur;
        y /= diviseur;

        trace_point(x, y, 0, 0., 255., 2);
    }
}

string FractionRationnelle::to_s() const
{
    string resultat = "";
    // resultat += m_numerateur.to_s() + " / " + m_denominateur.to_s();

    for(int i = 0; i < m_points_controle.size(); i++)
        m_points_controle[i].display();

    return resultat;
}


