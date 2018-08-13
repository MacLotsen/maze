//
// Created by erik on 23-7-18.
//

#ifndef MAZE_MAZE_RENDERER_H
#define MAZE_MAZE_RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <conio.h>
#else
#include <curses.h>
#endif

#include "maze.h"

void simple_renderer(maze_t *maze);

void box_drawing_renderer(maze_t *maze);

#ifdef __cplusplus
}
#endif

#endif //MAZE_MAZE_RENDERER_H
