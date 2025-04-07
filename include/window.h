#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <ball.h>
#include <paddle.h>
#include <score.h>

enum gameState
{
    gamePlay = 0,
    gameOver = 1
};

extern sfRenderWindow *window;
extern sfRectangleShape *line;
extern sfClock *clock;
extern sfText *gameOverText;
extern enum gameState state;
extern const int width;
extern const int height;
extern const char title[20];
extern const int bitsPerPixel;
extern const int framesPerSecond;
extern const char title[20];

void initWindow();
void initText();
void initLine();
void renderLine();
void pollEvent();
void update();
void render();

#endif