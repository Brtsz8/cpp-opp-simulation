#ifndef ANTYLOPA_H
#define ANTYLOPA_H

#include "../zwierze.h"

class Antylopa : public Zwierze {
    public:
        Antylopa(int pozycja_x, int pozycja_y, Swiat* swiat);

        ~Antylopa() override;

        char rysowanie() override;
};
#endif //ANTYLOPA_H