#ifndef DEF_POLYNOME
#define DEF_POLYNOME

#include <string>
#include <vector>


class Polynome
{
  public:
    // Constructeurs
    Polynome();
    Polynome(int degre);
    Polynome(const Polynome &original);
    Polynome(const Polynome &original, int degre_limite);
    Polynome(std::vector<float> coefficients);
    Polynome(float coefficients[], size_t taille);

    // Méthodes
    void normalize();
    int get_degre() const;
    int solve(float &x1, float &x2) const;
    float get_last_coef() const;
    float get_coef_puissance(int d) const;
    void add_coef(float c);
    float value_for(float x) const;
    std::vector<float> get_coefs() const;
    static Polynome div_euclide(Polynome const &p1, Polynome const &p2);
    std::vector<float> passage_base_bernstein(int degre) const;

    //Surchage d'opérateur
    Polynome &operator+=(const Polynome &p);
    Polynome &operator-=(const Polynome &p);
    // Polynome &operator*=(const Polynome &p);

    // Méthodes d'affichage
    std::string to_s();
    void affiche_polynome();
    void affiche_polynome(std::string message);

    void decalage(int puissance, float coefficient);
  private:

    std::vector<float> m_coefficients;

};

Polynome operator+(Polynome const &p1, Polynome const &p2);
Polynome operator-(Polynome const &p1, Polynome const &p2);
Polynome operator*(Polynome const &p1, Polynome const &p2);

#endif