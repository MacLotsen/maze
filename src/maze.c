//
// Created by erik on 14-6-18.
//
#include <stdlib.h>
#include <stdio.h>
#include "maze.h"
#include "disjoint-sets.h"

static void next_relation(maze_t *_maze, disjoint_sets_t *_disjoint_sets, int *p, int *q, int *d) {
    int offset = rand() % _disjoint_sets->size;
    for (int i = offset; 1; i++) {
        i = i % _disjoint_sets->size;

        *p = i;

        int dir;
        dir = coinflip() ? BOTTOM_OPEN : RIGHT_OPEN;

        if (dir & TOP_OPEN) {
            if (*p - _maze->width < 0)
                continue;
            *d = dir;
            *q = *p - _maze->width;
        } else if (dir & RIGHT_OPEN) {
            if ((*p + 1) % _maze->width == 0)
                continue;
            *d = dir;
            *q = *p + 1;
        } else if (dir & BOTTOM_OPEN) {
            if (*p + _maze->width >= _maze->size)
                continue;
            *d = dir;
            *q = *p + _maze->width;
        } else if (dir & LEFT_OPEN) {
            if ((*p - 1) < 0 || (*p - 1) % _maze->width == 0)
                continue;
            *q = *p - 1;
        }

        return;
    }
}

maze_t *create_maze(int width, int height) {
    int size = width * height;
    maze_t *_maze = malloc(sizeof(maze_t));
    _maze->size = size;
    _maze->width = width;
    _maze->height = height;
    _maze->tiles = calloc((size_t) size, sizeof(tile_mask_t));

    disjoint_sets_t *_disjoint_sets = create_disjoint_sets(size);

    while (size_of_sets(_disjoint_sets) > 1) {

        int p, q, pr, qr, dir;
        dir = 0;

        p = rand() % size;
        q = rand() % size;

        next_relation(_maze, _disjoint_sets, &p, &q, &dir);

        pr = find_root(_disjoint_sets, p);
        qr = find_root(_disjoint_sets, q);

        if (pr != qr && !(_maze->tiles[p] & dir)) {
            joint(_disjoint_sets, pr, qr);
            int opposite = opposite(dir);
            _maze->tiles[p] |= dir;
            _maze->tiles[q] |= opposite;
        }

    }

    destroy_disjoint_sets(_disjoint_sets);

    return _maze;
}

void destroy_maze(maze_t *maze) {
    free(maze->tiles);
    free(maze);
}
