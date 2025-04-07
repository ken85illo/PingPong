#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SFML/Graphics.h>
#include <ball.h>
#include <window.h>

extern sfText *scoreText[2];
extern char text[10];
extern int charSize;
extern int score[2];
extern int maxScore;
extern float offsetX;
extern float offsetY;

void initScore(sfRenderWindow *window);
void updateScore(sfRenderWindow *window);
void renderScore(sfRenderWindow *window);
void resetScore();

#endif