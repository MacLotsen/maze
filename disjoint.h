//
// Created by Erik on 2/4/2016.
//

#ifndef DISJOINT_SET_DISJOINT_H
#define DISJOINT_SET_DISJOINT_H

class DisjointSets {

public:
    DisjointSets(int size);
    ~DisjointSets();

    int find_root(int p) const;
    void joint(int p, int q);
    int size() const;
    int size_of(int p) const;

private:
    int length;
    int* N;

};

#endif //DISJOINT_SET_DISJOINT_H
