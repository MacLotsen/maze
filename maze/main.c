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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <getopt.h>
#include <signal.h>

#include "../libmaze/maze.h"
#include "maze-renderer.h"


void quit() {
    endwin();
    exit(0);
}


int main(int argc, char **argv) {
    // Default option values
    int flag_simple = 0;
    int flag_interactive = 0;
    int value_width = 15;
    int value_height = 7;
    int c;

    opterr = 0;

    // Parsing options passed through commandline
    while ((c = getopt(argc, argv, "siw:h:")) != -1)
        switch (c) {
            case 's':
                flag_simple = 1;
                break;
            case 'i':
                flag_interactive = 1;
                break;
            case 'w':
                value_width = atoi(optarg);
                break;
            case 'h':
                value_height = atoi(optarg);
                break;
            default:
                return 1;
        }

    srand((unsigned int) time(0));

    setlocale(LC_ALL, "");

    // Setup NCurses
    signal(SIGINT, quit);
    initscr();
    cbreak();
    noecho();

    // Simple drawer is too compact to use interactively.
    if (flag_simple && flag_interactive) {
        printw("Error: cannot use simple while playing interactively.");
        quit();
    }

    // create maze
    maze_t *maze = create_maze(value_width, value_height);

    // Multiple examples showing how to manually open walls in the maze

    // open top-right corner
    //maze->tiles[value_width-1] |= TOP_OPEN;
    // open bottom-left corner
    //maze->tiles[(value_height - 1) * value_width] |= BOTTOM_OPEN;
    // open top-mid
//    maze->tiles[WIDTH / 2] |= TOP_OPEN;
    // open bottom-mid
//    maze->tiles[(HEIGHT - 1) * WIDTH + (WIDTH / 2)] |= BOTTOM_OPEN;

    if (flag_simple)
        simple_renderer(maze);
    else
        box_drawing_renderer(maze);

    if (flag_interactive) {
        int input;
        int control_state = 0;
        int cur_i = 0;
        int cur_x = 2;
        int cur_y = 1;

        // Always set the end point farthest away from beginning point
        int end_i = farthest_tile(maze, cur_i);
        int end_x = (end_i % maze->width) * 5 + 2;
        int end_y = (end_i / maze->width) * 3 + 1;
        move(end_y, end_x);
        addch(ACS_BOARD);

        move(cur_y, cur_x);
        refresh();

        do {
            input = getch();

            if (input == -1)
                continue;

            if (control_state == 2) {
                // Calculate move
                switch (input) {
                    case 0x41:
                        if (maze->tiles[cur_i] & TOP_OPEN) {
                            cur_i -= maze->width;
                            cur_y -= 3;
                        }
                        break;
                    case 0x43:
                        if (maze->tiles[cur_i] & RIGHT_OPEN) {
                            cur_i += 1;
                            cur_x += 5;
                        }
                        break;
                    case 0x42:
                        if (maze->tiles[cur_i] & BOTTOM_OPEN) {
                            cur_i += maze->width;
                            cur_y += 3;
                        }
                        break;
                    case 0x44:
                        if (maze->tiles[cur_i] & LEFT_OPEN) {
                            cur_i -= 1;
                            cur_x -= 5;
                        }
                        break;
                }

                control_state = 0;
                move(cur_y, cur_x);

                // Check end condition after every move, and regenerate maze.
                if (cur_i == end_i) {
                    destroy_maze(maze);
                    maze = create_maze(value_width, value_height);
                    box_drawing_renderer(maze);
                    end_i = farthest_tile(maze, cur_i);
                    end_x = (end_i % maze->width) * 5 + 2;
                    end_y = (end_i / maze->width) * 3 + 1;
                    move(end_y, end_x);
                    addch(ACS_BOARD);
                    move(cur_y, cur_x);
                }
            }

            // Check if the inputs have an arrow sequence (0x1B 0x5B 0x41-0x44)
            if (input == 0x1B) {
                control_state = 1;
            } else if (input == 0x5B) {
                if (control_state == 1)
                    control_state = 2;
                else
                    control_state = 0;
            }
        } while (input != 'q');
    } else {
        getch();
    }

    destroy_maze(maze);

    endwin();
}
