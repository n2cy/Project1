
#include <stdio.h>                                                                                  //
#include <stdlib.h>                                                                                 //                                                                               //
#include <ncurses.h>                                                                
#include <sys/time.h>                                                                            
#include <time.h>

#include "other.h"
#include "tetris.h"
#include "colors.h"



//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//  Task : Print Hello msg        //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//
void headMessage(void)                                                     
{                                                                              
    system("clear");
    colors("35:48");
    printf("\n\t\t\t------------ [ Welcome to the 'System' ]------------");
     
}
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
//  Task : waiting key            //
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//
void welcomeMessage()
{
    
    printf("\n\n\n\t\t\t Loading enter any key to continue.....");
    getchar();
    system("clear");
}
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*//