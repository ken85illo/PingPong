#include <paddle.h>

sfRectangleShape *paddle[2];
float paddleWidth = 8.0f;
float paddleHeight = 130.0f;
float speed = 2.0f;

void initPaddle(sfRenderWindow *window) {
    for (int i = 0; i < 2; i++) {
        paddle[i] = sfRectangleShape_create();
        sfRectangleShape_setFillColor(paddle[i], sfWhite);
        sfRectangleShape_setSize(paddle[i], (sfVector2f){paddleWidth, paddleHeight});
    }

    sfVector2f startPos = {10.0f, (sfRenderWindow_getSize(window).y / 2.0f) - (paddleHeight / 2.0f)};
    sfRectangleShape_setPosition(paddle[0], startPos);
    sfRectangleShape_setOrigin(paddle[0],
                               (sfVector2f){getPaddleLeft(paddle[0]) - sfRectangleShape_getPosition(paddle[0]).x,
                                            getPaddleTop(paddle[0]) - sfRectangleShape_getPosition(paddle[0]).y});

    startPos = (sfVector2f){sfRenderWindow_getSize(window).x - 10.0f - paddleWidth,
                            (sfRenderWindow_getSize(window).y / 2.0f) - (paddleHeight / 2.0f)};
    sfRectangleShape_setPosition(paddle[1], startPos);
    sfRectangleShape_setOrigin(paddle[1],
                               (sfVector2f){getPaddleLeft(paddle[1]) - sfRectangleShape_getPosition(paddle[1]).x,
                                            getPaddleTop(paddle[1]) - sfRectangleShape_getPosition(paddle[1]).y});
}

void updatePaddle(sfRenderWindow *window) {
    // control paddle 1
    if (sfKeyboard_isKeyPressed(sfKeyW)) {
        sfRectangleShape_move(paddle[0], (sfVector2f){0.0f, -speed});
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        sfRectangleShape_move(paddle[0], (sfVector2f){0.0f, speed});
    }

    // restrict paddle 1 to window
    if (getPaddleTop(paddle[0]) < 0.0f) {
        sfRectangleShape_setPosition(paddle[0], (sfVector2f){getPaddleLeft(paddle[0]), 0.0f});
    } else if (getPaddleBottom(paddle[0]) > sfRenderWindow_getSize(window).y) {
        sfRectangleShape_setPosition(
            paddle[0], (sfVector2f){getPaddleLeft(paddle[0]), sfRenderWindow_getSize(window).y - paddleHeight});
    }

    // control paddle 2
    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        sfRectangleShape_move(paddle[1], (sfVector2f){0.0f, -speed});
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        sfRectangleShape_move(paddle[1], (sfVector2f){0.0f, speed});
    }

    // restrict paddle 2 to window
    if (getPaddleTop(paddle[1]) < 0.0f) {
        sfRectangleShape_setPosition(paddle[1], (sfVector2f){getPaddleLeft(paddle[1]), 0.0f});
    } else if (getPaddleBottom(paddle[1]) > sfRenderWindow_getSize(window).y) {
        sfRectangleShape_setPosition(
            paddle[1], (sfVector2f){getPaddleLeft(paddle[1]), sfRenderWindow_getSize(window).y - paddleHeight});
    }
}

void renderPaddle(sfRenderWindow *window) {
    for (int i = 0; i < 2; i++) {
        sfRenderWindow_drawRectangleShape(window, paddle[i], NULL);
    }
}

float getPaddleTop(sfRectangleShape *paddle) { return sfRectangleShape_getGlobalBounds(paddle).top; }

float getPaddleBottom(sfRectangleShape *paddle) { return sfRectangleShape_getGlobalBounds(paddle).top + paddleHeight; }

float getPaddleLeft(sfRectangleShape *paddle) { return sfRectangleShape_getGlobalBounds(paddle).left; }

float getPaddleRight(sfRectangleShape *paddle) { return sfRectangleShape_getGlobalBounds(paddle).left + paddleWidth; }
