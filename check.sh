#!/bin/bash

cppcheck --enable=all --suppress=missingInclude src test
