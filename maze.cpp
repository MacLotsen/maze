//
// Created by Erik on 2/4/2016.
//

#include <iostream>
#include "maze.h"

Maze::Maze(int width, int height) : tree(width * height ) {
    size = width * height;
    matrix = new pair<int,int>[size];
    this->width = width;
    this->height = height;

    int i;

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
            matrix[i++] = R;
        }

    }

    matrix_size = i;

    // shrink array
    pair<int, int> tmp[matrix_size];
    for(int x = 0; x < matrix_size; x++) tmp[x] = matrix[x];

    delete matrix;

    matrix = tmp;

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
    for (int i = 0; i < matrix_size; i++) {
        pair<int, int> R = matrix[i];
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

    for (int i = 0; i < width; i++) {

        // the opening
        if (i == 0)
            cout << '.';
        else
            cout << '|';

        for (int j = 0; j < height; j++) {

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