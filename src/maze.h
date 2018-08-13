//
// Created by erik on 14-6-18.
//

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
