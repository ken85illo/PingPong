#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SFML/Graphics.h>
#include <paddle.h>
#include <math.h>

extern sfCircleShape *ball;
extern sfClock *timer;
extern sfVector2f startPos;
extern const float radius;
extern const int maxSpeedX;
extern const int maxSpeedX;
extern const int maxSpeedY;
extern const int minSpeedY;
extern const float decimal;
extern float speedX;
extern float speedY;

void initBall(sfRenderWindow *window);
void updateBall(sfRenderWindow *window);
void renderBall(sfRenderWindow *window);

void restartBall(sfBool paddleWon);
float getBallTop();
float getBallBottom();
float getBallLeft();
float getBallRight();

#endif