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
        log << "Przesuwam na nowa pozycje x:"<<new_x<<", y: "<<new_y;
    }
    //w przeciwnym razie kolizja
    else{
        kolizja(from_x, from_y, other);
    }
    getSwiat()->nowyLog(log.str());
}

//opisuje co dzieje sie przy kolizji miedzy dwoma zwierzetami
void Zwierze::kolizja(int fromX, int fromY, Organizm* other){
    ostringstream log;
    if(typeid(*this)==typeid(*other))
    {
        getSwiat()->nowyLog(string("Beda sie klonowac!"));
        
        //zwraca dwa inty reprezentujace wolne pole
        auto [new_x, new_y] = znajdzWolnePoleObok();
        if(new_x == -1 && new_y == -1){
            return; //gdy nie ma miejsca na nowy organizm to konczymy kolizje 
        }else{
            Organizm* potomek = this->dodajPotomka(new_x, new_y);
            if(potomek == nullptr) { cout<<"Nie udało sie stworzyc potomka - błąd programu :(";};
            if(potomek) getSwiat()->nowyOrganizm(potomek);
            return;
        }

    }

    /*sprawdza czy inny organizm odbil atak*/
    if(other->czyOdbilAtak(this)){
        log<<"Nieudany atak na x:"<<getPozycjaX()<<" y:"<<getPozycjaY()<<" -powrot na stare wspolrzedne";
        getSwiat()->nowyLog(log.str());
        setPozycja(fromX, fromY);
        return;
    }

    other->wplywNaSile(this); //sprawdza czy inny organizm ma jakis wply na sile
    /*tu bedzie reszta logiki ataku*/
    log << "Próba ataku!";

    if(wiekszaSilaOd(other)){
        setPozycja(other->getPozycjaX(), other->getPozycjaY());  //organizm przesuwa sie na pole organizmu ktory pokonal
        other->setZyjeFalse();
        log<<"Organizm zabija inny organizm na x:" <<other->getPozycjaX()<<" y:"<<other->getPozycjaY();
    }else{
        setZyjeFalse();
        log<<"Organizm zabija inny organizm na x:" <<getPozycjaX()<<" y:"<<getPozycjaY();
    }
    getSwiat()->nowyLog(log.str());
}