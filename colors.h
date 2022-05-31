#ifndef COLORS__H
#define COLORS__H

#include <stdio.h>

#define clrscr() printf("\033[H\033[2J")

#define colors(param) printf("\033[%sm",param)

#endif // COLORS__H