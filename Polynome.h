#ifndef DEF_POLYNOME
#define DEF_POLYNOME

class Polynome
{
    public:

    Polynome();

    double getNumerateur() const;
    double getDenominateur() const;

    private:
    
    double numerateur[4];
    double denominateur[4];
};

#endif