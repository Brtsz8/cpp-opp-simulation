#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int height;
    int width;
    int start_y;
    int start_x;
} WinConfig;

//from config.cpp - reads config file and returns config struct
void load_config(const std::string& filename, WinConfig *config);

#endif