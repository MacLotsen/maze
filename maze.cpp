//
// Created by Erik on 2/4/2016.
//

#include <stdlib.h>
#include "maze.h"

Maze::Maze(int width, int height) {
    size = width * height;
    edge_count = size;
    edges = new std::pair<bool, bool>[edge_count];
    this->width = width;
    this->height = height;

    DisjointSets tree(size);

    srand(time(NULL));

    while (tree.size() > 1) {

        int p, q, pr, qr;

        short direction = -1;

        next_relation(p, q, direction);

        pr = tree.find_root(p);
        qr = tree.find_root(q);

        if (pr != qr && !is_open(p, direction == 1)) {
            tree.joint(pr, qr);
            if (direction == 1) {
                edges[p].first = true;
            } else if (direction == 2) {
                edges[p].second = true;
            }
        }

    }

};

void Maze::next_relation(int &p, int &q, short &d) {
    p = rand() % size;

    if (rand() % 2 == 1 && (p + 1) % width != 0) {
        // coinflip and has right neighbour
        d = 1;
        q = p + 1;

    } else if (p + width < size) {
        // has bottom neighbour
        d = 2;
        q = p + width;

    } else
        // retry
        next_relation(p, q, d);

};

bool Maze::is_open(const int index, const bool is_right) const {
    return is_right ? edges[index].first : edges[index].second;
};

int Maze::get_size() const {
    return size;
}

int Maze::get_width() const {
    return width;
}

int Maze::get_height() const {
    return height;
}

Maze::~Maze() {
    delete this->edges;
}
