#include <stdio.h>
#include <windows.h>

#include "console_utils.h"
#include "art_renderer.h"
#include "game.h"

struct Entity player = { "Player", '>', 16, 8 };
struct World  world  = { "Praia",  ' ', 128, 32 };

int tick = 0;

void tick_player() {

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

    putChar(player.x, player.y, player.symbol);
}

void tick_world() {

    tick++;

    art_flower(tick, world);
    tick_player();
}