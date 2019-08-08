/*
 * A simple maze generator written in just C.
 * Copyright (C) 2018  Erik Nijenhuis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include "maze.h"
#include "disjoint-sets.h"


maze_t *create_maze(int width, int height) {
    int size = width * height;
    maze_t *maze = malloc(sizeof(maze_t));
    maze->size = size;
    maze->width = width;
    maze->height = height;
    maze->tiles = calloc((size_t) size, sizeof(tile_mask_t));

    disjoint_sets_t *sets = create_disjoint_sets(size);

    tile_t p, q;
    direction_t direction = 0;

    for (p = 0; size_of_sets(sets) > 1; p++) {

        if (p >= maze->size)
            p -= maze->size;

        direction = coinflip() ? BOTTOM_OPEN : RIGHT_OPEN;
        q = adjacent_tile(maze, p, direction);
        // If already connected; try other
        if (are_joined(sets, p, q)) {
            direction = direction == BOTTOM_OPEN ? RIGHT_OPEN : BOTTOM_OPEN;
            q = adjacent_tile(maze, p, direction);
        }

        if (!is_within_bounds(maze, p, direction))
            continue;

        if (!are_joined(sets, p, q) && !(maze->tiles[p] & direction)) {
            create_joint(sets, p, q);
            direction_t opposite = opposite(direction);
            maze->tiles[p] |= direction;
            maze->tiles[q] |= opposite;
        }

    }

    destroy_disjoint_sets(sets);

    return maze;
}


void destroy_maze(maze_t *maze) {
    free(maze->tiles);
    free(maze);
}


int is_within_bounds(maze_t const *maze, tile_t p, direction_t direction) {
    switch(direction) {
        case TOP_OPEN:
            return p - maze->width >= 0;
        case RIGHT_OPEN:
            return (p + 1) % maze->width != 0;
        case BOTTOM_OPEN:
            return p + maze->width < maze->size;
        case LEFT_OPEN:
            return (p -1) >= 0 && p % maze->width != 0;
        default:
            return 0;
    }
}


tile_t adjacent_tile(maze_t const *maze, tile_t p, direction_t direction) {
    if (direction & TOP_OPEN) {
        return p - maze->width;
    } else if (direction & RIGHT_OPEN) {
        return p + 1;
    } else if (direction & BOTTOM_OPEN) {
        return p + maze->width;
    } else if (direction & LEFT_OPEN) {
        return p - 1;
    }
    return p;
}


static void walk_maze(maze_t const *maze, int **costs, tile_t cx, tile_t cy) {
    // This function will call itself for adjacent tiles which are valid moves.
    // At the end this function will iterate/call itself N times.
    // When this function is done, the costs grid will be filled with the step count for each tile.

    tile_t ci = cy * maze->width + cx;
    int cur_val = costs[cy][cx];

    // Notice that this order has the same as the tile_mask_t enumeration
    int adjacent_tiles[] = {
            ci - maze->width,
            ci + 1,
            ci + maze->width,
            ci - 1
    };

    // Try all adjacent tiles
    for (unsigned int i = 0; i < 4; i++) {
        tile_t ti = adjacent_tiles[i];
        tile_t tx = ti % maze->width;
        tile_t ty = ti / maze->width;


        if (ti < 0 || ti >= maze->size
                || !is_within_bounds(maze, ci, (1 << i))
                || !(maze->tiles[ci] & (1 << i))
                || costs[ty][tx] != -1)
            continue;

        costs[ty][tx] = cur_val+1;
        walk_maze(maze, costs, tx, ty);
    }
}


int farthest_tile(maze_t const *maze, tile_t from) {
    // For those who read this code, this is not dijkstra since many benefits are useless for a maze.
    // Every possible move is calculated and the first farthest point is returned.

    int max = -1;
    int max_tile = -1;
    int fx = from % maze->width;
    int fy = from / maze->width;
    int **costs;
    costs = malloc(sizeof(unsigned int*) * maze->height);
    for (int i = 0; i < maze->height; i++) {
        costs[i] = malloc(sizeof(unsigned int) * maze->width);
        for (int j = 0; j < maze->width; j++) {
            costs[i][j] = -1;
        }
    }

    // Set current position as zero moves done
    costs[fy][fx] = 0;

    // Walk the maze recursively
    walk_maze(maze, costs, fx, fy);

    // Just take the first farthest point
    for (int i = 0; i < maze->size; i++) {
        int cur = costs[i / maze->width][i % maze->width];
        if (cur > max) {
            max = cur;
            max_tile = i;
        }
    }

    free(costs);

    return max_tile;
}
