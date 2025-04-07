#include <window.h>

sfRenderWindow *window = NULL;
sfRectangleShape *line = NULL;
sfClock *clock = NULL;
sfText *gameOverText = NULL;
enum gameState state = gamePlay;
const int width = 800;
const int height = 600;
const int bitsPerPixel = 32;
const int framesPerSecond = 60;
const char title[20] = "Ping Pong Game";

void initWindow() {
    sfVideoMode mode = {width, height, bitsPerPixel};
    window = sfRenderWindow_create(mode, title, sfDefaultStyle, NULL);

    // initialize here
    initLine();
    initText();
    initBall(window);
    initPaddle(window);
    initScore(window);
}

void initLine() {
    line = sfRectangleShape_create();
    sfRectangleShape_setFillColor(line, sfColor_fromRGB(100, 100, 200));
    sfRectangleShape_setSize(line, (sfVector2f){10.0f, 20.0f});
    sfRectangleShape_setPosition(line, (sfVector2f){(width / 2.0f) - (sfRectangleShape_getSize(line).x / 2.0f), 0.0f});
}

void initText() {
    sfFont *font = sfFont_createFromFile("include/arial.ttf");
    gameOverText = sfText_create();
    sfText_setFont(gameOverText, font);
    sfText_setStyle(gameOverText, sfTextBold);
    sfText_setCharacterSize(gameOverText, 10);
    sfText_setColor(gameOverText, sfYellow);
    sfText_setString(gameOverText, "GAME OVER!\n[PRESS ENTER TO PLAY AGAIN]");
}

void renderLine() {
    for (int i = 0; i < (height / sfRectangleShape_getSize(line).y) / 2; i++) {
        sfRectangleShape_setPosition(
            line, (sfVector2f){sfRectangleShape_getPosition(line).x, (sfRectangleShape_getSize(line).y * i) * 2.0f});
        sfRenderWindow_drawRectangleShape(window, line, NULL);
    }
}

void pollEvent() {
    clock = sfClock_create();
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape)) {
                sfRenderWindow_close(window);
            }
        }

        sfRenderWindow_clear(window, sfBlack);

        update();
        render();

        sfRenderWindow_display(window);
    }
}

void update() {
    if (state == gamePlay) {
        if (sfTime_asMilliseconds(sfClock_getElapsedTime(clock)) >= (1000.0f / (float)(framesPerSecond))) {
            // update here
            updateBall(window);
            updatePaddle(window);
            updateScore(window);
        }
    }
}

void render() {
    // render here
    renderLine(window);
    renderBall(window);
    renderPaddle(window);
    renderScore(window);
    if (state == gameOver) {
        sfRenderWindow_drawText(window, gameOverText, NULL);
        if (sfKeyboard_isKeyPressed(sfKeyReturn)) {
            resetScore();
            restartBall(rand() % 2);
            state = gamePlay;
        }
    }
}
