//
// Created by Erik on 2/4/2016.
//

#include <iostream>
#include <assert.h>
#include "disjoint.h"

using namespace std;

Tree::Tree(int size) {
    length = size;
    N = new int[size];
    for(int i = 0; i < length; i++)
        N[i] = -1;
};

int Tree::find_root(int p) {
    if(N[p] < 0)
        return p;
    else
        return N[p] = this->find_root(N[p]);
};

void Tree::joint(int p, int q) {
    assert(N[p] < 0 && N[q] < 0 && p != q);
    N[p] = N[p] + N[q];
    N[q] = p;
    print();
};

int Tree::size() {
    int s (0);
    for(int i = 0; i < length; i++)
        if(N[i] < 0)
            s++;
    return s;
};

int Tree::size_of(int p) {
    return N[p] * -1;
};

void Tree::print() {
    for(int i = 0; i < length; i++)
        cout << N[i] << ' ';
    cout << endl;
};