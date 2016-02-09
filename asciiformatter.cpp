//
// Created by erik on 2/8/16.
//

#include "formatter.h"

string AsciiFormatter::format(const Maze &maze) const {

    string format = "" + h_wall;

    for (int i = 0; i < maze.get_height(); i++) {

        string top = "", mid = "";

        for (int j = 0; j < maze.get_width(); j++) {

            int p = i * maze.get_width() + j,
                    top_left = (i - 1) * maze.get_width() + (j - 1);

            bool t = i > 0 && maze.is_open((i - 1) * maze.get_width() + j, false),
            //r = j != maze.get_width() - 1 && maze.is_open(p, 1),
            //b = i != maze.get_height() - 1 && maze.is_open(p, 2),
                    l = (i == 0 && j == 0) || j > 0 && maze.is_open(p - 1, true);

            char status(0);

            if (i == 0 || maze.is_open(top_left, true))
                status += 1;


            if (i != 0 && maze.is_open(top_left, false))
                status += 2;

            if (t)
                status += 4;

            if (l || (i == 0 && j == 0))
                status += 8;

            if (status == 0)
                top += cross;
            else if (status == 1)
                top += h_wall_bottom;
            else if (status == 2)
                top += v_wall_right;
            else if (status == 3)
                top += tl_corner;
            else if (status == 4)
                top += v_wall_left;
            else if (status == 5)
                top += tr_corner;
            else if (status == 6)
                top += v_wall;
            else if (status == 7)// asdasd
                top += v_wall;
            else if (status == 8)
                top += h_wall_top;
            else if (status == 9)
                top += h_wall;
            else if (status == 10)
                top += bl_corner;
            else if (status == 11)
                top += h_wall;
            else if (status == 12)
                top += br_corner;
            else if (status == 13)
                top += h_wall;
            else if (status == 14)
                top += v_wall;
            else {
                top += '.';
            }

            if (t)
                top += ' ';
            else
                top += h_wall;

            if (l)
                mid += ' ';
            else
                mid += v_wall;

            mid += ' ';

            if (j == maze.get_width() - 1) {
                if (i == 0)
                    top += tr_corner;
                else if (t)
                    top += v_wall;
                else
                    top += v_wall_left;

                if (i != maze.get_height() - 1)
                    mid += v_wall;
            }

        }

//        cout << top.c_str() << mid.c_str() << endl;

        format += top;
        format += '\n';
        format += mid;
        format += '\n';

    }

    // bottom line
    format += bl_corner;

    for (int i = (maze.get_height() - 1) * maze.get_width(); i < maze.get_size(); i++) {
        format += h_wall;
        if (i == maze.get_size() - 1 || maze.is_open(i, true))
            format += h_wall;
        else
            format += h_wall_top;
    }

    return format;

};