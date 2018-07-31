//
// Created by erik on 23-7-18.
//
#include <stdlib.h>
#include <stdio.h>
#include "maze-renderer.h"

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


void box_drawing_renderer(maze_t *maze) {
//    setvbuf (stdout, NULL, _IONBF, 0);
    const wchar_t **chunk_map = (const wchar_t **) malloc(maze->size * sizeof(const wchar_t *));
    
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
    for (int i = 0; i < maze->height; i++) {
        for (int k = 0; k < 3; k++) {
            int offset = k * 3;
            for (int j = 0; j < maze->width; j++) {
                int index = i * maze->width + j;
                printf("%lc%lc%lc%lc%lc", chunk_map[index][offset], chunk_map[index][offset+1], chunk_map[index][offset+1], chunk_map[index][offset+1], chunk_map[index][offset+2]);
            }
            printf("\n");
        }
//        printf("\n");
    }
    fflush(stdout);
}
