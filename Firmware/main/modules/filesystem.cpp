//
// Created by Alexandru Anastasiu on 2/7/23.
//

#include "filesystem.hpp"

inline void trap()
{
    printf("Trap!\n");
    fflush(stdout);
}
#include "driver/gpio.h"

int testFileSystem(int x, char**y)
{
    // TODO: me
    return ESP_OK;
}

int initFileSystem()
{
    // TODO: me
    return ESP_OK;
}
//#include <dirent.h>

int listDir(int x, char**y)
{
    /*DIR* d;
    dirent *dir;
    d = opendir("/storage/");
    if(d)
    {
        while((dir = readdir(d)) != nullptr)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }*/

    return 0;
}

int cat(int x, char**y)
{
    /*char dest[100] = "/storage/";
    strcat(dest, y[1]);
    FILE* file = fopen(dest, "r");
    char c;
    do{
        fscanf(file, "%c", &c);
        printf("%c", c);
    }while(c != EOF);
    return 0;*/
    return 0;
}

int touch(int x, char**y)
{
    /*char dest[100] = "/storage/";
    strcat(dest, y[1]);
    fclose(fopen(dest, "w+"));*/
    return 0;
}
