#include "drawui.h"

void DrawWeather(WINDOW *weatherWindow,int weatherflag,const char *title)
{
    mvwprintw(weatherWindow,0,7,title);
    for(int i=0;i<5;i++){
        mvwprintw(weatherWindow,i+1,1,weather[weatherflag][i]);
    }
}

void DrawWeatherType(WINDOW *weathertype, const char *Data[])
{
    mvwprintw(weathertype,0,3,"天气");
    mvwprintw(weathertype,1,1,"温差:%s",Data[0]);
    mvwprintw(weathertype,2,1,"湿度:%s",Data[1]);
    mvwprintw(weathertype,3,1,"天气:%s",Data[2]);
    mvwprintw(weathertype,4,1,"风向:%s",Data[3]);
    mvwprintw(weathertype,5,1,"风力:%s",Data[4]);
}



WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0); /* 0, 0 是字符默认的行列起始位置 */
    //wrefresh(local_win); /*刷新窗口缓冲，显示 box */
    return local_win;
}

WINDOW *create_childwin(WINDOW* parent,int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = subwin(parent,height, width, starty, startx);
    box(local_win, 0 , 0); /* 0, 0 是字符默认的行列起始位置 */
    //wrefresh(local_win); /*刷新窗口缓冲，显示 box */
    return local_win;
}

//求二维字符串数组最大字符串长度
int getStrLen(const char *str[4])
{
    int len;
    for(int i=0;i<5;i++){
        int length = strlen(str[i]);
        if(length>=len)
            len = length;
    }
    return len;
}

void DrawWeathIndex(WINDOW *index, const char *data[5])
{
    mvwprintw(index,0,3,"指数");
    mvwprintw(index,1,1,"紫外线:%s",data[0]);
    mvwprintw(index,2,1,"感冒:%s",data[1]);
    mvwprintw(index,3,1,"穿衣:%s",data[2]);
    mvwprintw(index,4,1,"运动:%s",data[3]);
    mvwprintw(index,5,1,"空气污染:%s",data[4]);
}

void DayWeather(WINDOW *window[3],
                const int weathertype,
                const char *weatherdata[],
                const char *indexdata[],
                const int startY,
                const char *title)
{
    //int weathertypeLength = getStrLen(weatherdata);
    //int indexdataLenth = getStrLen(indexdata);
    window[0] = create_newwin(7,18,startY,1);
    window[1] = create_newwin(7,18,startY,19);
    window[2] = create_newwin(7,60,startY,37);

    DrawWeather(window[0],weathertype,title);
    DrawWeatherType(window[1],weatherdata);
    DrawWeathIndex(window[2],indexdata);
}

void DrawingUI(const char *type[],
                const char *index[],
                const int wearid,
               const char *time,
               const int Y)
{
    WINDOW *W[3];
    DayWeather(W,wearid,type,index, Y,time);
    for(int i=0;i<3;i++){
        wrefresh(W[i]);
    }
}
