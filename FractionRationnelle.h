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
    FractionRationnelle(Polynome numerateur, Polynome denominateur);
    FractionRationnelle(const std::vector<double> &numerateur, const std::vector<double> &denominateur);
    FractionRationnelle(double num[], size_t taille_num, double denom[], size_t taille_denom);

    // Méthodes
    double get_numerateur() const;
    double get_denominateur() const;
    void assymptote_h();
    void trace_assymptotes();

    // Méthodes d'affichage
    std::string to_s();

  private:
    Polynome m_numerateur;
    Polynome m_denominateur;
    PointMassique m_p0;
    PointMassique m_p1;
    PointMassique m_p2;
    PointMassique m_p3;
};

#endif