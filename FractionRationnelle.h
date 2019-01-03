#ifndef DEF_FRACTION_RATIONNELLE
#define DEF_FRACTION_RATIONNELLE

#include <string>
#include <vector>

class FractionRationnelle
{
    public:
        FractionRationnelle();
        FractionRationnelle(double num[], size_t taille_num, double denom[], size_t taille_denom);
        double getNumerateur() const;
        double getDenominateur() const;
        int solve_denom(double &x1, double &x2);
        double assymptote_h();
        void divisionEuclidienne(double &m, double &p);

        std::string to_s();

    private:
    
        int get_degre(bool select = false);

        std::vector<double> numerateur;
        std::vector<double> denominateur;
};

#endif