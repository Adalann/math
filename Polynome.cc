#include "Polynome.h"
#include "Bernstein.h"
#include <iostream>
#include <cmath>

using namespace std;

// void reverse_vector(vector<float> &v);

Polynome::Polynome()
{
    m_coefficients = vector<float>();
}

Polynome::Polynome(int degre)
{
    for(int i = 0; i < degre; i++)
        m_coefficients.push_back(0.);

    m_coefficients.push_back(1.);
}

Polynome::Polynome(const Polynome &original)
{
    m_coefficients = original.m_coefficients;
}

Polynome::Polynome(const Polynome &original, int degre_limite)
{
    for(int i = 0; i < degre_limite; i++)
        m_coefficients.push_back(0);

    m_coefficients.push_back(original.m_coefficients[degre_limite]);
}

Polynome::Polynome(vector<float> coefficients)
{
    for (int i = coefficients.size() - 1; i >= 0; i--)
        m_coefficients.push_back(coefficients[i]);
}

Polynome::Polynome(float coefficients[], size_t taille)
{
    for(int i = taille - 1; i >= 0; i--)
        m_coefficients.push_back(coefficients[i]);
}

void Polynome::normalize()
{
    while(m_coefficients.back() == 0)
        m_coefficients.pop_back();
}

int Polynome::get_degre() const
{
    return m_coefficients.size() - 1;
}

int Polynome::solve(float &x1, float &x2) const
{
    int nb_solution = -1;

    if(get_degre() == 2)
    {
        float delta = (m_coefficients[1] * m_coefficients[1]) - (4 * m_coefficients[0] * m_coefficients[2]);

        if (delta < 0)
            nb_solution = 0;
        else if (delta == 0)
        {
            x1 = x2 = -(m_coefficients[1] / (2 * m_coefficients[2]));
            nb_solution = 1;
        }
        else
        {
            x1 = (-m_coefficients[1] + sqrt(delta)) / (2 * m_coefficients[2]);
            x2 = (-m_coefficients[1] - sqrt(delta)) / (2 * m_coefficients[2]);
            nb_solution = 2;
        }
    }
    else if(get_degre() == 1)
    {
        x1 = x2 = -m_coefficients[0] / m_coefficients[1];
        nb_solution = 1;
    }

    return nb_solution;
}

float Polynome::get_last_coef() const
{
    return m_coefficients.back();
}

float Polynome::get_coef_puissance(int d) const
{
    float c = 0;

    if (d < m_coefficients.size())
        c = m_coefficients[d];
    else
        cout << "Error, polynome degre = " << get_degre() << ", requested degre = " << d << endl;

    return c;
}

vector<float> Polynome::get_coefs() const
{
    return m_coefficients;
}

void Polynome::add_coef(float c)
{
    m_coefficients.push_back(c);
}

float Polynome::value_for(float x) const
{
    float resultat = 0;

    for(int i = 0; i < m_coefficients.size(); i++)
        resultat += m_coefficients[i] * pow(x, i);
    
    return resultat;
}

Polynome& Polynome::operator+=(const Polynome &p)
{
    int size_membre_a = m_coefficients.size();
    int size_membre_b = p.m_coefficients.size();
    int limite = (size_membre_a < size_membre_b ? size_membre_a : size_membre_b);

    for (int i = 0; i < limite; i++)
    {
        m_coefficients[i] += p.m_coefficients[i];
    }

    if (size_membre_a < size_membre_b)
    {
        for(int i = limite; i < size_membre_b; i++)
            m_coefficients.push_back(p.m_coefficients[i]);
    }

    return *this;
}

Polynome& Polynome::operator-=(const Polynome &p)
{
    int size_membre_a = m_coefficients.size();
    int size_membre_b = p.m_coefficients.size();
    int limite = (size_membre_a < size_membre_b ? size_membre_a : size_membre_b);

    for (int i = 0; i < limite; i++)
    {
        m_coefficients[i] -= p.m_coefficients[i];
    }

    if (size_membre_a < size_membre_b)
    {
        for(int i = limite; i < size_membre_b; i++)
            m_coefficients.push_back(-p.m_coefficients[i]);
    }

    while(m_coefficients.back() == 0.)
        m_coefficients.pop_back();

    return *this;
}

void Polynome::decalage(int puissance, float coefficient = 1.0)
{
    if (puissance == 0)
    {
        for (int i = 0; i < m_coefficients.size(); i++)
        {
            if (m_coefficients[i] != 0)
                m_coefficients[i] *= coefficient;
        }
    }
    else if (puissance > 0)
    {
        for (int i = 0; i < puissance; i++)
            m_coefficients.insert(m_coefficients.begin(), 0);

        for (int i = 0; i < m_coefficients.size(); i++)
            if (m_coefficients[i] != 0)
                m_coefficients[i] *= coefficient;
    }
}

string Polynome::to_s()
{
    string resultat = "";

    for (int i = m_coefficients.size() - 1; i > 0; i--)
    {
        if (m_coefficients[i] > 0)
            resultat += "+";

        if (m_coefficients[i] != 0)
        {
            resultat += m_coefficients[i];
            resultat += "x^";
            resultat += i;
            resultat += " ";
        }
    }

    return resultat;
}

void Polynome::affiche_polynome()
{
    // cout << to_s() << endl;
    for (int i = m_coefficients.size() - 1; i >= 0; i--)
        cout << m_coefficients[i] << " ";
    cout << endl;
}

void Polynome::affiche_polynome(string message)
{
    // cout << to_s() << endl;
    cout << message << " ";
    for (int i = m_coefficients.size() - 1; i >= 0; i--)
        cout << m_coefficients[i] << " ";
    cout << endl;
}

Polynome operator+(Polynome const &p1, Polynome const &p2)
{
    Polynome copie(p1);
    copie += p2;

    return copie;
}

Polynome operator-(Polynome const &p1, Polynome const &p2)
{
    Polynome copie(p1);
    copie -= p2;

    return copie;
}

Polynome operator*(Polynome const &p1, Polynome const &p2)
{
    Polynome resultat;

    for(int i = 0; i <= p1.get_degre(); i++)
    {
        Polynome tmp;
        tmp.decalage(i);
        for(int j = 0; j <= p2.get_degre(); j++)
        {
            float d = p1.get_coefs()[i] * p2.get_coefs()[j];
            tmp.add_coef(d);
        }
        resultat += tmp;
    }

    return resultat;
}

// Division euclidienne de P par M
Polynome Polynome::div_euclide(const Polynome &P, const Polynome &M)
{
    Polynome Q(1), R(P);
    int curseur_Q(1);

    while (R.get_degre() >= M.get_degre())
    {
        Q.m_coefficients[curseur_Q] = R.m_coefficients[R.get_degre()] / M.m_coefficients[M.get_degre()];
        Polynome multiplicateur(Q, curseur_Q--);
        R -= multiplicateur * M;
    }

    return Q;
}

vector<float> Polynome::passage_base_bernstein(int degre) const
{
    vector<Polynome> polynomes_bernstein;
    vector<float> coefs_base_bernstein;
    Polynome p = bernstein(degre, 0);
    float coef(0);
    float alpha(0), beta(0), gamma(0), delta(0);

    coefs_base_bernstein.push_back(m_coefficients[0]);
    alpha = m_coefficients[0];

    polynomes_bernstein.push_back(p);

    for (int i = 1; i <= degre; i++)
    {
        p = bernstein(degre, i);
        polynomes_bernstein.push_back(p);

        switch(i)
        {
            case 1:
                coef = (m_coefficients[i] - polynomes_bernstein[0].get_coef_puissance(i) * alpha) / polynomes_bernstein[i].get_coef_puissance(i);
                beta = coef;
                break;
            case 2:
                coef = (m_coefficients[i] - polynomes_bernstein[0].get_coef_puissance(i) * alpha - polynomes_bernstein[1].get_coef_puissance(i) * beta) / polynomes_bernstein[i].get_coef_puissance(i);
                gamma = coef;
                break;
            case 3:
                coef = (m_coefficients[i] - polynomes_bernstein[0].get_coef_puissance(i) * alpha - polynomes_bernstein[1].get_coef_puissance(i) * beta - polynomes_bernstein[2].get_coef_puissance(i) * gamma) / polynomes_bernstein[i].get_coef_puissance(i);
                delta = coef;
                break;
        }

        coefs_base_bernstein.push_back(coef);
    }

    return coefs_base_bernstein;
}