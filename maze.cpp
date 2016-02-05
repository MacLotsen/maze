//
// Created by Erik on 2/4/2016.
//

#include <assert.h>
#include "maze.h"

Maze::Maze(int width, int height) : tree(width * height ) {
    this->size = width * height;
    this->width = width;
    this->height = height;

    srand (time(NULL));

    int p, q;

    next_relation(p, q);

    // TODO validation
//    pair<int, int> pair (p, q);
//    matrix.insert(pair);

    //matrix[p] = q;

    //assert(matrix[p] == q);

    cout << "p: " << p << endl << "q: " << q << endl;

    next_relation(p, q);

    cout << "p: " << p << endl << "q: " << q << endl;

};

void Maze::next_relation(int &p, int &q) {
    p = rand() % size;
    q = rand() % size;
};

void Maze::print() {
    // for(int i = 0; )
}