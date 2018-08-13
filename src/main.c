//
// Created by erik on 14-6-18.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <getopt.h>
#include <signal.h>

#include "maze.h"
#include "maze-renderer.h"


void quit() {
    endwin();
    exit(0);
}


int main(int argc, char **argv) {
    int flag_simple = 0;
    int flag_interactive = 0;
    int value_width = 15;
    int value_height = 7;
    int c;

    opterr = 0;

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

    signal(SIGINT, quit);
    initscr();
    cbreak();
    noecho();

    if (flag_simple && flag_interactive) {
        printw("Error: cannot use simple while playing interactively.");
        quit();
    }

    // create maze
    maze_t *maze = create_maze(value_width, value_height);

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

        move(cur_y, cur_x);

        do {
            input = getch();

            if (input == -1)
                continue;

            if (control_state == 2) {

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
            }

            if (input == 0x1B) {
                control_state = 1;
            } else if (input == 0x5B) {
                if (control_state == 1)
                    control_state = 2;
                else
                    control_state = 0;
            }
        } while (input != 'q');
    }

    farthest_tile(maze, 0);

    destroy_maze(maze);

    endwin();
}
