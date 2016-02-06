//
// Created by Erik on 2/4/2016.
//

#include <iostream>
#include "maze.h"

Maze::Maze(int width, int height) : DisjointSets(width * height ) {
    size = width * height;
    edge_count = size - 1;
    S = new pair<int,int>[edge_count];
    this->width = width;
    this->height = height;

    int i;

    srand (time(NULL));

    while (DisjointSets.size() > 1) {

        if (i >= size)
            throw new exception();

        int p, q, pr, qr;

        next_relation(p, q);

        pr = DisjointSets.find_root(p);
        qr = DisjointSets.find_root(q);

        if (pr != qr && !is_open(p, q)) {
            DisjointSets.joint(pr, qr);
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

bool Maze::is_open(int p, int q) {
    for (int i = 0; i < edge_count; i++) {
        pair<int, int> R = S[i];
        if ( (p == R.first && q == R.second)
                /* || (p == R.second && q == R.first) */ )
            return true;
    }
    return false;
};

void Maze::print() {
    // printing the top bar
    cout << '.';
    for (int i = 0; i < width; i++) cout << "_.";
    cout << endl;

    for (int i = 0; i < height; i++) {

        // the opening
        if (i == 0)
            cout << '.';
        else
            cout << '|';

        for (int j = 0; j < width; j++) {

            int p = (i * width) + j;

            // bottom is open?
            if(is_open(p, p + width))
                cout << ' ';
            else
                cout << '_';

            // end or right is open?
            if(p == size - 1 || is_open(p, p + 1))
                cout << '.';
            else
                cout << '|';

        }

        cout << endl;

    }

};