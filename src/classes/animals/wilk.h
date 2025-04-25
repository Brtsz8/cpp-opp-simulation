#ifndef WILK_H
#define WILK_H

#include "../zwierze.h"

class Wilk : public Zwierze {
    public:
        Wilk(int pozycja_x, int pozycja_y, Swiat* swiat);

        ~Wilk() override;

        virtual char rysowanie()const override;
        virtual Organizm* dodajPotomka(int x, int y) const override;
};
#endif //WILK_H