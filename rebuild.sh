CURRENT=$(dirname ".")
CURRENT=$(readlink -f $CURRENT)

DIR=$(dirname "$0")
DIR=$(readlink -f $DIR)

if [ ! -d "$DIR/build" ]; then
    mkdir build
fi
BUILDDIR="$DIR/build"

if [ -f "$BUILDDIR/Makefile" ]; then
    cd $BUILDDIR
    make clean
fi

cd $DIR

cd $BUILDDIR
../configure
make all

cd $CURRENT
