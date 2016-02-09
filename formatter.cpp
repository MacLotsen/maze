//
// Created by erik on 2/6/16.
//

#include <tuple>
#include "formatter.h"

string ConsoleFormatter::format(const Maze &maze) const {

    string format = ".";

    for (int i = 0; i < maze.get_width(); i++) format += "_.";
    format += '\n';

    for (int i = 0; i < maze.get_height(); i++) {

        // the opening
        if (i == 0)
            format += '.';
        else
            format += '|';

        for (int j = 0; j < maze.get_width(); j++) {

            int p = (i * maze.get_width()) + j;

            // bottom is open?
            if(maze.is_open(p, false))
                format += ' ';
            else
                format += '_';

            // end or right is open?
            if(p == maze.get_size() - 1 || maze.is_open(p, true))
                format += '.';
            else
                format += '|';

        }

        format += '\n';

    }

    return format;
}