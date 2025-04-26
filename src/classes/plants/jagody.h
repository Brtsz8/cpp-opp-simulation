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
        virtual void kolizja(int from_x, int from_y, Organizm* other) override;
        void wplywNaSile(Organizm* atakujacy) override;
        virtual string nazwa() const override;
};
#endif //JAGODY_H