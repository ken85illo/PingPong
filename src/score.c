#include <score.h>
#include <stdio.h>

sfText *scoreText[2];
char text[10];
int charSize = 30;
int score[2];
int maxScore = 5;
float offsetX = 30.0f;
float offsetY = 10.0f;

void initScore(sfRenderWindow *window) {
    sfFont *font = sfFont_createFromFile("include/arial.ttf");
    for (int i = 0; i < 2; i++) {
        scoreText[i] = sfText_create();
        sfText_setCharacterSize(scoreText[i], charSize);
        sfText_setFont(scoreText[i], font);
        sfText_setStyle(scoreText[i], sfTextBold);
        sfText_setColor(scoreText[i], sfColor_fromRGBA(255, 255, 255, 150));
        sprintf(text, "%d", score[i]);
        sfText_setString(scoreText[i], text);
    }

    sfText_setOrigin(scoreText[0], (sfVector2f){sfText_getGlobalBounds(scoreText[0]).width, 0.0f});
    sfText_setPosition(scoreText[0], (sfVector2f){(sfRenderWindow_getSize(window).x / 2) - offsetX, offsetY});
    sfText_setPosition(scoreText[1], (sfVector2f){(sfRenderWindow_getSize(window).x / 2) + offsetX, offsetY});
}

void updateScore(sfRenderWindow *window) {
    if (getBallRight() < 0.0f) {
        score[1]++;
        sprintf(text, "%d", score[1]);
        sfText_setString(scoreText[1], text);
        restartBall(1);
    } else if (getBallLeft() > sfRenderWindow_getSize(window).x) {
        score[0]++;
        sprintf(text, "%d", score[0]);
        sfText_setString(scoreText[0], text);
        restartBall(0);
    }

    sfText_setOrigin(scoreText[0], (sfVector2f){sfText_getGlobalBounds(scoreText[0]).width, 0.0f});

    if (score[0] == maxScore || score[1] == maxScore) {
        score[0] = 0;
        score[1] = 0;
        state = gameOver;
    }
}

void renderScore(sfRenderWindow *window) {
    for (int i = 0; i < 2; i++) {
        sfRenderWindow_drawText(window, scoreText[i], NULL);
    }
}

void resetScore() {
    sprintf(text, "%d", score[0]);
    sfText_setString(scoreText[0], text);
    sprintf(text, "%d", score[1]);
    sfText_setString(scoreText[1], text);
}
