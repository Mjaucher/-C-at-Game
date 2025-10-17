#include <stdio.h>
#include <windows.h>

#define WIDTH 128
#define HEIGHT 32

void fixConsoleSize() {

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD size = { WIDTH + 1, HEIGHT + 1 };
    SetConsoleScreenBufferSize(hOut, size);

    SMALL_RECT rect = { 0, 0, WIDTH, HEIGHT };
    SetConsoleWindowInfo(hOut, TRUE, &rect);

    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_SIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
}

void setCursor(const int x, const int y) {

    const COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci = {1, FALSE};
    SetConsoleCursorInfo(h, &cci);
}

void clearScreen() {

    COORD topLeft = {0, 0};
    DWORD written, cells;
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(h, &info))
        return;

    cells = info.dwSize.X * info.dwSize.Y;

    FillConsoleOutputCharacter(h, ' ', cells, topLeft, &written);
    SetConsoleCursorPosition(h, topLeft);
}

int main() {

    char player;

    int x = 16, y = 8;
    int side = 3;

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