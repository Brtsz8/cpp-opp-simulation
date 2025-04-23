#include <iostream>
//nie uzywam rand ze wzgledu na thread safety
#include <random>
#include <sstream>
#include "zwierze.h"
#include "swiat.h"

using namespace std;

//zwraca liczbe od 0 do 3 wlacznie, w celu wybrania kierunku ruchu przez organizm
int getRandomDir(){
    //static urzywany zeby nie resetowac tego z kazdym wywolaniem funkcji 
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0,3);
    return dis(gen);
}

//funkcja sprawdza czy nie zwierze nie probuje wyjsc poza plansze
bool isInBounds(WINDOW* win, int y, int x) {
    int h, w;
    getmaxyx(win, h, w);
    return y > 0 && y < h-1 && x > 0 && x < w-1;
}

//konstruktor
Zwierze::Zwierze(int sila, int inicjatywa, int pozycja_x, int pozycja_y, Swiat* swiat)
    :Organizm(sila, inicjatywa, pozycja_x, pozycja_y,swiat) {}

//Destruktor
Zwierze::~Zwierze() {};

pair<int, int> Zwierze::znajdzWolnePoleObok(){
    static const int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    for(auto [dx, dy] : dirs){
        int new_x = getPozycjaX() + dx;
        int new_y = getPozycjaY() + dy;

        //sprawdza czy nowo wybrana pozycja jest wolna i czy nie jest poza granicami swiata
        if( isInBounds(getSwiat()->getWin(), new_x, new_y) && 
            getSwiat()->findOrganismAt(new_x, new_y) == nullptr)
            return {new_x, new_y};
    }

    return {-1,-1}; //brak miejsca -> trzeba sprawdzic to w funckji wywolujacej
}

//akcja ktora zalezy od typu zwierzecia
void Zwierze::akcja(){

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
    
    if (other != nullptr) {
    //std::cerr << "Znaleziono innego organizma na (" << new_x << "," << new_y << "): "
    //          << typeid(*other).name() << "\n";
}

    //jezeli w dany miejsu nie ma zadnego organizmu
    if(other == nullptr)
    {
        setPozycja(new_x,new_y);
        
        ostringstream log;
        log << "Przesuwam na nowa pozycje x:"<<new_x<<", y: "<<new_y;
        getSwiat()->nowyLog(log.str());
    }
    //w przeciwnym razie kolizja
    else{
        ostringstream log;
        log << "Próba ataku!";
        getSwiat()->nowyLog(log.str());
        kolizja(from_x, from_y, other);
    }
}

//opisuje co dzieje sie przy kolizji miedzy dwoma zwierzetami
void Zwierze::kolizja(int fromX, int fromY, Organizm* other){
    if(typeid(*this)==typeid(*other))
    {
        getSwiat()->nowyLog(string("Beda sie klonowac!"));
        
        //zwraca dwa inty reprezentujace wolne pole
        auto [new_x, new_y] = znajdzWolnePoleObok();
        if(new_x == -1 && new_y == -1){
            //[new_x, new_y] == other->znajdzWolnePoleObok();
            //if(new_x == -1 && new_y == -1){
            //    getSwiat()->nowyLog(string("Klonowanie nie powiodlo sie - za malo miejsca"));
            //    return;
            //}else{
            //    Organizm* potomek = this->dodajPotomka(new_x, new_y);
            //    if(potomek == nullptr) {
            //        cerr << "dodajPotomka zwrocilo nullptr!\n";
            //    }
            //    if(potomek) getSwiat()->nowyOrganizm(potomek);
            //}
            getSwiat()->nowyLog(string("Klonowanie nie powiodlo sie - za malo miejsca"));
            return;
        }else{
            Organizm* potomek = this->dodajPotomka(new_x, new_y);
            if(potomek == nullptr) {
                cerr << "dodajPotomka zwrocilo nullptr!\n";
            }
            if(potomek) getSwiat()->nowyOrganizm(potomek);
        }

    }
    /*tu bedzie reszta logiki ataku*/
}