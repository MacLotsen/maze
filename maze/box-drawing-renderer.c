/*
 * A simple maze generator written in just C.
 * Copyright (C) 2018  Erik Nijenhuis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include "maze-renderer.h"

/**
 * All chunks are Unicode characters which some terminals may not print right.
 * The problem is solved by using 'print_box_ch' function (last function in this file...).
 * If you happen to know to fit those ASC_<?> in such arrays, please send a pull request or create a ticket.
 */

/**
 * All closed
 */
static const wchar_t chunk0[] = {
        0x250c, 0x2500, 0x2510,
        0x2502, 0x0020, 0x2502,
        0x2514, 0x2500, 0x2518
};

/**
 * Top open
 */
static const wchar_t chunk1[] = {
        0x2502, 0x0020, 0x2502,
        0x2502, 0x0020, 0x2502,
        0x2514, 0x2500, 0x2518
};

/**
 * Right open
 */
static const wchar_t chunk2[] = {
        0x250c, 0x2500, 0x2500,
        0x2502, 0x0020, 0x0020,
        0x2514, 0x2500, 0x2500
};

/**
 * Top & right open
 */
static const wchar_t chunk3[] = {
        0x2502, 0x0020, 0x2514,
        0x2502, 0x0020, 0x0020,
        0x2514, 0x2500, 0x2500
};

/**
 * Bottom open
 */
static const wchar_t chunk4[] = {
        0x250c, 0x2500, 0x2510,
        0x2502, 0x0020, 0x2502,
        0x2502, 0x0020, 0x2502
};

/**
 * Top & bottom open
 */
static const wchar_t chunk5[] = {
        0x2502, 0x0020, 0x2502,
        0x2502, 0x0020, 0x2502,
        0x2502, 0x0020, 0x2502
};

/**
 * Right & bottom open
 */
static const wchar_t chunk6[] = {
        0x250c, 0x2500, 0x2500,
        0x2502, 0x0020, 0x0020,
        0x2502, 0x0020, 0x250c
};

/**
 * Top, right & bottom open
 */
static const wchar_t chunk7[] = {
        0x2502, 0x0020, 0x2514,
        0x2502, 0x0020, 0x0020,
        0x2502, 0x0020, 0x250c
};

/**
 * Left open
 */
static const wchar_t chunk8[] = {
        0x2500, 0x2500, 0x2510,
        0x0020, 0x0020, 0x2502,
        0x2500, 0x2500, 0x2518
};

/**
 * Top & left open
 */
static const wchar_t chunk9[] = {
        0x2518, 0x0020, 0x2502,
        0x0020, 0x0020, 0x2502,
        0x2500, 0x2500, 0x2518
};

/**
 * Right & left open
 */
static const wchar_t chunk10[] = {
        0x2500, 0x2500, 0x2500,
        0x0020, 0x0020, 0x0020,
        0x2500, 0x2500, 0x2500
};

/**
 * Top, right and left open
 */
static const wchar_t chunk11[] = {
        0x2518, 0x0020, 0x2514,
        0x0020, 0x0020, 0x0020,
        0x2500, 0x2500, 0x2500
};

/**
 * Bottom and left open
 */
static const wchar_t chunk12[] = {
        0x2500, 0x2500, 0x2510,
        0x0020, 0x0020, 0x2502,
        0x2510, 0x0020, 0x2502
};

/**
 * Top, bottom & left open
 */
static const wchar_t chunk13[] = {
        0x2518, 0x0020, 0x2502,
        0x0020, 0x0020, 0x2502,
        0x2510, 0x0020, 0x2502
};

/**
 * Right, bottom & left open
 */
static const wchar_t chunk14[] = {
        0x2500, 0x2500, 0x2500,
        0x0020, 0x0020, 0x0020,
        0x2510, 0x0020, 0x250c
};

/**
 * All open
 */
static const wchar_t chunk15[] = {
        0x2518, 0x0020, 0x2514,
        0x0020, 0x0020, 0x0020,
        0x2510, 0x0020, 0x250c
};


/**
 * Proxy printer
 *
 * Accepts a unicode character and prints the corresponding NCurses definition.
 * @param c
 */
static void print_box_ch(wchar_t c) {
    // This is a hot fix. It's ugly and doesn't belong here.
    // On the other hand, this program is just a simple maze printer.
    // Therefore all this logic will not be added to the maze library.
    switch(c) {
        case 0x250c:
            addch(ACS_ULCORNER); break;
        case 0x2500:
            addch(ACS_HLINE); break;
        case 0x2510:
            addch(ACS_URCORNER); break;
        case 0x2502:
            addch(ACS_VLINE); break;
        case 0x2514:
            addch(ACS_LLCORNER); break;
        case 0x2518:
            addch(ACS_LRCORNER); break;
        default:
            addch(0x0020);
    }
}


/**
 * Pretty print the maze with box drawing characters.
 * @param maze
 */
void box_drawing_renderer(maze_t *maze) {
    // A map of the maze tiles that will be mapped with the corresponding chunks
    const wchar_t **chunk_map = (const wchar_t **) malloc(maze->size * sizeof(const wchar_t *));

    // The mapping...
    for (int i = 0; i < maze->size; i++) {
        switch (maze->tiles[i]) {
            case 0:
                chunk_map[i] = chunk0;
                break;
            case 1:
                chunk_map[i] = chunk1;
                break;
            case 2:
                chunk_map[i] = chunk2;
                break;
            case 3:
                chunk_map[i] = chunk3;
                break;
            case 4:
                chunk_map[i] = chunk4;
                break;
            case 5:
                chunk_map[i] = chunk5;
                break;
            case 6:
                chunk_map[i] = chunk6;
                break;
            case 7:
                chunk_map[i] = chunk7;
                break;
            case 8:
                chunk_map[i] = chunk8;
                break;
            case 9:
                chunk_map[i] = chunk9;
                break;
            case 10:
                chunk_map[i] = chunk10;
                break;
            case 11:
                chunk_map[i] = chunk11;
                break;
            case 12:
                chunk_map[i] = chunk12;
                break;
            case 13:
                chunk_map[i] = chunk13;
                break;
            case 14:
                chunk_map[i] = chunk14;
                break;
            case 15:
                chunk_map[i] = chunk15;
                break;
        }
    }

    // Print that stuff
    for (int i = 0; i < maze->height; i++) {
        for (int k = 0; k < 3; k++) {
            int offset = k * 3;
            move(i*3+k,0);
            for (int j = 0; j < maze->width; j++) {
                int index = i * maze->width + j;

                // Notice the extra padding added in the width
                print_box_ch(chunk_map[index][offset]);
                print_box_ch(chunk_map[index][offset+1]);
                print_box_ch(chunk_map[index][offset+1]);
                print_box_ch(chunk_map[index][offset+1]);
                print_box_ch(chunk_map[index][offset+2]);
            }
        }
    }

    free(chunk_map);
}
