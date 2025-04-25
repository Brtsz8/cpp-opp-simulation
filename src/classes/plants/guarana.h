#ifndef GUARANA_H
#define GUARANA_H

#include "../roslina.h"

using namespace std;

class Guarana : public Roslina {
    public:
        Guarana(int pozycja_x, int pozycja_y, Swiat* swiat);
        virtual ~Guarana() override;

        virtual Organizm* dodajPotomka(int x, int y) const override;
        virtual char rysowanie() const override;
};
#endif //GUARANA_H