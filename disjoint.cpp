//
// Created by Erik on 2/4/2016.
//

#include <assert.h>
#include "disjoint.h"

DisjointSets::DisjointSets(int size) {
    length = size;
    N = new int[length];
    for(int i = 0; i < length; i++)
        N[i] = -1;
};

int DisjointSets::find_root(int p) const {
    if(N[p] < 0)
        return p;
    else
        return N[p] = this->find_root(N[p]);
};

void DisjointSets::joint(int p, int q) {
    assert(N[p] < 0 && N[q] < 0 && p != q);
    N[p] = N[p] + N[q];
    N[q] = p;
};

int DisjointSets::size() const {
    int s (0);
    for(int i = 0; i < length; i++)
        if(N[i] < 0)
            s++;
    return s;
};

int DisjointSets::size_of(int p) const {
    assert(N[p] < 0);
    return N[p] * -1;
};

DisjointSets::~DisjointSets() {
    delete this->N;
}
