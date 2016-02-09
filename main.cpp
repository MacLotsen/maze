#include <iostream>
#include <fstream>
#include "test.h"
#include "formatter.h"

using namespace std;

int main() {
    test_disjoint();

    Maze maze(6, 7);

    MazeFormatter *formatter = new ConsoleFormatter();

	string m = formatter->format(maze);
    cout << m.c_str();

    delete formatter;

    // NOT IMPLEMENTED YET
    //*

    ofstream out ("new.txt", ofstream::binary);

    formatter = new AsciiFormatter();

    string o = formatter->format(maze);

    // cout << o;

    const char* buffer = o.c_str();

    out.write(buffer, o.length());

    //delete[] buffer;

    out.close();

	cout << o.c_str();

     //*/

	//cout << AsciiFormatter::tl_corner << AsciiFormatter::h_wall << AsciiFormatter::tr_corner << endl;
	//cout << AsciiFormatter::v_wall << ' ' << AsciiFormatter::v_wall << endl;
	//cout << AsciiFormatter::v_wall_left << ' ' << AsciiFormatter::v_wall_right;

	int c;

	cin >> c;

    return 0;
}
