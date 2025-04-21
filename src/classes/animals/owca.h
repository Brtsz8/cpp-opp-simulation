#ifndef OWCA_H
#define OWCA_H

#include "../zwierze.h"

class Owca : public Zwierze {
    public:
        Owca(int pozycja_x, int pozycja_y, Swiat* swiat);

        ~Owca() override;

        char rysowanie() override;
};
#endif //OWCA_H