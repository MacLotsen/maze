//
// Created by erik on 14-6-18.
//

#ifndef MAZE_DISJOINTSETS_H
#define MAZE_DISJOINTSETS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct disjoint_sets {
    int size;
    int* values;
} disjoint_sets_t;

disjoint_sets_t* create_disjoint_sets(int grid_length);

void destroy_disjoint_sets(disjoint_sets_t *sets);

int find_root(disjoint_sets_t* sets, int index);

int joint(disjoint_sets_t* sets, int set_i, int set_j);

int size_of_sets(disjoint_sets_t *sets);

int size_of(disjoint_sets_t* sets, int set_i);

#ifdef __cplusplus
}
#endif

#endif //MAZE_DISJOINTSETS_H
