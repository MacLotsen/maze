//
// Created by erik on 2/6/16.
//

#ifndef DISJOINT_SET_PRINTER_H
#define DISJOINT_SET_PRINTER_H

#include <iostream>
#include "maze.h"

using namespace std;

class MazeFormatter {
public:
    virtual string format(const Maze&) const = 0;

};

class ConsoleFormatter : public MazeFormatter {
public:
    string format(const Maze&) const;

};

class AsciiFormatter : public MazeFormatter {
public:
    string format(const Maze&) const;
private:
    static const char v_wall = 179;
    static const char v_wall_left = 180;
    static const char tr_corner = 191;
    static const char bl_corner = 192;
    static const char h_wall_top = 193;
    static const char h_wall_bottom = 194;
    static const char v_wall_right = 195;
    static const char h_wall = 196;
    static const char cross = 197;
    static const char br_corner = 217;
    static const char tl_corner = 218;

};

#endif //DISJOINT_SET_PRINTER_H
