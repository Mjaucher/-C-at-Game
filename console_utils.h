#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>

#ifndef WIDTH
#define WIDTH 128
#endif

#ifndef HEIGHT
#define HEIGHT 32
#endif

void setCursor(int x, int y);
void hideCursor();
void clearScreen();
void fixConsoleSize();
void disableQuickEdit();

#endif
