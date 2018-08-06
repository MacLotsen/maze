//
// Created by erik on 14-6-18.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <getopt.h>

#include "maze.h"
#include "maze-renderer.h"

int main(int argc, char **argv) {
    int flag_simple = 0;
    int value_width = 15;
    int value_height = 7;
    int c;

    opterr = 0;

    while((c = getopt(argc, argv, "sw:h:")) != -1)
      switch(c) {
        case 's':
          flag_simple = 1;
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

    // create maze
    maze_t *maze = create_maze(value_width, value_height);

    // open top-right corner
    maze->tiles[value_width-1] |= TOP_OPEN;
    // open bottom-left corner
    maze->tiles[(value_height - 1) * value_width] |= BOTTOM_OPEN;
    // open top-mid
//    maze->tiles[WIDTH / 2] |= TOP_OPEN;
    // open bottom-mid
//    maze->tiles[(HEIGHT - 1) * WIDTH + (WIDTH / 2)] |= BOTTOM_OPEN;

    if (flag_simple)
      simple_renderer(maze);
    else
      box_drawing_renderer(maze);

    destroy_maze(maze);
}
