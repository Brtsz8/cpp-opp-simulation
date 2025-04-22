#ifndef LIS_H
#define LIS_H

#include "../zwierze.h"

class Lis : public Zwierze {
    public:
        Lis(int pozycja_x, int pozycja_y, Swiat* swiat);

        ~Lis() override;

        char rysowanie() override;
};
#endif //LIS_H