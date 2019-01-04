#ifndef DEF_POLYNOME
#define DEF_POLYNOME

#include <vector>
#include <string>

class Polynome
{
  public:
    // Constructeurs
    Polynome();
    Polynome(int degre);
    Polynome(const Polynome &original);
    Polynome(const Polynome &original, int degre_limite);
    Polynome(std::vector<double> coefficients);
    Polynome(double coefficients[], size_t taille);

    // Méthodes
    int get_degre() const;
    int solve(double &x1, double &x2) const;
    double get_last_coef() const;
    void add_coef(double c);
    double value_for(double x) const;
    std::vector<double> get_coefs() const;
    static Polynome div_euclide(Polynome const &p1, Polynome const &p2);

    //Surchage d'opérateur
    Polynome &operator+=(const Polynome &p);
    Polynome &operator-=(const Polynome &p);
    // Polynome &operator*=(const Polynome &p);

    // Méthodes d'affichage
    std::string to_s();
    void affiche_polynome();
    void affiche_polynome(std::string message);

    void decalage(int puissance, double coefficient);
  private:

    std::vector<double> m_coefficients;

};

Polynome operator+(Polynome const &p1, Polynome const &p2);
Polynome operator-(Polynome const &p1, Polynome const &p2);
Polynome operator*(Polynome const &p1, Polynome const &p2);

#endif