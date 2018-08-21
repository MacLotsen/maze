# The Maze Project
A simple maze generator written in just C.

```
┌──────────────────┐┌───┐┌────────┐
│ █                ││   ││        │
│   ┌─────┐   ┌┐   ││   ││   ┌┐   │
│   │┌────┘   ││   ││   ││   ││   │
│   ││        ││   ││   ││   ││   │
│   │└────────┘│   ││   ││   ││   │
│   └─────────┐│   └┘   ││   ││   │
│             ││        ││ ▒ ││   │
│   ┌─────────┘│   ┌────┘└───┘│   │
│   └─────────┐│   │┌───┐┌───┐│   │
│             ││   ││   ││   ││   │
│   ┌─────────┘└───┘│   ││   ││   │
│   │┌────────┐┌───┐│   ││   └┘   │
│   ││        ││   ││   ││        │
│   ││   ┌────┘│   ││   │└────┐   │
│   └┘   └────┐│   ││   │┌───┐│   │
│             ││   ││   ││   ││   │
│   ┌┐   ┌────┘│   ││   ││   ││   │
│   ││   └─────┘   └┘   └┘   └┘   │
│   ││                            │
└───┘└────────────────────────────┘



```

## Getting Started
Use the following procedure to get and build the maze generator.
 * Download the source: `curl -L https://github.com/MacLotsen/maze/archive/master.zip --output maze.zip`
 * Unzip the archive: `unzip maze.zip`
 * Go into archive: `cd maze-master`
 * Create build folder: `mkdir build; cd build`
 * Build the binary and/or library: `cmake ..; make`
 * Run the maze: `maze/draw_maze -i -w 15 -h 7`

If you're only interested in using the library for development, make sure to take a look at `maze.h`.

### Prerequisites
For building the project the following dependencies are required.
 * GCC
 * CMake

For the binary `draw_maze` you need the following dependencies.
 * NCurses
 
No dependencies are required for `libmaze`.

### Installing
If you have already built the project you can just use `make install`.

## License
This project is licensed under the GPLv3 License -- See License.txt.
