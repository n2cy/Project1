#ifndef SNAKE__H
#define SNAKE__H

int kbhit (void);

int colliding(int *snakeArray, int snakeLength);

void moveSnake(int *snakeArray, int dirX, int dirY, int speed, int snakeLength);

void letThereBeApple(int* appleX, int* appleY, int *appleEaten);

void eatApple(int *snakeArray, int appleX, int appleY, int *appleEaten, int *snakeLength);

void maths(void);

#endif // SNAKE__H

