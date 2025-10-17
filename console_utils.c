#include "console_utils.h"
#include <stdio.h>

void disableQuickEdit() {

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;

    if (!GetConsoleMode(hIn, &prevMode))
        return;

    DWORD newMode = prevMode;

    newMode |= ENABLE_EXTENDED_FLAGS;
    newMode &= ~ENABLE_QUICK_EDIT_MODE;
    newMode |= ENABLE_MOUSE_INPUT;
    newMode |= ENABLE_WINDOW_INPUT;

    SetConsoleMode(hIn, newMode);
}

void fixConsoleSize() {

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD size = {WIDTH + 1, HEIGHT + 1};
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