#ifndef ZOLW_H
#define ZOLW_H

#include "../zwierze.h"

class Zolw : public Zwierze {
    public:
        Zolw(int pozycja_x, int pozycja_y, Swiat* swiat);

        ~Zolw() override;

        char rysowanie() override;
        Organizm* dodajPotomka(int x, int y) override;
};
#endif //ZOLW_H