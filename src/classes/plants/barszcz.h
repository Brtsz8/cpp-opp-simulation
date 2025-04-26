#ifndef BARSZCZ_H
#define BARSZCZ_H

#include "../roslina.h"

using namespace std;

class Barszcz : public Roslina {
    public:
        Barszcz(int pozycja_x, int pozycja_y, Swiat* swiat);
        virtual ~Barszcz() override;

        virtual Organizm* dodajPotomka(int x, int y) const override;
        virtual char rysowanie() const override;
        virtual string nazwa() const override;
        virtual void akcja() override;
        virtual void kolizja(int from_x, int from_y, Organizm* other) override;
        void wplywNaSile(Organizm* atakujacy) override;
};
#endif //BARSZCZ_H