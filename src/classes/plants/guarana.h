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
        virtual string nazwa() const override;
        virtual void kolizja(int from_x, int from_y, Organizm* other) override;
        void wplywNaSile(Organizm* atakowany) override;
        
};
#endif //GUARANA_H