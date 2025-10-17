#include <stdio.h>
#include <windows.h>

#include "console_utils.h"

int main() {

    char player;

    int x = 16, y = 8;
    int side = 3;

    disableQuickEdit();
    fixConsoleSize();

    while (1) {

        int sprint = 1;

        hideCursor();
        clearScreen();
        setCursor(0,0);

        printf("Use arrow or WASD keys, ESC to quit. x,y:%d,%d\n", x, y);

        if (GetAsyncKeyState(VK_LSHIFT)) sprint++;

        if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) {
            x -= sprint; //A
            side = 1;
        }
        if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)) {
            x += sprint; //D
            side = 3;
        }
        if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) {
            y -= sprint; //W
            side = 0;
        }
        if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) {
            y += sprint; //S
            side = 2;
        }

        if (GetAsyncKeyState(VK_ESCAPE)) break;

        switch (side) {

            case 0: player = '^'; break;
            case 1: player = '<'; break;
            case 2: player = 'v'; break;
            default: player = '>';
        }

        if (x <= 0) x = 1;
        if (x >= WIDTH) x = WIDTH - 1;
        if (y <= 0) y = 1;
        if (y >= HEIGHT) y = HEIGHT - 1;

        setCursor(x, y);
        putchar(player);

        Sleep(50);
    }
}