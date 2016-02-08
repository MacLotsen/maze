#include <iostream>
#include <fstream>
#include "test.h"
#include "formatter.h"

using namespace std;

int main() {

    test_disjoint();

    Maze maze(50, 20);

    MazeFormatter *formatter = new ConsoleFormatter();

    cout << formatter->format(maze);

    delete formatter;

    // NOT IMPLEMENTED YET
    /*


    ofstream out ("new.txt", ofstream::binary);

    formatter = new AsciiFormatter();

    string o = formatter->format(maze);

    // cout << o;

    const char* buffer = o.c_str();

    out.write(buffer, o.length());

    delete[] buffer;

    out.close();

     //*/

    return 0;
}
