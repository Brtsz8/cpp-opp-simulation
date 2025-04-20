#include <iostream>
#include <stdio.h>
#include "config.h"

void load_config(char *filename, WinConfig *config){
    FILE *file = fopen(filename, "r");
    if(!file){
        std::cout<<"ERROR: nie można otworzyc pliku ("<<filename<<") - urzywane sa podstawowe wartosci!";
        return;
    }

    char line[101];
    while(fgets(line, sizeof(line), file)){
        sscanf(line, "height=%d",   &config->height);
        sscanf(line, "width=%d",    &config->width);
        sscanf(line, "start_y=%d",  &config->start_y);
        sscanf(line, "start_x=%d",  &config->start_x);
    }
    fclose(file);
}

