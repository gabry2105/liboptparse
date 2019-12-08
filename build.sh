CURRENT=$(dirname ".")
CURRENT=$(readlink -f $CURRENT)

DIR=$(dirname "$0")
DIR=$(readlink -f $DIR)

cd $DIR

BUILDDIR="$DIR/build"

if [ ! -d "$DIR/build" ]; then
    mkdir build
    cd $BUILDDIR
    ../configure
fi
cd $BUILDDIR

make all

cd $CURRENT
