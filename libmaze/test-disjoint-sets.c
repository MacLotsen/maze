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

#include "disjoint-sets.h"

int main(int argc, char ** argv) {
    const int matrix_length = 9;
    disjoint_sets_t* sets = create_disjoint_sets(matrix_length);

    // expected: -1 -1 -1 -1 -2 -1 -1 -1 4
    create_joint(sets, 4, 8);
    if (find_root(sets, 8) != 4)
        return 1;

    // note that 8 is already replaced with 4 thanks to the find_root()
    // expected: -1 -1  4 -1 -3 -1 -1 -1 4
    create_joint(sets, find_root(sets, 8), 2);
    if (find_root(sets, 2) != 4)
        return 2;

    // expect the size_of_sets of 4 to be 3
    if (size_of(sets, 4) != 3)
        return 3;

    // expect that the count of collections is ( size_of_sets - 2 )
    if (size_of_sets(sets) != matrix_length - 2)
        return 4;

    // joining a subset
    // expect the size_of_sets to be updated
    create_joint(sets, 0, 1);
    create_joint(sets, find_root(sets, 0), find_root(sets, 8));

    if (size_of(sets, find_root(sets, 8)) != 5)
        return 5;

    return 0;
}