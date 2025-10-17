#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>

#ifndef WIDTH
#define WIDTH 128
#endif

#ifndef HEIGHT
#define HEIGHT 32
#endif

void putChar(int x, int y, char c);
int* getMouse();
void setCursor(int x, int y);
void hideCursor();
void setScreen(char background);
void fixConsoleSize();
void disableQuickEdit();

#endif
