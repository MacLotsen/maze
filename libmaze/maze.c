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


/**
 * Returns true if the given tile and direction (adjacent tile) is within the field of the maze.
 * For example. When taking tile zero (first tile in the maze) and direction left, it will return false.
 *
 * @param _maze
 * @param _tile
 * @param _dir
 * @return
 */
static int within_bounds(maze_t* _maze, int _tile, char _dir) {
  switch(_dir) {
    case TOP_OPEN:
      return _tile - _maze->width >= 0;
    case RIGHT_OPEN:
      return (_tile + 1) % _maze->width != 0;
    case BOTTOM_OPEN:
      return _tile + _maze->width < _maze->size;
    case LEFT_OPEN:
      return (_tile -1) >= 0 && _tile % _maze->width != 0;
    default:
      return -1;
    }
}


/**
 * This function decides the next two tiles to connect with each other.
 *
 * @param _maze
 * @param _disjoint_sets
 * @param p
 * @param q
 * @param d
 */
static void next_relation(maze_t *_maze, disjoint_sets_t *_disjoint_sets, int *p, int *q, char *d) {
    // Use P (a random point within the maze's bounds) as a starting point.
    for (int i = *p;; i++) {
        // Always ensure a clean index (Preventing out of bounds)
        i = i % _disjoint_sets->size;

        *p = i;

        char dir;
        dir = coinflip() ? BOTTOM_OPEN : RIGHT_OPEN;

        if (!within_bounds(_maze, *p, dir))
            continue;


        if (dir & TOP_OPEN) {
            *q = *p - _maze->width;
        } else if (dir & RIGHT_OPEN) {
            *q = *p + 1;
        } else if (dir & BOTTOM_OPEN) {
            *q = *p + _maze->width;
        } else if (dir & LEFT_OPEN) {
            *q = *p - 1;
        }
        *d = dir;

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

        int p, q, pr, qr;
        char dir = 0;

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


/**
 * This function will -- at the end -- fill the costs with steps taken from the starting point.
 * @param maze
 * @param costs
 * @param cx
 * @param cy
 */
static void walk_maze(maze_t *maze, int **costs, int cx, int cy) {
    // This function will call itself for adjacent tiles which are valid moves.
    // At the end this function will iterate/call itself N times.
    // When this function is done, the costs grid will be filled with the step count for each tile.

    int ci = cy * maze->width + cx;
    int cur_val = costs[cy][cx];

    // Notice that this order has the same as the tile_mask_t enumeration
    int adjacent_tiles[] = {
            ci - maze->width,
            ci + 1,
            ci + maze->width,
            ci - 1
    };

    // Try all adjacent tiles
    for (int i = 0; i < 4; i++) {
        int ti = adjacent_tiles[i];
        int tx = ti % maze->width;
        int ty = ti / maze->width;


        if (ti < 0 || ti >= maze->size
                || !within_bounds(maze, ci, (1 << i))
                || !(maze->tiles[ci] & (1 << i))
                || costs[ty][tx] != -1)
            continue;

        costs[ty][tx] = cur_val+1;
        walk_maze(maze, costs, tx, ty);
    }
}


/**
 * Returns the farthest point from starting point.
 * This is useful for determining the end point.
 *
 * @param maze
 * @param from
 * @return
 */
int farthest_tile(maze_t *maze, int from) {
    // For those who read this code, this is not dijkstra since many benefits are useless for a maze.
    // Every possible move is calculated and the first farthest point is returned.

    int max = -1;
    int max_tile = -1;
    int fx = from % maze->width;
    int fy = from / maze->width;
    int **costs;
    costs = malloc(sizeof(int*) * maze->height);
    for (int i = 0; i < maze->height; i++) {
        costs[i] = malloc(sizeof(int) * maze->width);
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
