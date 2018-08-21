#
# A simple maze generator written in just C.
# Copyright (C) 2018  Erik Nijenhuis
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

project(maze)

find_package(Curses)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(draw_maze ${MAZE_HEADERS} maze-renderer.h main.c simple-renderer.c box-drawing-renderer.c)
target_link_libraries(draw_maze maze ${CURSES_LIBRARIES})

install(TARGETS draw_maze
        DESTINATION bin)
