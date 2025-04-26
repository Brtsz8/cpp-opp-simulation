#ifndef LIS_H
#define LIS_H

#include "../zwierze.h"

class Lis : public Zwierze {
    public:
        Lis(int pozycja_x, int pozycja_y, Swiat* swiat);

        ~Lis() override;
        void akcja() override;

        Organizm* dodajPotomka(int x, int y) const override;
        char rysowanie() const override;
        virtual string nazwa() const override;
};
#endif //LIS_H