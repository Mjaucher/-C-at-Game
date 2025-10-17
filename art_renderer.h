#ifndef ART_RENDERER_H
#define ART_RENDERER_H

#include "game.h"

void art_draw(int x, int y, char **art, int height, char replace);
void art_flower(const int tick, struct World world);

#endif
