
add_executable(draw_maze main.c disjoint-sets.c disjoint-sets.h maze.h maze.c maze-renderer.h simple-renderer.c box-drawing-renderer.c)
add_executable(test-disjoint test-disjoint-sets.c disjoint-sets.c)
add_test(test-disjointsets test-disjoint)
add_test(test-maze-drawing draw_maze)
