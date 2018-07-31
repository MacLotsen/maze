//
// Created by erik on 14-6-18.
//

#include "disjoint-sets.h"

int main(int argc, char ** argv) {
    const int matrix_length = 9;
    disjoint_sets_t* sets = create_disjoint_sets(matrix_length);

    // expected: -1 -1 -1 -1 -2 -1 -1 -1 4
    joint(sets, 4, 8);
    if (find_root(sets, 8) != 4)
        return 1;

    // note that 8 is already replaced with 4 thanks to the find_root()
    // expected: -1 -1  4 -1 -3 -1 -1 -1 4
    joint(sets, find_root(sets, 8), 2);
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
    joint(sets, 0, 1);
    joint(sets, find_root(sets, 0), find_root(sets, 8));

    if (size_of(sets, find_root(sets, 8)) != 5)
        return 5;

    return 0;
}