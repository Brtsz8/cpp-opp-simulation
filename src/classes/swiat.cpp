#include <iostream>
#include <ncurses.h>
#include <vector>
#include "swiat.h"

using namespace std;

Swiat::Swiat(WINDOW *new_win, WINDOW *new_log_win) : win(new_win), log_window(new_log_win) {}
