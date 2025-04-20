#include <iostream>
#include <stdio.h>
#include <fstream>
#include "config.h"

void load_config(const std::string& filename, WinConfig *config){
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open " << filename << ", using default values.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("height=") == 0) {
            config->height = std::stoi(line.substr(7));
        } else if (line.find("width=") == 0) {
            config->width = std::stoi(line.substr(6));
        } else if (line.find("start_y=") == 0) {
            config->start_y = std::stoi(line.substr(8));
        } else if (line.find("start_x=") == 0) {
            config->start_x = std::stoi(line.substr(8));
        }
    }      
}
