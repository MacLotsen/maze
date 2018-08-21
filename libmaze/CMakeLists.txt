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

set(MAZE_HEADERS maze.h disjoint-sets.h)

add_library(maze ${MAZE_HEADERS} maze.c disjoint-sets.c)

add_executable(test_disjointsets test-disjoint-sets.c)
target_link_libraries(test_disjointsets maze)
add_test(disjointsets-test test_disjointsets)

install(FILES ${MAZE_HEADERS}
        DESTINATION include)

install(TARGETS maze
        DESTINATION lib)
