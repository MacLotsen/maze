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

#ifndef MAZE_MAZE_RENDERER_H
#define MAZE_MAZE_RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <conio.h>
#else
#define _GNU_SOURCE
#include <curses.h>
#endif

#include "../libmaze/maze.h"

void simple_renderer(maze_t *maze);

void box_drawing_renderer(maze_t *maze);

#ifdef __cplusplus
}
#endif

#endif //MAZE_MAZE_RENDERER_H
