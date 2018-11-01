#ifndef DEF_POLYNOME
#define DEF_POLYNOME

#include <string>

class Polynome
{
    public:

    Polynome();
    Polynome(double num[], double denom[]);
    double getNumerateur() const;
    double getDenominateur() const;
    int solve_denom(double &x1, double &x2);

    std::string to_s();

    private:
    
    int get_degre(bool select);

    double numerateur[4];
    double denominateur[4];
};

#endif