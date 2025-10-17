#include <stdio.h>
#include <windows.h>

#include "console_utils.h"

char background = ' ';

char *flower0[7] = {

    "_( )_    ",
    "(_(@)_)   ",
    " (_)\\    ",
    "     | __",
    "     |/_/",
    "     |   ",
    "     |   "
};

char *flower1[7] = {

    "  _( )_    ",
    " (_(@)_)   ",
    "  (_)|    ",
    "     | __",
    "     |/_/",
    "     |   ",
    "     |   "
};

char *flower2[7] = {

    "     _( )_    ",
    "    (_(@)_)   ",
    "     |(_)    ",
    "     | ___",
    "     |/__/",
    "     |   ",
    "     |   "
};

char *flower3[7] = {

    "      _( )_    ",
    "    (_(@) _)   ",
    "     |(_)    ",
    "     | ___",
    "     |/__/",
    "     |   ",
    "     |   "
};

struct Entity {

    char* name;
    char symbol;
    int x;
    int y;
};

struct Entity player = { "Player", '>', 16, 8 };

void putChar(int x, int y, char c) {

    setCursor(x, y);
    putchar(c);
}

void drawArt(int x, int y, char **art, int height, char replace) {

    for (int row = 0; row < height; ++row) {

        const char *line = art[row];

        for (int col = 0; line[col] != '\0'; ++col) {

            char c = line[col];

            if (c == ' ')
                c = replace;

            putChar(x + col, y + row, c);
        }
    }
}

int* mouse() {

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    int* mouse = malloc(sizeof(int) * 3);

    INPUT_RECORD ir;
    DWORD count;

    ReadConsoleInput(hIn, &ir, 1, &count);

    if (ir.EventType == MOUSE_EVENT) {

        MOUSE_EVENT_RECORD m = ir.Event.MouseEvent;

        if (m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {

            mouse[0] = 1;

        } else if (m.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {

            mouse[0] = 2;
        }

        mouse[1] = m.dwMousePosition.X;
        mouse[2] = m.dwMousePosition.Y;
    }

    return mouse;
}

void updatePlayer() {

    int sprint = 1;

    if (GetAsyncKeyState(VK_LSHIFT)) sprint++;

    if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) {
        player.x -= sprint; //A
        player.symbol = '<';
    }
    if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)) {
        player.x += sprint; //D
        player.symbol = '>';
    }
    if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) {
        player.y -= sprint; //W
        player.symbol = '^';
    }
    if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) {
        player.y += sprint; //S
        player.symbol = 'v';
    }

    if (player.x <= 0) player.x = 1;
    if (player.x >= WIDTH) player.x = WIDTH - 1;
    if (player.y <= 0) player.y = 1;
    if (player.y >= HEIGHT) player.y = HEIGHT - 1;
}

void flowerAnimation(const int tick) {

    const int q = tick / 20;
    const int e = q * 20;
    int w = tick;

    if (tick >= 20) {

        w = tick - e;
    }

    if (w <= 5) drawArt(16, 8, flower0, 7, background);
    else if (w <= 10) drawArt(16, 8, flower1, 7, background);
    else if (w <= 15) drawArt(16, 8, flower2, 7, background);
    else if (w <= 20) drawArt(16, 8, flower3, 7, background);
}

int main() {

    int tick = 0;

    disableQuickEdit();
    fixConsoleSize();

    while (1) {

        tick++;

        hideCursor();
        setScreen(background);
        setCursor(0,0);

        printf("Use arrow or WASD keys, ESC to quit. x,y:%d,%d\n", player.x, player.y);

        updatePlayer();

        flowerAnimation(tick);
        putChar(player.x, player.y, player.symbol);

        Sleep(50);

        if (GetAsyncKeyState(VK_ESCAPE)) break;
    }
}