#!/bin/bash

./test/optparse_test
result="$?"
if [ "$result" -ne 0 ]; then
    exit $result
else
    cd ./src
    lcov --directory . --capture --output-file liboptparse.info
    genhtml liboptparse.info
fi
