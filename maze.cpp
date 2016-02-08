//
// Created by Erik on 2/4/2016.
//

#include <iostream>
#include "maze.h"

Maze::Maze(int width, int height) {
    size = width * height;
    edge_count = size - 1;
    S = new pair<int,int>[edge_count];
    this->width = width;
    this->height = height;

    DisjointSets tree  (size);

    int i (0);

    srand (time(NULL));

    while (tree.size() > 1) {

        if (i >= size)
            throw new exception();

        int p, q, pr, qr;

        next_relation(p, q);

        pr = tree.find_root(p);
        qr = tree.find_root(q);

        if (pr != qr && !is_open(p, q)) {
            tree.joint(pr, qr);
            pair<int, int> R (p, q);
            S[i++] = R;
        }

    }

};

void Maze::next_relation(int &p, int &q) {
    p = rand() % size;

    if(rand() % 2 == 1 && (p + 1) % width != 0)
        // coinflip and has right neighbour
        q = p + 1;

    else if(p + width < size)
        // has bottom neighbour
        q = p + width;

    else
        // retry
        next_relation(p, q);

};

bool Maze::is_open(int p, int q) const {
    for (int i = 0; i < edge_count; i++) {
        pair<int, int> R = S[i];
        if ( (p == R.first && q == R.second)
                /* || (p == R.second && q == R.first) */ )
            return true;
    }
    return false;
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
    delete this->S;
}
