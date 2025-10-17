#include "console_utils.h"
#include "game.h"

char *moroni[3] = {

    " * ",
    " _ ",
    "<_>"
};

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

void art_draw(int x, int y, char **art, int height, char replace) {

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

void art_flower(const int tick, const struct World world) {

    const int q = tick / 20;
    const int e = q * 20;
    int w = tick;

    if (tick >= 20) {

        w = tick - e;
    }

    if (w <= 5) art_draw(16, 8, flower0, 7, world.background);
    else if (w <= 10) art_draw(16, 8, flower1, 7, world.background);
    else if (w <= 15) art_draw(16, 8, flower2, 7, world.background);
    else if (w <= 20) art_draw(16, 8, flower3, 7, world.background);
}