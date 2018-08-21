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


disjoint_sets_t* create_disjoint_sets(int grid_length) {
    disjoint_sets_t* _disjoint_sets;
    _disjoint_sets = malloc(sizeof(disjoint_sets_t));
    _disjoint_sets->size = grid_length;
    _disjoint_sets->values = malloc(sizeof(disjoint_sets_t) * grid_length);
    for (int i = 0; i < grid_length; i++)
        _disjoint_sets->values[i] = -1;
    return _disjoint_sets;
}

void destroy_disjoint_sets(disjoint_sets_t *sets) {
    free(sets->values);
    free(sets);
}

int find_root(disjoint_sets_t* sets, int index) {
    if (sets->values[index] < 0)
        return index;
    else
        return sets->values[index] = find_root(sets, sets->values[index]);
}


int joint(disjoint_sets_t* sets, int set_i, int set_j) {
    if (sets->values[set_i] < 0 && sets->values[set_j] < 0 && set_i != set_j) {
        sets->values[set_i] = sets->values[set_i] + sets->values[set_j];
        sets->values[set_j] = set_i;
        return 1;
    }
    return 0;
}


int size_of_sets(disjoint_sets_t *sets) {
    int size = 0;
    for (int i = 0; i < sets->size; i++)
        if (sets->values[i] < 0) size++;
    return size;
}


int size_of(disjoint_sets_t *sets, int set_i) {
    if (sets->values[set_i] < 0)
        return sets->values[set_i] * -1;
    return -1;
}
