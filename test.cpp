//
// Created by Erik on 2/4/2016.
//

#include <assert.h>
#include "disjoint.h"

int test_disjoint() {

    int SIZE = 9;

    Tree tree(SIZE);

    // expected: -1 -1 -1 -1 -1 -1 -1 -1 4
    tree.joint(4, 8);
    assert(tree.find_root(8) == 4);

    // note that 8 is already replaced with 4 thanks to the find_root()
    // expected: -1 -1  4 -1 -1 -1 -1 -1 4
    tree.joint(tree.find_root(8), 2);
    assert(tree.find_root(2) == 4);

    // expect the size of 4 to be 3
    assert(tree.size_of(4) == 3);

    // expect that the count of collections is ( size - 2 )
    assert(tree.size() == SIZE - 2);


};