//
// Created by Erik on 2/4/2016.
//

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <bits/stl_list.h>
#include "disjoint.h"

#ifndef DISJOINT_SET_MAZE_H
#define DISJOINT_SET_MAZE_H

#endif //DISJOINT_SET_MAZE_H

using namespace std;

class Maze {

public:
    Maze(int width, int height);
    bool is_open(int p, int q);
    void print();

private:
    Tree tree;
    int width, height, size, edge_count;
    pair<int, int>*S;
    void next_relation(int &p, int &q);

};