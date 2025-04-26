#ifndef ZOLW_H
#define ZOLW_H

#include "../zwierze.h"

class Zolw : public Zwierze {
    public:
        Zolw(int pozycja_x, int pozycja_y, Swiat* swiat);

        ~Zolw() override;

        virtual void akcja() override;
        char rysowanie() const override;
        virtual string nazwa() const override;
        Organizm* dodajPotomka(int x, int y) const override;
        bool czyOdbilAtak(Organizm* atakujacy) override;
};
#endif //ZOLW_H