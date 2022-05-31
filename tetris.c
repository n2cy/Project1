#include <stdio.h>                                                                                 
#include <stdlib.h>                                                                                                                                                            
#include <ncurses.h>                                                                                
#include <sys/time.h>                                                                             
#include <time.h>

#include "colors.h"
#include "other.h"
#include "snake.h" // --> maths() 


#define TRUE 1                                                                                      
#define FALSE 0                                                                                    
#define ROW 15                                                                                     
#define COL 11   

//*-*-*-*-*-*-*-*-*-*-*-*-*//
// constant variables      //
//*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
char Tab[ROW][COL] = {0};                                                                           //
int score = 0;                                                                                      //
char activePlay = TRUE;                                                                             //
suseconds_t timer = 500000; //half second                                                           //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//


//*-*-*-*-*-*-*-*-*-*-*-*-*//
// Structure of the table  //
//*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
typedef struct {                                                                                    //
    char **tab;                                                                                     //
    int width, row, col;                                                                            //
} Shape;                                                                                            //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//
// Design of the seven shapes  //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
Shape current;                                                                                                                  //
                                                                                                                                //
const Shape Shapestab[7]= {                                                                                                     //
                                                                                                                                //
    {(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4},                            //
    {(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},                                                       //
    {(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},                                                       //
    {(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},                                                       //
    {(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},                                                       //
    {(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},                                                       //
    {(char *[]){(char []){1,1},(char []){1,1}}, 2}                                                                              //
                                                                                                                                //
};                                                                                                                              //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//



//*-*-*-*-*-*-*-*//
// copies shape  //
//*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
Shape trio_COPY(Shape shape){                                                                       //
    Shape tetris_new_dom = shape;                                                                   //
    char **copy_trio = shape.tab;                                                                   //
    tetris_new_dom.tab = (char**)malloc(tetris_new_dom.width*sizeof(char*));                        //
    int i, j;                                                                                       //
    for(i = 0; i < tetris_new_dom.width; i++){                                                      //
        tetris_new_dom.tab[i] = (char*)malloc(tetris_new_dom.width*sizeof(char));                   //
        for(j=0; j < tetris_new_dom.width; j++) {                                                   //
            tetris_new_dom.tab[i][j] = copy_trio[i][j];                                             //
        }                                                                                           //
    }                                                                                               //
    return tetris_new_dom;                                                                          //
}                                                                                                   //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//


//*-*-*-*-*-*-*-*//
// deletes shape //
//*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
void supprShape(Shape shape){                                                                       //
    int i;                                                                                          //
    for(i = 0; i < shape.width; i++){                                                               //
        free(shape.tab[i]);                                                                         //
    }                                                                                               //
    free(shape.tab);                                                                                //
}                                                                                                   //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//



//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//
// checks the position of the copied shape //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
int Position(Shape shape){                                                                          //
    char **tab = shape.tab;                                                                         //
    int i, j;                                                                                       //
    for(i = 0; i < shape.width;i++) {                                                               //
        for(j = 0; j < shape.width ;j++){                                                           //
            if((shape.col+j < 0 || shape.col+j >= COL || shape.row+i >= ROW)){ //Beware of borders  //
                if(tab[i][j])                                                                       //
                    return FALSE;                                                                   //
            }                                                                                       //
            else if(Tab[shape.row+i][shape.col+j] && tab[i][j])                                     //
                return FALSE;                                                                       //
        }                                                                                           //
    }                                                                                               //
    return TRUE;                                                                                    //
}                                                                                                   //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//



//*-*-*-*-*-*-*-*-*-*-*-*//
// returns random shape  //
//*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
void rdm_shape(){                                                                                                               //
    Shape tetris_new_dom = trio_COPY(Shapestab[rand()%7]); //Select a shape at random from the seven available                  //
                                                                                                                                //
    tetris_new_dom.col = rand()%(COL-tetris_new_dom.width+1);                                                                   //
    tetris_new_dom.row = 0;                                                                                                     //
    supprShape(current);                                                                                                        //
    current = tetris_new_dom;                                                                                                   //
    if(!Position(current)){                                                                                                     //
        activePlay = FALSE;                                                                                                     //
    }                                                                                                                           //
}                                                                                                                               //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//



//*-*-*-*-*-*-*-*-*-*-*-*-*//
// rotates shapes clockwise//
//*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
void TurnShape_postion(Shape shape){                                                                                            //
    Shape temp = trio_COPY(shape);                                                                                              //
    int i, j, k, width;                                                                                                         //
    width = shape.width;                                                                                                        //
    for(i = 0; i < width ; i++){                                                                                                //
        for(j = 0, k = width-1; j < width ; j++, k--){                                                                          //
                shape.tab[i][j] = temp.tab[k][i];                                                                               //
        }                                                                                                                       //
    }                                                                                                                           //
    supprShape(temp);                                                                                                           //
}                                                                                                                               //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//


//*-*-*-*-*-*-*-*-*//
// writes to table //
//*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//
void WriteToTab(){                                                                       //
    int i, j;                                                                            //
    for(i = 0; i < current.width ;i++){                                                  //
        for(j = 0; j < current.width ; j++){                                             //
            if(current.tab[i][j])                                                        //
                Tab[current.row+i][current.col+j] = current.tab[i][j];                   //
        }                                                                                //
    }                                                                                    //
}                                                                                        //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//



//*-*-*-*-*-*-*-*-*-*-*-*-*//
//  adds points to player  //
//*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//
void AddPoints(){                                          //
    int i, j, sum, count=0;                                //
    for(i=0;i<ROW;i++){                                    //
        sum = 0;                                           //
        for(j=0;j< COL;j++) {                              //
            sum+=Tab[i][j];                                //
        }                                                  //
        if(sum==COL){                                      //
            count++;                                       //
            int l, k;                                      //
            for(k = i;k >=1;k--)                           //
                for(l=0;l<COL;l++)                         //
                    Tab[k][l]=Tab[k-1][l];                 //
            for(l=0;l<COL;l++)                             //
                Tab[k][l]=0;                               //
        }                                                  //
    }                                                      //
    timer-=1000; score += 100*count;                       //
}                                                          //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//
// views the table in the terminal //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
void PrintTab(){                                                                                    //
    char buf_TAB[ROW][COL] = {0};                                                                   //
    int i, j;                                                                                       //
    for(i = 0; i < current.width ;i++){                                                             //
        for(j = 0; j < current.width ; j++){                                                        //
            if(current.tab[i][j])                                                                   //
                buf_TAB[current.row+i][current.col+j] = current.tab[i][j];                          //
        }                                                                                           //
    }                                                                                               //
    clear();                                                                                        //
    for(i = 0; i < ROW ;i++){                                                                       //
        for(j = 0; j < COL ; j++){                                                                  //
            colors("31;48");                                                                        //
            printw("%c ", (Tab[i][j] + buf_TAB[i][j])? '@': '-');                                   //
        }                                                                                           //
        printw("\n");                                                                               //
    }                                                                                               //
                                                                                                    //
    printw("\nScore: %d\n", score);                                                                 //
    printw("\n");                                                                                   //
    printw("Move right : 'd'\nMove left : 'q'\nMove down : 's'\nChange position : 'z'");            //
}                                                                                                   //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//



//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//
//  moves shapes like you want //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
void move_TRIO(int action){                                                                         //
    Shape temp = trio_COPY(current);                                                                //
    switch(action){                                                                                 //
        case 's':                                                                                   //
            temp.row++;  //moves to down                                                            //
            if(Position(temp))                                                                      //
                current.row++;                                                                      //
            else {                                                                                  //
                WriteToTab();                                                                       //
                AddPoints(); //checks full lines, after putting it down                             //
                rdm_shape();                                                                        //
            }                                                                                       //
            break;                                                                                  //
        case 'd':                                                                                   //
            temp.col++;  //moves to right                                                           //
            if(Position(temp))                                                                      //
                current.col++;                                                                      //
            break;                                                                                  //
        case 'q':                                                                                   //
            temp.col--;  //moves to left                                                            //
            if(Position(temp))                                                                      //
                current.col--;                                                                      //
            break;                                                                                  //
        case 'z':                                                                                   //
            TurnShape_postion(temp);  //changes position                                            //
            if(Position(temp))                                                                      //
                TurnShape_postion(current);                                                         //
            break;                                                                                  //
    }                                                                                               //
    supprShape(temp);                                                                               //
    PrintTab();                                                                                     //
}                                                                                                   //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//

void menu()
{
    int choice = 0;
    int yesNo = 0;
    
    
        printf("\n\n\n\t\t\t1. Would you like to to maths");
        printf("\n\t\t\t2. Or would you like to play with me...");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            maths();
            break;
        case 2:
            srand(time(0));
            score = 0;
            int c;
            initscr();
            struct timeval b, a;
            gettimeofday(&b, NULL);
            nodelay(stdscr, TRUE);
            struct timespec ts = {0, 1000000}; /*sleeps for 100 microsec*/
            timeout(1);
            inline int is_later(){
                return ((suseconds_t)(a.tv_sec*1000000 + a.tv_usec) -((suseconds_t)b.tv_sec*1000000 + b.tv_usec)) > timer;
            }
            rdm_shape();
            PrintTab();
            while(activePlay){
                if ((c = getch()) != ERR) {
                  move_TRIO(c);
                }
                gettimeofday(&a, NULL);
                 if (is_later()) { /*time difference in microsec accuracy*/
                    move_TRIO('s');
                    gettimeofday(&b, NULL); /*again, it's for accuracy*/
                }
            }
            printw("\nGame over!\n");
            supprShape(current);
            endwin();
            system("clear");
            printf("\n\n\t\t\t------------ You lose !------------\n\n\n");
            break;

        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            /*Switch Ended*/
} 
