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
#include "maze-renderer.h"


void simple_renderer(maze_t *maze) {
    int print_width = maze->width + 1;
    int print_height = maze->height + 1;

    char **print_grid = (char**) calloc((size_t) (print_height), sizeof(char**));
    for (int i = 0; i < print_height; i++)
        print_grid[i] = (char*) calloc((size_t) (print_width), sizeof(char*));

    // fill top bar
    for (int xi = 0; xi < maze->width; xi++) {
        int x = xi * 2;
        print_grid[0][x] = '.';
        print_grid[0][x+1] = (char) ((maze->tiles[xi] & TOP_OPEN) ? ' ' : '_');
        print_grid[0][x+2] = '.';
    }

    // fill left bar
    for (int yi = 0; yi < maze->height; yi++) {
        int y = yi + 1;
        print_grid[y][0] = (char) ((maze->tiles[yi*maze->width] & LEFT_OPEN) ? '.' : '|');
    }

    // fill right, bottom
    for (int xi = 0; xi < maze->width; xi++) {

        for (int yi = 0; yi < maze->height; yi++) {
            int i = (yi) * maze->width + xi;
            int x = xi * 2;
            int y = yi+1;
            print_grid[y][x+1] = (char) ((maze->tiles[i] & BOTTOM_OPEN) ? ' ' : '_');
            print_grid[y][x+2] = (char) ((maze->tiles[i] & RIGHT_OPEN) ? '.' : '|');
        }

    }

    // print the print grid
    for (int x = 0; x < print_height; x++) {
//        mvprintw(x, 0, print_grid[x]);
        printf("%s\n", print_grid[x]);
    }
    refresh();
}
