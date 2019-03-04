#ifndef DRAWUI_H
#define DRAWUI_H
#include <stdio.h>
#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "asciiarttable.h"


typedef struct weatherdata{
    char *type[64];
    char *index[64];
}WeatherData;


WINDOW *create_newwin(int height, int width, int starty, int startx);
WINDOW *create_childwin(WINDOW* parent,int height, int width, int starty, int startx);

void DrawWeather(WINDOW *weatherWindow,int weatherflag,const char *title);
void DrawWeatherType(WINDOW *weathertype, const char *Data[]);
void DrawWeathIndex(WINDOW *index,const char *data[]);

void DayWeather(WINDOW *window[],
                const int weathertype,
                const char *weatherdata[],
                const char *indexdata[],
                const int startY,
                const char *title);

void DrawingUI(const char *type[], const char *index[], const int wearid, const char *time, const int Y);




int getStrLen(const char *str[4]);


#endif // DRAWUI_H
