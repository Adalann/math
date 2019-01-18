#include "FractionRationnelle.h"
#include "Dessin.h"
#include "Casteljau.h"
#include "Bernstein.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

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

    Polynome tQ = Polynome();
    for (int i = 0; i < 2; i++)
    {
        float c = (i == 1 ? 1. : 0.);
        tQ.add_coef(c);
    }
    tQ = tQ * m_denominateur;

    int degre_max = (m_numerateur.get_degre() >= m_denominateur.get_degre() ? m_numerateur.get_degre() : m_denominateur.get_degre());
    degre_max = (tQ.get_degre() >= degre_max ? tQ.get_degre() : degre_max);

    Polynome P(numerateur);
    while(P.get_degre() < degre_max)
        P.add_coef(0.);

    Polynome Q(denominateur);
    while(Q.get_degre() < degre_max)
        Q.add_coef(0.);

    vector<float> coef_P = P.passage_base_bernstein(degre_max);
    vector<float> coef_Q = Q.passage_base_bernstein(degre_max);
    vector<float> coef_tQ = tQ.passage_base_bernstein(degre_max);

    ofstream fichier_points("points.txt", ios::trunc);
    for(int i = 0; i <= degre_max; i++)
    {
        float diviseur = (coef_Q[i] == 0 ? 1 : coef_Q[i]);

        PointMassique p(PointMassique(coef_tQ[i] / diviseur, coef_P[i] / diviseur, coef_Q[i]));
        m_points_controle.push_back(p);
        fichier_points << p << endl;
    }
    fichier_points.close();
}

FractionRationnelle::FractionRationnelle(const vector<float> &numerateur, const vector<float> &denominateur) : FractionRationnelle(Polynome(numerateur), Polynome(denominateur))
{

}

FractionRationnelle::FractionRationnelle(float num[], size_t taille_num, float denom[], size_t taille_denom) : FractionRationnelle(Polynome(num, taille_num), Polynome(denom, taille_denom))
{

}

void FractionRationnelle::trace_assymptotes() const
{
    // Assymptote(s) verticale(s)
    float x1(0), x2(0);
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
        float y = m_numerateur.get_last_coef() / m_denominateur.get_last_coef();
        trace_segment(-100000, y, 100000, y, 0, 100, 0, 2);
    }

    // Assymptote oblique
    if (m_numerateur.get_degre() == m_denominateur.get_degre() + 1)
    {
        Polynome oblique = Polynome::div_euclide(m_numerateur, m_denominateur);
        Point a(-100000, oblique.value_for(-100000));
        Point b(100000, oblique.value_for(100000));
        trace_segment(a, b, 0, 100, 0, 2);
    }
}

void FractionRationnelle::trace_courbe() const
{
    if(m_points_controle.size() == 3)
        de_casteljau(m_points_controle[0], m_points_controle[1], m_points_controle[2]);
    else if(m_points_controle.size() == 4)
        de_casteljau(m_points_controle[0], m_points_controle[1], m_points_controle[2], m_points_controle[3]);
}

void FractionRationnelle::changement_homographique() const
{
    float a(0.0), b(0.0), c(0.0), d(0.0), x1(0.0), x2(0.0);
    int nb_racines(0);

    PointMassique Q0, Q1, Q2, Q3;

    nb_racines = m_denominateur.solve(x1, x2);

    if (nb_racines == 0 || (nb_racines == 1 && x1 == 0.0))
    {
        // On trace de -inf a 0
        PointMassique pts[3];

        a = -1; b = 0; c = 0; d = 1;

        pts[0] = (m_points_controle[0] * pow(c - a, 2)) + (m_points_controle[1] * 2 * a * (c - a)) + (m_points_controle[2] * a * a);
        pts[1] = (m_points_controle[0] * (c - a) * (d - b)) + (m_points_controle[1] * (b * c - 2 * a * b + a * d)) + (m_points_controle[2] * (a * b));
        pts[2] = (m_points_controle[0] * pow(d - b, 2)) + (m_points_controle[1] * 2 * b * (d - b)) + (m_points_controle[2] * b * b);

        cout << "-inf to 0" << endl;
        cout << pts[0] << endl;
        cout << pts[1] << endl;
        cout << pts[2] << endl;

        de_casteljau(pts[0], pts[1], pts[2]);

        // On trace de 0 a +inf
        a = 0; b = 1; c = 1; d = 0;

        pts[0] = (m_points_controle[0] * pow(c - a, 2)) + (m_points_controle[1] * 2 * a * (c - a)) + (m_points_controle[2] * a * a);
        pts[1] = (m_points_controle[0] * (c - a) * (d - b)) + (m_points_controle[1] * (b * c - 2 * a * b + a * d)) + (m_points_controle[2] * (a * b));
        pts[2] = (m_points_controle[0] * pow(d - b, 2)) + (m_points_controle[1] * 2 * b * (d - b)) + (m_points_controle[2] * b * b);

        cout << "0 to +inf" << endl;
        cout << pts[0] << endl;
        cout << pts[1] << endl;
        cout << pts[2] << endl;

        de_casteljau(pts[0], pts[1], pts[2]);
    }
    else if (nb_racines ==  2)
    {
        a = -1; b = -6; c = 0; d = 2;

        Q0 = m_points_controle[0] * pow(c - a, 3) + m_points_controle[1] * 3 * a * pow(c - a, 2) + m_points_controle[2] * 3 * a * a * (c - a) + m_points_controle[3] * a * a * a;
        Q1 = m_points_controle[0] * pow(c - a, 2) * (d - b) + m_points_controle[1] * (2 * a * (c - a) * (d - b) + b * pow(c - a, 2)) + m_points_controle[2] * (2 * a * b * (c - a) + a * a * (d - b)) + m_points_controle[3] * a * a * b;
        Q2 = m_points_controle[0] * pow(d - b, 2) * (c - a) + m_points_controle[1] * (2 * b * (c - a) * (d - b) + a * pow(d - b, 2)) + m_points_controle[2] * (2 * a * b * (d - b) + b * b * (c - a)) + m_points_controle[3] * a * b * b;
        Q3 = m_points_controle[0] * pow(d - b, 3) + m_points_controle[1] * 3 * b * pow(d - b, 2) + m_points_controle[2] * 3 * b * b * (d - b) + m_points_controle[3] * b * b * b;

        de_casteljau(Q0, Q1, Q2, Q3);

        a = -6; b = 1; c = 2; d = 1;

        Q0 = m_points_controle[0] * pow(c - a, 3) + m_points_controle[1] * 3 * a * pow(c - a, 2) + m_points_controle[2] * 3 * a * a * (c - a) + m_points_controle[3] * a * a * a;
        Q1 = m_points_controle[0] * pow(c - a, 2) * (d - b) + m_points_controle[1] * (2 * a * (c - a) * (d - b) + b * pow(c - a, 2)) + m_points_controle[2] * (2 * a * b * (c - a) + a * a * (d - b)) + m_points_controle[3] * a * a * b;
        Q2 = m_points_controle[0] * pow(d - b, 2) * (c - a) + m_points_controle[1] * (2 * b * (c - a) * (d - b) + a * pow(d - b, 2)) + m_points_controle[2] * (2 * a * b * (d - b) + b * b * (c - a)) + m_points_controle[3] * a * b * b;
        Q3 = m_points_controle[0] * pow(d - b, 3) + m_points_controle[1] * 3 * b * pow(d - b, 2) + m_points_controle[2] * 3 * b * b * (d - b) + m_points_controle[3] * b * b * b;

        de_casteljau(Q0, Q1, Q2, Q3);

        a = 1; b = 3; c = 1; d = 0;

        Q0 = m_points_controle[0] * pow(c - a, 3) + m_points_controle[1] * 3 * a * pow(c - a, 2) + m_points_controle[2] * 3 * a * a * (c - a) + m_points_controle[3] * a * a * a;
        Q1 = m_points_controle[0] * pow(c - a, 2) * (d - b) + m_points_controle[1] * (2 * a * (c - a) * (d - b) + b * pow(c - a, 2)) + m_points_controle[2] * (2 * a * b * (c - a) + a * a * (d - b)) + m_points_controle[3] * a * a * b;
        Q2 = m_points_controle[0] * pow(d - b, 2) * (c - a) + m_points_controle[1] * (2 * b * (c - a) * (d - b) + a * pow(d - b, 2)) + m_points_controle[2] * (2 * a * b * (d - b) + b * b * (c - a)) + m_points_controle[3] * a * b * b;
        Q3 = m_points_controle[0] * pow(d - b, 3) + m_points_controle[1] * 3 * b * pow(d - b, 2) + m_points_controle[2] * 3 * b * b * (d - b) + m_points_controle[3] * b * b * b;

        de_casteljau(Q0, Q1, Q2, Q3);
    }
}

string FractionRationnelle::to_s() const
{
    string resultat = "";

    for(int i = 0; i < m_points_controle.size(); i++)
        m_points_controle[i].display();

    return resultat;
}


