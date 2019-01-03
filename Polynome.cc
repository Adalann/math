#include "Polynome.h"
#include <iostream>
#include <cmath>

using namespace std;

Polynome::Polynome()
{
    m_coeficients = vector<double>(1);
}

Polynome::Polynome(int degre)
{
    for(int i = 0; i < degre + 1; i++)
        m_coeficients.push_back(1);
}

Polynome::Polynome(const Polynome &original)
{
    m_coeficients = original.m_coeficients;
}

Polynome::Polynome(vector<double> coeficients)
{
    for (int i = coeficients.size() - 1; i >= 0; i--)
        m_coeficients.push_back(coeficients[i]);
}

Polynome::Polynome(double coeficients[], size_t taille)
{
    for(int i = taille - 1; i >= 0; i--)
        m_coeficients.push_back(coeficients[i]);
}

int Polynome::get_degre()
{
    return m_coeficients.size() - 1;
}

int Polynome::solve(double &x1, double &x2)
{
    int nb_solution = -1;

    if(get_degre() == 2)
    {
        double delta = (m_coeficients[1] * m_coeficients[1]) - (4 * m_coeficients[0] * m_coeficients[2]);

        if (delta < 0)
            nb_solution = 0;
        else if (delta == 0)
        {
            x1 = x2 = -(m_coeficients[1] / (2 * m_coeficients[2]));
            nb_solution = 1;
        }
        else
        {
            x1 = (-m_coeficients[1] + sqrt(delta)) / (2 * m_coeficients[2]);
            x2 = (-m_coeficients[1] - sqrt(delta)) / (2 * m_coeficients[2]);
            nb_solution = 2;
        }
    }
    else if(get_degre() == 1)
    {
        x1 = x2 = -m_coeficients[1] / m_coeficients[2];
        nb_solution = 1;
    }

    return nb_solution;
}

double Polynome::get_last_coef()
{
    return m_coeficients.back();
}

vector<double> Polynome::get_coefs() const
{
    return m_coeficients;
}

Polynome& Polynome::operator-=(const Polynome &p)
{
    int size_membre_a = m_coeficients.size();
    int size_membre_b = p.m_coeficients.size();
    int limite = (size_membre_a < size_membre_b ? size_membre_a : size_membre_b);

    for (int i = 0; i < limite; i++)
    {
        m_coeficients[i] -= p.m_coeficients[i];
    }

    if (size_membre_a < size_membre_b)
    {
        for(int i = limite; i < size_membre_b; i++)
            m_coeficients.push_back(-p.m_coeficients[i]);
    }

    return *this;
}

Polynome& Polynome::operator*=(const Polynome &p)
{
    for(int i = 0; i < get_degre(); i++)
    {

    }
    
    return *this;
}

string Polynome::to_s()
{
    string resultat = "";

    for (int i = m_coeficients.size() - 1; i > 0; i--)
    {
        if (m_coeficients[i] > 0)
            resultat += "+";

        if (m_coeficients[i] != 0)
        {
            resultat += m_coeficients[i];
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
    for (int i = m_coeficients.size() - 1; i >= 0; i--)
        cout << m_coeficients[i] << " ";
    cout << endl;
}

void Polynome::decalage(int puissance, double coeficient = 1.0)
{
    if(puissance == 0)
    {
        for(int i = 0; i < m_coeficients.size(); i++)
            m_coeficients[i] *= coeficient;
    }
    else if(puissance > 0)
    {
        for(int i = 0; i < puissance; i++)
            m_coeficients.insert(0, 0);
    }
}

Polynome operator-(Polynome const &p1, Polynome const &p2)
{
    Polynome copie(p1);
    copie -= p2;

    return copie;
}

Polynome operator*(Polynome const &p1, Polynome const &p2)
{
    Polynome copie(p1);
    copie *= p2;

    return copie;
}

// Division euclidienne de P par M
Polynome div_euclide(Polynome &P, Polynome &M)
{
    Polynome Q(1), R(P);
    int curseur = 1;

    while(R.get_degre() >= M.get_degre())
    {
        Q.m_coeficients[i] = R.m_coeficients[i + 1] / M.m_coeficients[i];
        R = R - Q * M;
    }

    return Q;
}