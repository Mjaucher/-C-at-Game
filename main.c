#include <stdio.h>
#include <windows.h>

#include "console_utils.h"
#include "game.h"

int main() {

    disableQuickEdit();
    fixConsoleSize();

    while (1) {

        hideCursor();
        setScreen(world.background);
        setCursor(0,0);

        printf("x,y:%d,%d\n", player.x, player.y);

        tick_world();

        Sleep(50);

        if (GetAsyncKeyState(VK_ESCAPE)) break;
    }
}