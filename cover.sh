#!/bin/bash

#!/bin/bash
#
# <Program name and brief descritpion.>
# Copyright (C) 2020 Guybrush aka Gabriele Labita
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
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# file      cover.sh<liboptparse>
# brief     This script is used to perform code coverage.
# copyright GNU Public License.
# author    Gabriele Labita
#           <gabriele.labita@linux.it>
#
# This script is used to perform code coverage using lcov when
# unit test are run

CURRENT=$(dirname ".")
CURRENT=$(readlink -f $CURRENT)

DIR=$(dirname "$0")
DIR=$(readlink -f $DIR)

cd $DIR

COVERDIR="$DIR/cover"

if [ ! -d "$DIR/cover" ]; then
    mkdir $DIR/cover
    cd $COVERDIR
    ../configure
else
    cd $COVERDIR
fi
cd $DIR/cover
make clean
make CXXFLAGS='-g -O0 --coverage' check
if [ -d "$COVERDIR/site" ]; then
   rm -rf site
fi
mkdir site
COVER_INFO_FILE=liboptparse.info
lcov --directory . --capture --output-file $COVER_INFO_FILE
# This line remove the std coverage from info file.
lcov --remove $COVER_INFO_FILE "/usr/*" -o $COVER_INFO_FILE
genhtml $COVER_INFO_FILE -o ./site
