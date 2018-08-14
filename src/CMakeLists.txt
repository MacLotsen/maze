set(MAZE_HEADERS maze.h disjoint-sets.h)

add_library(maze maze.c disjoint-sets.c ${MAZE_HEADERS})

link_libraries(maze)

add_executable(draw_maze main.c maze-renderer.h simple-renderer.c box-drawing-renderer.c ${MAZE_HEADERS})
target_link_libraries(draw_maze ${CURSES_LIBRARIES})

add_executable(test-disjoint test-disjoint-sets.c disjoint-sets.c)

add_test(test-disjointsets test-disjoint)
add_test(test-maze-drawing draw_maze)
