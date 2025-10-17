// game.h
#ifndef GAME_H
#define GAME_H

struct Entity { char name[16]; char symbol; int x; int y; };
struct World { char name[16]; char background; int width; int height; };

extern struct Entity player;
extern struct World world;
extern int tick;

void tick_player(void);
void tick_world(void);

#endif