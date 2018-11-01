#include "Polynome.h"
#include <cmath>

using namespace std;

Polynome::Polynome()
{
    for(int i = 0; i < 3; i++)
    {
        numerateur[i]   = 0;
        denominateur[i] = 0;
    }

    numerateur[3]   = 1;
    denominateur[3] = 1;
}

Polynome::Polynome(double num[], double denom[])
{
    for(int i = 0; i < 4; i++)
    {
        numerateur[i]   = num[i];
        denominateur[i] = denom[i];
    }
}

int Polynome::solve_denom(double &x1, double &x2)
{
    int degre = Polynome::get_degre(true);

    if(degre == 2)
    {
        double delta = pow(denominateur[2], 2) - 4 * denominateur[1] * denominateur[3];

        if(delta < 0)
            return 0;
        else if(delta == 0)
        {
            x1 = x2 = denominateur[2] / 2 * denominateur[1];
            return 1;
        }
        else
        {
            x1 = (-denominateur[2] + sqrt(delta)) / 2 * denominateur[1];
            x2 = (-denominateur[2] - sqrt(delta)) / 2 * denominateur[1];

            return 2;
        }
    }
    else if(degre == 1)
    {
        x1 = x2 = -denominateur[3] / denominateur[2];
        return 1;
    }
}

int Polynome::get_degre(bool select = false)
{
    if(select)
    {
        int i = 0;
        while(denominateur[i] == 0. && i < 4)
            i++;
        return 3 - i;
    }
    else
    {
        int i = 0;
        while (numerateur[i] == 0. && i < 4)
            i++;
        return 3 - i;
    }
}

string Polynome::to_s()
{
    string res = "numérateur : ";
    for (int i = 0; i < 4; i++)
        res += std::to_string(numerateur[i]) + " ";

    res += "\ndenominateur : ";
    for (int i = 0; i < 4; i++)
        res += std::to_string(denominateur[i]) + " ";

    return res;
}
