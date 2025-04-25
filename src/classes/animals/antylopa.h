#ifndef ANTYLOPA_H
#define ANTYLOPA_H

#include "../zwierze.h"

class Antylopa : public Zwierze {
    public:
        Antylopa(int pozycja_x, int pozycja_y, Swiat* swiat);

        virtual ~Antylopa() override;

        char rysowanie() const override;
        Organizm* dodajPotomka(int x, int y) const override;
        virtual void akcja() override;
        virtual void kolizja(int fromX, int fromY, Organizm* other) override;
        virtual bool czyOdbilAtak(Organizm* atakujacy) override;
        virtual int getRandomDir() override;
    protected:
        bool czyUcieka();
};
#endif //ANTYLOPA_H