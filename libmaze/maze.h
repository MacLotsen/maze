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

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#ifdef __cplusplus
extern "C" {
#endif

#define opposite(direction) (((direction) < 4) ? direction << 2: direction >> 2)
#define coinflip() (rand() % 2)

typedef enum tile_mask {
  NONE_OPEN = 0x00,
  TOP_OPEN = 0x01,
  RIGHT_OPEN = 0x02,
  BOTTOM_OPEN = 0x04,
  LEFT_OPEN = 0x08
} tile_mask_t;

typedef struct maze {
  int width;
  int height;
  int size;
  char* tiles;
} maze_t;

maze_t* create_maze(int width, int height);
void destroy_maze(maze_t* maze);

int farthest_tile(maze_t* maze, int from);

#ifdef __cplusplus
}
#endif

#endif //MAZE_MAZE_H
