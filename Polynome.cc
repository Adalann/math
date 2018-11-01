#include "Polynome.h"

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
