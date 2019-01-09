#ifndef DEF_FRACTION_RATIONNELLE
#define DEF_FRACTION_RATIONNELLE

#include <string>
#include <vector>
#include "Polynome.h"
#include "PointMassique.h"

class FractionRationnelle
{
  public:
    // Constructeurs
    FractionRationnelle();
    FractionRationnelle(PointMassique p1, PointMassique p2, PointMassique p3, PointMassique p4);
    FractionRationnelle(Polynome numerateur, Polynome denominateur);
    FractionRationnelle(const std::vector<double> &numerateur, const std::vector<double> &denominateur);
    FractionRationnelle(double num[], size_t taille_num, double denom[], size_t taille_denom);

    // Méthodes
    double get_numerateur() const;
    double get_denominateur() const;
    void assymptote_h() const;
    void trace_assymptotes() const;
    void trace_courbe() const;
    void affiche_points_controles() const;

    // Méthodes d'affichage
    std::string to_s() const;

  public:
    Polynome m_numerateur;
    Polynome m_denominateur;
    std::vector<PointMassique> m_points_controle;
};

#endif