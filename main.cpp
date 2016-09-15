#include <iostream>
#include <fstream>
#include "test.h"
#include "formatter.h"

using namespace std;

int main() {
    test_disjoint();

    Maze maze(35, 15);

    MazeFormatter *formatter = new ConsoleFormatter();

    string m = formatter->format(maze);
    cout << m.c_str() << endl;

    delete formatter;

    // NOT IMPLEMENTED YET
    //*
    ofstream out("new.txt", ofstream::binary);

    formatter = new AsciiFormatter();

    string o = formatter->format(maze);

    cout << o;

    const char *buffer = o.c_str();

    out.write(buffer, o.length());

    out.close();

    cout << o.c_str();

    //*/

    return 0;
}
