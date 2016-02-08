//
// Created by erik on 2/8/16.
//

#include "formatter.h"

string AsciiFormatter::format(const Maze &maze) const {

    string format = "" + h_wall;


    //tuple<int, int, int, int> *h_buffer = new tuple<int, int, int, int>[maze.get_width()];

    for (int i = 0; i < maze.get_height(); i++) {

        string top, mid;

        for (int j = 0; j < maze.get_width(); j++) {

            int p = i * maze.get_width() + j;

            bool t, r, b, l;

            // beginning
            if (i == 0 && j == 0) {
                //prev_l = true;
                //prev_t = false;
            } else if (i == 0) {
                //prev_t = false;
            } else if (j == 0) {
                //prev_l = false;
            }



            // bottom is open?
            if(maze.is_open(p, p + maze.get_width()))
                top += ' ';
            else
                top += h_wall;

            // end or right is open?
            if(p == maze.get_size() - 1 || maze.is_open(p, p + 1))
                top += cross;
            else
                mid += v_wall;

            // is added


        }

        format += top;
        format += '\n';
        format += mid;
        format += '\n';

    }

    return format;

};