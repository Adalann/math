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
    std::string to_s();

    private:
    
    double numerateur[4];
    double denominateur[4];
};

#endif