#include <iostream>
#include "test.h"
#include "maze.h"

using namespace std;

int main() {

    test_disjoint();

    Maze maze(3, 3);
    maze.print();
    return 0;
}
