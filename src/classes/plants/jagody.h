#ifndef JAGODY_H
#define JAGODY_H

#include "../roslina.h"

using namespace std;

class Jagody : public Roslina {
    public:
        Jagody(int pozycja_x, int pozycja_y, Swiat* swiat);
        virtual ~Jagody() override;

        virtual Organizm* dodajPotomka(int x, int y) const override;
        virtual char rysowanie() const override;
};
#endif //JAGODY_H