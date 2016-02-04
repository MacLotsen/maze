//
// Created by Erik on 2/4/2016.
//

#ifndef DISJOINT_SET_DISJOINT_H
#define DISJOINT_SET_DISJOINT_H

#endif //DISJOINT_SET_DISJOINT_H

class Tree {

public:
    Tree(int size);

    int find_root(int p);
    void joint(int p, int q);
    int size_of(int p);
    void print();

private:
    int length;
    int* N;

};