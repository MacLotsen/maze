//
// Created by erik on 14-6-18.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "maze-renderer.h"

#define WIDTH 15
#define HEIGHT 7

int main(int argc, char **argv) {
    srand((unsigned int) time(0));

    setlocale(LC_ALL, "");

    // create maze
    maze_t *maze = create_maze(WIDTH, HEIGHT);

    // open top-right corner
    maze->tiles[WIDTH-1] |= TOP_OPEN;
    // open bottom-left corner
    maze->tiles[(HEIGHT - 1) * WIDTH] |= BOTTOM_OPEN;
    // open top-mid
//    maze->tiles[WIDTH / 2] |= TOP_OPEN;
    // open bottom-mid
//    maze->tiles[(HEIGHT - 1) * WIDTH + (WIDTH / 2)] |= BOTTOM_OPEN;

    //simple_renderer(maze);
    box_drawing_renderer(maze);

    destroy_maze(maze);
}