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
    FractionRationnelle(const std::vector<float> &numerateur, const std::vector<float> &denominateur);
    FractionRationnelle(float num[], size_t taille_num, float denom[], size_t taille_denom);

    // Méthodes
    float get_numerateur() const;
    float get_denominateur() const;
    void trace_asymptotes() const;
    void trace_courbe() const;
    void changement_homographique() const;

    // Méthodes d'affichage
    std::string to_s() const;

  public:
    Polynome m_numerateur;
    Polynome m_denominateur;
    std::vector<PointMassique> m_points_controle;
};

#endif