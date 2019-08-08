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

#ifndef MAZE_DISJOINTSETS_H
#define MAZE_DISJOINTSETS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct disjoint_sets {
    unsigned int size;
    int* values;
} disjoint_sets_t;

disjoint_sets_t* create_disjoint_sets(unsigned int grid_length);

void destroy_disjoint_sets(disjoint_sets_t *sets);

unsigned int find_root(disjoint_sets_t *sets, unsigned int index);

int create_joint(disjoint_sets_t *sets, unsigned int set_i, unsigned int set_j);
int are_joined(disjoint_sets_t *sets, unsigned int set_i, unsigned int set_j);

int size_of_sets(disjoint_sets_t const *sets);
int size_of(disjoint_sets_t const *sets, unsigned int set_i);

#ifdef __cplusplus
}
#endif

#endif //MAZE_DISJOINTSETS_H
