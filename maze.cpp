//
// Created by Erik on 2/4/2016.
//

#include <assert.h>
#include "maze.h"

Maze::Maze(int width, int height) : tree(width * height ) {
    size = width * height;
    matrix = new pair<int,int>[size];
    this->width = width;
    this->height = height;

    int i (0);

    srand (time(NULL));

    while (tree.size() > 1) {

        if (i >= size)
            throw new exception();

        int p, q, pr, qr;

        next_relation(p, q);

        // TODO validation

        pr = tree.find_root(p);
        qr = tree.find_root(q);

        if (pr != qr) {
            tree.joint(pr, qr);
            pair<int, int> R (p, q);
            matrix[i] = R;
            cout << "new set" << endl << "p: " << p << endl << "q: " << q << endl;
        }

    }

//    pair<int, int> pair (p, q);
//    matrix.insert(pair);

    //matrix[p] = q;

    //assert(matrix[p] == q);

};

void Maze::next_relation(int &p, int &q) {
    p = rand() % size;
    q = rand() % size;
};

void Maze::print() {
    // for(int i = 0; )
}