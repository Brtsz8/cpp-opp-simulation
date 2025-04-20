#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int height;
    int width;
    int start_y;
    int start_x;
} WinConfig;

void load_config(char *filename, WinConfig *config);

#endif