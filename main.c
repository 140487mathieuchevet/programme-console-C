#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>

#define  TX         80
#define  TAILLEBORDX 81
#define  TAILLEBORDY 22
#define  TAILLEBORDY2 21
#define  TAILLEBORDY3 23
#define  TY         20
#define  TP         24
#define  HAUT       72
#define  BAS        80
#define  GAUCHE     75
#define  DROITE     77

void affiche_lettre(int x, int y, int l, int color);
void textcolor(int color);
void gotoxy(int x, int y);


int main()
{
srand(time(NULL));
int snake[300]={0},xx[80],yy[80];
int x=0,y=0,w=0,z=0,clav,i=0,fin=0,dern=0,accel=150,p=0,continu=0;

    do{
        accel=150;
        system("cls");
        dern=0;
        p=0;
        x=rand()%TX;
        y=rand()%TY;
        w=rand()%TX;
        z=rand()%TY;
        for(i=0; i<TAILLEBORDY; i++){
            gotoxy(TAILLEBORDX,i);
            textcolor(12);
            putchar('6');
        }
        for(i=0; i<TAILLEBORDX; i++){
            gotoxy(i,TAILLEBORDY2);
            textcolor(12);
            putchar('6');
        }



        gotoxy(x,y);
        textcolor(10);
        putchar('0');

        fin=0;
        while(!fin){

            if(kbhit()){
                clav=getch();
                if(clav!=224){
                    gotoxy(x,y);
                    textcolor(0);
                    putchar(' ');

                    while(!kbhit() && !fin){
                        Sleep(accel);
                        gotoxy(w,z);
                        textcolor(12);
                        putchar('0');
                        if(x==w && y==z){
                            gotoxy(w,z);
                            textcolor(0);
                            putchar(' ');
                            w=rand()%TX;
                            z=rand()%TY;
                            dern++;
                            p++;
                            gotoxy(0,TP);
                            textcolor(14);
                            printf("points : %d",p);
                            accel-= 2;
                        }

                        switch (clav){

                            case HAUT :y--;break;
                            case DROITE :x++;break;
                            case BAS :y++;break;
                            case GAUCHE :x--;break;
                            default : break;
                        }

                        gotoxy(x,y);
                        textcolor(10);
                        printf("%d",snake[0]);

                        if(x<0 || y<0 || x>TX || y>TY){
                            gotoxy(0,TAILLEBORDY);
                            textcolor(12);
                            printf("vous avez perdu");
                            fin=1;

                        }
                        for(i=1; i<=dern; i++){
                            if(x==xx[i] && y==yy[i]){
                                gotoxy(0,TAILLEBORDY);
                                textcolor(12);
                                printf("vous avez perdu");
                                fin=1;

                            }
                        }
                        affiche_lettre(xx[dern],yy[dern],snake[dern],0);

                        for (i=dern; i>0; i--){
                            xx[i]=xx[i-1];
                            yy[i]=yy[i-1];
                        }

                        xx[0]=x;
                        yy[0]=y;


                        for(i=1; i<=dern; i++){
                            affiche_lettre(xx[i],yy[i],snake[i],12);
                        }
                        affiche_lettre(xx[0],yy[0],snake[0],10);
                    }
                }
            }
        }
        gotoxy(0,TAILLEBORDY3);
        textcolor(10);
        printf("voulez vous rejouer?:(0 = quitter 1 = rejouer)");
        scanf("%d",&continu);
        rewind(stdin);
        while(continu> 1 || continu<0){
            continu=0;
            gotoxy(0,TAILLEBORDY3);
            textcolor(10);
            printf("voulez vous rejouer?:(0 = quitter 1 = rejouer)");
            scanf("%d",&continu);
            rewind(stdin);
        }
    }while(continu == 1);
    return 0;
}

void affiche_lettre(int x, int y, int l, int color)

{
    gotoxy(x,y);
    textcolor(color);
    printf("%d",l);
}

void gotoxy(int x, int y)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(h,c);
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);

}
//
void textcolor(int color)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,color);
}
