//
// Created by Erik on 2/4/2016.
//

#include <iostream>
#include "disjoint.h"

#ifndef DISJOINT_SET_MAZE_H
#define DISJOINT_SET_MAZE_H

#endif //DISJOINT_SET_MAZE_H

using namespace std;

class Maze {

public:
    int width, height, size;
    Tree tree;

    Maze(int width, int height);

    void print();

private:
    void next_relation(int &p, int &q);

};