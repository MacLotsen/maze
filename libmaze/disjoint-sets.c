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

#include <stdlib.h>
#include "disjoint-sets.h"


disjoint_sets_t* create_disjoint_sets(unsigned int grid_length) {
    disjoint_sets_t* _disjoint_sets;
    _disjoint_sets = malloc(sizeof(disjoint_sets_t));
    _disjoint_sets->size = grid_length;
    _disjoint_sets->values = malloc(sizeof(disjoint_sets_t) * grid_length);
    for (unsigned int i = 0; i < grid_length; i++)
        _disjoint_sets->values[i] = -1;
    return _disjoint_sets;
}


void destroy_disjoint_sets(disjoint_sets_t *sets) {
    free(sets->values);
    free(sets);
}


unsigned int find_root(disjoint_sets_t* sets, unsigned int index) {
    if (sets->values[index] < 0)
        return index;
    else
        return sets->values[index] = (int) find_root(sets, sets->values[index]);
}


int create_joint(disjoint_sets_t* sets, unsigned int set_i, unsigned int set_j) {
    unsigned int set_i_root = find_root(sets, set_i);
    unsigned int set_j_root = find_root(sets, set_j);
    if (sets->values[set_i_root] < 0 && sets->values[set_j_root] < 0 && set_i_root != set_j_root) {
        sets->values[set_i_root] = (int) (sets->values[set_i_root] + sets->values[set_j_root]);
        sets->values[set_j_root] = (int) set_i_root;
        return 1;
    }
    return 0;
}


int are_joined(disjoint_sets_t *sets, unsigned int set_i, unsigned int set_j) {
    return find_root(sets, set_i) == find_root(sets, set_j);
}


int size_of_sets(disjoint_sets_t const *sets) {
    int size = 0;
    for (int i = 0; i < sets->size; i++)
        if (sets->values[i] < 0) size++;
    return size;
}


int size_of(disjoint_sets_t const *sets, unsigned int set_i) {
    if (sets->values[set_i] < 0)
        return sets->values[set_i] * -1;
    return -1;
}
