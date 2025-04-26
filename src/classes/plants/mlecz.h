#ifndef MLECZ_H
#define MLECZ_H

#include "../roslina.h"

using namespace std;

class Mlecz : public Roslina {
    public:
        Mlecz(int pozycja_x, int pozycja_y, Swiat* swiat);
        virtual ~Mlecz() override;

        virtual void akcja() override;
        virtual Organizm* dodajPotomka(int x, int y) const override;
        virtual char rysowanie() const override;
        virtual string nazwa() const override;
};
#endif //MLECZ_H