#ifndef TRAWA_H
#define TRAWA_H

#include "../roslina.h"

using namespace std;

class Trawa : public Roslina {
    public:
        Trawa(int pozycja_x, int pozycja_y, Swiat* swiat);
        virtual ~Trawa() override;

        virtual Organizm* dodajPotomka(int x, int y) const override;
        virtual char rysowanie() const override;
        virtual string nazwa() const override;
};
#endif //TRAWA_H