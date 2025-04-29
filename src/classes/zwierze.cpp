#include <iostream>
//nie uzywam rand ze wzgledu na thread safety
#include <sstream>
#include "zwierze.h"
#include "swiat.h"

using namespace std;

//konstruktor
Zwierze::Zwierze(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat)
    :Organizm(sila, inicjatywa, pozycja_x, pozycja_y,swiat) {}

//Destruktor
Zwierze::~Zwierze() {};

//akcja ktora zalezy od typu zwierzecia
void Zwierze::akcja(){
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
    int move_x[] = {0, 0, -1, 1};
    int move_y[] = {-1, 1, 0, 0};
    
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
        log << "Przesuwam "<<nazwa()<<" na nowa pozycje x:"<<new_x<<", y: "<<new_y;
        getSwiat()->nowyLog(log.str());
    }
    //w przeciwnym razie kolizja
    else{
        kolizja(from_x, from_y, other);
    }
}

//opisuje co dzieje sie przy kolizji miedzy dwoma zwierzetami
void Zwierze::kolizja(int fromX, int fromY, Organizm* other){
    ostringstream log;
    if(typeid(*this)==typeid(*other))
    {   
        //zwraca dwa inty reprezentujace wolne pole
        auto [new_x, new_y] = znajdzWolnePoleObok();
        if(new_x == -1 && new_y == -1){    
                return; //gdy nie ma miejsca na nowy organizm to konczymy kolizje 
        }else{
            Organizm* potomek = this->dodajPotomka(new_x, new_y);
            log<<nazwa()<<" i "<<other->nazwa()<<" beda miec potomka na x:"
            <<new_x<<" y:"<<new_y;
            if(potomek == nullptr) { cout<<"Nie udało sie stworzyc potomka - błąd programu :(";};
            if(potomek) getSwiat()->nowyOrganizm(potomek);
            getSwiat()->nowyLog(log.str());
            return;
        }

    }

    /*sprawdza czy inny organizm odbil atak*/
    if(other->czyOdbilAtak(this)){
        log<<nazwa()<<" nieudany atak na x:"<<getPozycjaX()<<" y:"<<getPozycjaY()<<" -wraca na pole";
        getSwiat()->nowyLog(log.str());
        setPozycja(fromX, fromY);
        return;
    }

    other->wplywNaSile(this); //sprawdza czy inny organizm ma jakis wply na sile
    if(getSila()<0){
        setZyjeFalse();
        log<<nazwa()<<" zatruty przez "<<other->nazwa();
        getSwiat()->nowyLog(log.str());
        log.str("");
        log.clear();
    }
    /*tu bedzie reszta logiki ataku*/
    if(wiekszaSilaOd(other)){
        setPozycja(other->getPozycjaX(), other->getPozycjaY());  //organizm przesuwa sie na pole organizmu ktory pokonal
        other->setZyjeFalse();
        log<<nazwa()<<" zabija "<<other->nazwa()<<" na x:" <<other->getPozycjaX()<<" y:"<<other->getPozycjaY();
        getSwiat()->nowyLog(log.str());
    }else{
        setZyjeFalse();
        log<<other->nazwa()<<" zabija "<<nazwa()<<" na x:" <<getPozycjaX()<<" y:"<<getPozycjaY();
        getSwiat()->nowyLog(log.str());
    }
}