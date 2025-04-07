#include <ball.h>
#include <stdlib.h>
#include <time.h>

sfCircleShape *ball = NULL;
sfClock *timer = NULL;
sfVector2f startPos;
const float radius = 10.0f;
const int maxSpeedX = 250;
const int minSpeedX = 100;
const int maxSpeedY = 60;
const int minSpeedY = 15;
const float decimal = 100.0f; // thousandths
float speedX = minSpeedX / decimal;
float speedY = minSpeedY / decimal;

void initBall(sfRenderWindow *window) {
    timer = sfClock_create();
    srand(time(0));
    startPos =
        (sfVector2f){(sfRenderWindow_getSize(window).x / 2) - radius, (sfRenderWindow_getSize(window).y / 2) - radius};

    ball = sfCircleShape_create();
    sfCircleShape_setFillColor(ball, sfWhite);
    sfCircleShape_setRadius(ball, radius);
    sfCircleShape_setOrigin(ball, (sfVector2f){getBallLeft() - sfCircleShape_getPosition(ball).x,
                                               getBallTop() - sfCircleShape_getPosition(ball).y});
    restartBall(rand() % 2);
}

void updateBall(sfRenderWindow *window) {
    // movement in x-axis
    if (sfTime_asSeconds(sfClock_getElapsedTime(timer)) >= 3.0f) {
        sfCircleShape_move(ball, (sfVector2f){speedX, speedY});
    }

    // bounds from x-axis
    //  if(getBallLeft() < 0.0f)
    //  {
    //      sfCircleShape_setPosition(ball, (sfVector2f){0.0f, getBallTop()});
    //      speedX *= -1.0f;
    //  }
    //  else if (getBallRight() > sfRenderWindow_getSize(window).x)
    //  {
    //      sfCircleShape_setPosition(ball, (sfVector2f){sfRenderWindow_getSize(window).x-(radius*2), getBallTop()});
    //      speedX *= -1.0f;
    //  }

    // bounds from y-axis
    if (getBallTop() < 0.0f) {
        sfCircleShape_setPosition(ball, (sfVector2f){getBallLeft(), 0.0f});
        speedY *= -1.0f;
    } else if (getBallBottom() > sfRenderWindow_getSize(window).y) {
        sfCircleShape_setPosition(ball, (sfVector2f){getBallLeft(), sfRenderWindow_getSize(window).y - (radius * 2)});
        speedY *= -1.0f;
    }

    // bounce on paddle (left)
    if (getBallBottom() >= getPaddleTop(paddle[0]) && getBallTop() <= getPaddleBottom(paddle[0])) {
        if (getBallLeft() < getPaddleRight(paddle[0]) && getBallLeft() > getPaddleLeft(paddle[0])) {
            sfCircleShape_setPosition(ball, (sfVector2f){getPaddleRight(paddle[0]), getBallTop()});
            speedX = ((rand() % (maxSpeedX - minSpeedX)) + maxSpeedX) / decimal;

            if (speedY > 0.0f)
                speedY = ((rand() % (maxSpeedY - minSpeedY)) + maxSpeedY) / decimal;
            else
                speedY = (((rand() % (maxSpeedY - minSpeedY)) + maxSpeedY) / decimal) * -1.0f;
        }
    }

    // bounce on paddle (right)
    if (getBallBottom() >= getPaddleTop(paddle[1]) && getBallTop() <= getPaddleBottom(paddle[1])) {
        if (getBallRight() > getPaddleLeft(paddle[1]) && getBallRight() < getPaddleRight(paddle[1])) {
            sfCircleShape_setPosition(ball, (sfVector2f){getPaddleLeft(paddle[1]) - (radius * 2), getBallTop()});
            speedX = (((rand() % (maxSpeedX - minSpeedX)) + maxSpeedX) / decimal) * -1.0f;

            if (speedY > 0.0f)
                speedY = ((rand() % (maxSpeedY - minSpeedY)) + maxSpeedY) / decimal;
            else
                speedY = (((rand() % (maxSpeedY - minSpeedY)) + maxSpeedY) / decimal) * -1.0f;
        }
    }
}

void renderBall(sfRenderWindow *window) { sfRenderWindow_drawCircleShape(window, ball, NULL); }

void restartBall(sfBool paddleWon) {
    sfCircleShape_setPosition(ball, startPos);
    speedX = (paddleWon == 0) ? minSpeedX / decimal : -minSpeedX / decimal;
    speedY = minSpeedY / decimal;
    sfClock_restart(timer);
}

float getBallTop() { return sfCircleShape_getGlobalBounds(ball).top; }

float getBallBottom() { return sfCircleShape_getGlobalBounds(ball).top + (radius * 2); }

float getBallLeft() { return sfCircleShape_getGlobalBounds(ball).left; }

float getBallRight() { return sfCircleShape_getGlobalBounds(ball).left + (radius * 2); }
