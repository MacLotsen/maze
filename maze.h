//
// Created by Erik on 2/4/2016.
//

#ifndef DISJOINT_SET_MAZE_H
#define DISJOINT_SET_MAZE_H

#include "disjoint.h"
#include <tuple>

class Maze {

public:
    Maze(int width, int height);
    ~Maze();
    bool is_open(const int, const bool) const;
    int get_size() const;
    int get_width() const;
    int get_height() const;

private:
    int width, height, size, edge_count;
    std::pair<bool, bool>*edges;
    void next_relation(int &p, int &q, short &d);

};

#endif //DISJOINT_SET_MAZE_H
