#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <random>
#include "antylopa.h"
#include "../swiat.h"
using namespace std;

Antylopa::Antylopa(int pozycja_x, int pozycja_y, Swiat* swiat) 
    : Zwierze(4, 4, pozycja_x, pozycja_y, swiat) {};

Antylopa::~Antylopa() {};

char Antylopa::rysowanie() const {
    return 'A';
}

Organizm* Antylopa::dodajPotomka(int x, int y) const {
    Organizm* mlodaAntylopa = new Antylopa(x,y,getSwiat());
    return mlodaAntylopa;
}
//zwraca liczbe od 0 do 11 wlacznie, w celu wybrania kierunku ruchu przez organizm
int Antylopa::getRandomDir(){
    //static urzywany zeby nie resetowac tego z kazdym wywolaniem funkcji 
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0,11);
    return dis(gen);
}

bool Antylopa::czyUcieka(){
    if(getRandomDir()%2 == 0 ) return true;
    return false;
}

//akcja ktora zalezy od typu zwierzecia
void Antylopa::akcja(){
    ostringstream log; //do wpisywania logow
    
    if (getSwiat() == nullptr) {
        std::cerr << "Błąd: getSwiat() == nullptr\n";
        abort();
    }

    WINDOW* win = getSwiat()->getWin();
    if (win == nullptr) {
        std::cerr << "Błąd: getWin() == nullptr\n";
        abort();
    }

    int dir = getRandomDir();
    int move_x[] = {0, 0, -1, 1,-2,2,0,0,1,1,-1,-1};
    int move_y[] = {-1, 1, 0, 0,0,0,-2,2,1,-1,1,-1};
    
    int from_x = getPozycjaX();
    int from_y = getPozycjaY();

    int new_x = from_x + move_x[dir];
    int new_y = from_y + move_y[dir];

    
    if(!isInBounds(win, new_y, new_x )) return;
    //znajduje organizm na miejsu do ktorego chce sie ruszyc
    Organizm* other = getSwiat()->findOrganismAt(new_x,new_y);
    
    //jezeli w dany miejsu nie ma zadnego organizmu
    if(other == nullptr)
    {
        setPozycja(new_x,new_y);        
        log << "Przesuwam na nowa pozycje x:"<<new_x<<", y: "<<new_y;
    }
    //w przeciwnym razie kolizja
    else{
        kolizja(from_x, from_y, other);
    }
    getSwiat()->nowyLog(log.str());
}

//opisuje co dzieje sie przy kolizji miedzy dwoma zwierzetami
void Antylopa::kolizja(int fromX, int fromY, Organizm* other){
    ostringstream log;
    if(typeid(*this)==typeid(*other)){
        Zwierze::kolizja(fromX,fromY,other);
    }
    if(!czyUcieka()){
        log<<"Antylopa na x:"<<getPozycjaX()<<" y:"<<getPozycjaY()<<" nie ucieka";
        getSwiat()->nowyLog(log.str());
        Zwierze::kolizja(fromX,fromY,other);
    }else{
        //ucieczka antylopy nie działa tak samo jak jej ruch 
        //- przesuwa sie tylko na sasiednie pola
        int move_x[] = {0 , 0,-1, 1};
        int move_y[] = {-1, 1, 0, 0};
        int kierunki = 4;
        while(kierunki){
            int new_x = getPozycjaX() + move_x[kierunki-1];
            int new_y = getPozycjaY() + move_y[kierunki-1];
            if( isInBounds(getSwiat()->getWin(), new_y, new_x) &&
                getSwiat()->findOrganismAt(new_x, new_y) == nullptr)
            {
                log<<"Antylopa ucieka na pole x:"<<new_x<<" y:"<<new_y;
                setPozycja(new_x,new_y);
                getSwiat()->nowyLog(log.str());
                return;
            }
            kierunki--;
        }
        getSwiat()->nowyLog(log.str());
    }
    return;
}

bool Antylopa::czyOdbilAtak(Organizm* atakujacy){
    ostringstream log;
    if(!czyUcieka()){
        log<<"Antylopa na x:"<<getPozycjaX()<<" y:"<<getPozycjaY()<<" nie ucieka";
        getSwiat()->nowyLog(log.str());
        return false;
    }
    //ucieczka antylopy nie działa tak samo jak jej ruch 
    //- przesuwa sie tylko na sasiednie pola
    int move_x[] = {0 , 0,-1, 1};
    int move_y[] = {-1, 1, 0, 0};
    int kierunki = 4;
    while(kierunki){
        int new_x = getPozycjaX() + move_x[kierunki-1];
        int new_y = getPozycjaY() + move_y[kierunki-1];
        if( isInBounds(getSwiat()->getWin(), new_y, new_x) &&
            getSwiat()->findOrganismAt(new_x, new_y) == nullptr)
        {
            log<<"Antylopa ucieka na pole x:"<<new_x<<" y:"<<new_y;
            setPozycja(new_x,new_y);
            getSwiat()->nowyLog(log.str());
            return true;
        }
        kierunki--;
    }
    return false;   //jesli nie ma gdzie uciec to nie odbija ataku
}