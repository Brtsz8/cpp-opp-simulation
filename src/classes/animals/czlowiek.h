#ifndef CZLOWIEK_H
#define CZLOWIEK_H

#include "../zwierze.h"

class Czlowiek : public Zwierze {
    private:
        bool umiejetnoscAktywna = false;
        int dlugoscUmiejetnosci = 5;
        int dlugoscRegeneracji = 0;
    public:
        Czlowiek(int pozycja_x, int pozycja_y, Swiat* swiat);

        virtual ~Czlowiek() override;
        virtual void akcja() override;
        virtual void kolizja(int from_x, int from_y, Organizm* other);  
        bool czyOdbilAtak(Organizm* atakujacy) override;
        
        //gettery
        bool getUmiejetnoscAktywna() const;
        int getDlugoscUmiejetnosci() const;
        int getDlugoscRegeneracji() const;

        //settery
        void setUmiejetnoscAktywna(bool zmianaStanu) const;
        void setDlugoscUmiejetnosci(int dlugoscUmiejetnosci);
        void setDlugoscRegeneracji(int dlugoscRegeneracji);

        //Organizm* dodajPotomka(int x, int y) const override;
        char rysowanie() const override;
        virtual string nazwa() const override;
};
#endif //CZLOWIEK_H