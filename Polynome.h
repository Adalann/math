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
    Polynome(std::vector<double> coeficients);
    Polynome(double coeficients[], size_t taille);

    // Méthodes
    int get_degre();
    int solve(double &x1, double &x2);
    double get_last_coef();
    std::vector<double> get_coefs() const;
    friend Polynome div_euclide(Polynome const &p1, Polynome const &p2);

    //Surchage d'opérateur
    Polynome &operator-=(const Polynome &p);
    Polynome &operator*=(const Polynome &p);

    // Méthodes d'affichage
    std::string to_s();
    void affiche_polynome();

  private:
    void decalage(int puissance, double coeficient);

    std::vector<double> m_coeficients;

};

Polynome operator-(Polynome const &p1, Polynome const &p2);
Polynome operator*(Polynome const &p1, Polynome const &p2);

#endif