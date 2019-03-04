
#include "drawui.h"
#include "curlapi.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>



#define WIDTH 15
#define HEIGHT 9

int startx = 0;
int starty = 85;


void iniwindow(){
    setlocale(LC_ALL,"");

    initscr();
    raw();
    //noecho();
    curs_set(0);
}


void MainUI(const char *weatid,const char *wear[20],const char *index[20],const char *city){
    iniwindow();


    //char time[]={"123",};

    WINDOW *W;
    W = create_newwin(7,17,2,1);
    DrawWeather(W,1,city);

    refresh();

    char *wearA[6];
    char *wearB[6];
    char *wearC[6];

    char *indexA[6];
    char *indexB[6];
    char *indexC[6];

    char *Time[3];
    Time[0] = index[0];
    Time[1] = index[6];
    Time[2] = index[12];



        wearA[0] = wear[1];
        wearA[1] = wear[2];
        wearA[2] = wear[3];
        wearA[3] = wear[4];
        wearA[4] = wear[5];

        wearB[0] = wear[7];
        wearB[1] = wear[8];
        wearB[2] = wear[9];
        wearB[3] = wear[10];
        wearB[4] = wear[11];

        wearC[0] = wear[13];
        wearC[1] = wear[14];
        wearC[2] = wear[15];
        wearC[3] = wear[16];
        wearC[4] = wear[17];





        indexA[0] = index[1];
        indexA[1] = index[2];
        indexA[2] = index[3];
        indexA[3] = index[4];
        indexA[4] = index[5];

        indexB[0] = index[7];
        indexB[1] = index[8];
        indexB[2] = index[9];
        indexB[3] = index[10];
        indexB[4] = index[11];

        indexC[0] = index[13];
        indexC[1] = index[14];
        indexC[2] = index[15];
        indexC[3] = index[16];
        indexC[4] = index[17];


    int id = getWeatid(weatid);
    DrawingUI(wearA,indexA,id,Time[0],9);
    DrawingUI(wearB,indexB,id,Time[1],16);
    DrawingUI(wearC,indexB,id,Time[2],23);
    wrefresh(W);

    //endwin();
    //getch();
}



void print_menu(WINDOW *menu_win, int highlight, const char choices[6][64], int length);
void print_input(WINDOW *input);
void inputchar(WINDOW *input);
void print_input(WINDOW *input){
    //box(input, 2, 0);
    wprintw(input," 输入城市\n|");
    wrefresh(input);
}


void menu(){

   iniwindow();
   char choices[6][64] ={
       "beijing",
       "....",
       "....",
       "....",
       "....",
       "...."
   };
   int menuIndex[6]= {0,1,2,3,4,5,6};

   char *weardata[18];
   char *index[18];

   char a[32];
    int b = getcityid(choices[0]);
    sprintf(a,"%d",b);
    getForcast(a,weardata);
    getLifeIndex(a,index);
    MainUI(a,weardata,index,choices[0]);


   int n_choices = sizeof(choices) / sizeof(char[64]);

   WINDOW *menu_win,*input_win;
   int highlight = 1;
   int choice = 0;
   int c;


   menu_win = newwin(HEIGHT, WIDTH, startx, starty);

   keypad(menu_win, TRUE);
   print_menu(menu_win, highlight,choices,n_choices);

   for(;;)
   {
       c = wgetch(menu_win);
       switch(c)
       {

       case KEY_UP:
           if(highlight == 1)
               highlight = n_choices;
           else
               --highlight;
               break;
       case KEY_DOWN:
           if(highlight == n_choices)
               highlight = 1;
           else
           ++highlight;
           break;
       case KEY_LEFT:

               choice = highlight;
               memcpy(choices[menuIndex[choice-1]],"....",4);
               print_menu(menu_win, highlight,choices,n_choices);
               refresh();
               break;
       case KEY_RIGHT:
               choice = highlight;
               input_win = create_newwin(3,10,2,87);
               touchwin(input_win);
               print_input(input_win);
               char s[32]={0,};
               wscanw(input_win,"%s",s);
               memset(choices[choice-1],0,64);
               memcpy(choices[choice-1],s,strlen(s));
               werase(input_win);
               delwin(input_win);
               refresh();
           break;
       case 10:
               choice = highlight;
               if(!strcmp(choices[choice-1],"...."))
                   break;
               int id = getcityid(choices[choice-1]);
               if(id==-1){
                   break;
               }
               char sid[32];
//               mvprintw(24, 0, "                    ");
//               mvprintw(24, 0, "%s",choices[choice-1]);
//               mvprintw(28, 0, "                    ");
//               mvprintw(28, 0, "%d",id);
               sprintf(sid,"%d",id);
               getForcast(sid,weardata);
               getLifeIndex(sid,index);
               MainUI(sid,weardata,index,choices[choice-1]);
               print_menu(menu_win, highlight,choices,n_choices);
               refresh();
               break;
        default:
           refresh();
           break;
       }

       print_menu(menu_win, highlight,choices,n_choices);
   }
   clrtoeol();

   endwin();
}



int main()
{

   menu();
    //setlocale(LC_ALL,"");
    //int a= getcityid("huairou");
    //printf("%d",a);
}
void print_menu(WINDOW *menu_win, int highlight,const char choices[6][64],int length)
{
    int x, y, i;

    x = 2;
    y = 2;
    //int n_choices = sizeof(choices) / sizeof(char *);
    box(menu_win, 0, 0);
    for(i = 0; i < length; ++i)
    {	if(highlight == i + 1) /* High light the present choice */
        {	wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}
