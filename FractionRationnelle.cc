#include "FractionRationnelle.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

FractionRationnelle::FractionRationnelle()
{
    numerateur.push_back(1);
    denominateur.push_back(1);
}

FractionRationnelle::FractionRationnelle(double num[], size_t taille_num, double denom[], size_t taille_denom)
{
    for (int i = 0; i < taille_num; i++)
        numerateur.push_back(num[i]);

    for (int i = 0; i < taille_denom; i++)
        denominateur.push_back(denom[i]);
}

int FractionRationnelle::solve_denom(double &x1, double &x2)
{
    int degre = FractionRationnelle::get_degre(true);

    if(degre == 2)
    {
        double delta = pow(denominateur[1], 2) - 4 * denominateur[2] * denominateur[0];

        if(delta < 0)
            return 0;
        else if(delta == 0)
        {
            x1 = x2 = -(denominateur[1] / (2 * denominateur[2]));
            return 1;
        }
        else
        {
            x1 = (-denominateur[1] + sqrt(delta)) / (2 * denominateur[2]);
            x2 = (-denominateur[1] - sqrt(delta)) / (2 * denominateur[2]);

            return 2;
        }
    }
    else if(degre == 1)
    {
        x1 = x2 = -denominateur[1] / denominateur[2];
        return 1;
    }

    return -1;
}

double FractionRationnelle::assymptote_h()
{
    double res = 0;

    if(get_degre() == get_degre(true))
    {
        res = numerateur.back() / denominateur.back();
    }

    return res;
}


int FractionRationnelle::get_degre(bool select)
{
    if(select)
    {
        return denominateur.size() - 1;
    }
    else
    {
        return numerateur.size() - 1;
    }
}


string FractionRationnelle::to_s()
{
    string res = "numérateur : ";
    for (int i = 0; i < numerateur.size(); i++)
        res += std::to_string(numerateur[i]) + " ";

    res += "\ndenominateur : ";
    for (int i = 0; i < denominateur.size(); i++)
        res += std::to_string(denominateur[i]) + " ";

    return res;
}
