#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include <SFML/Graphics.h>

extern sfRectangleShape *paddle[2];
extern float paddleWidth;
extern float paddleHeight;

void initPaddle(sfRenderWindow *window);
void updatePaddle(sfRenderWindow *window);
void renderPaddle(sfRenderWindow *window);

float getPaddleTop(sfRectangleShape *paddle);
float getPaddleBottom(sfRectangleShape *paddle);
float getPaddleLeft(sfRectangleShape *paddle);
float getPaddleRight(sfRectangleShape *paddle);

#endif