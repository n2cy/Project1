#ifndef TETRIS__H
#define TETRIS__H

typedef struct {                                                                                   
    char **tab;                                                                                    
    int width, row, col;                                                                           
} Shape;    

Shape trio_COPY(Shape shape);

void supprShape(Shape shape);

int Position(Shape shape);

void rdm_shape();

void TurnShape_postion(Shape shape);

void WriteToTab();

void AddPoints();

void PrintTab();

void move_TRIO(int action);

void menu();



#endif // TETRIS__H