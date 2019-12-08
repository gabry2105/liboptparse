LibOptparse
===========

A c++ library use to parse CLI arguments

# Installation
TODO

# Usage
TODO


# Test
TODO


# Static analysis

Whole project is written according to the set of rules defined, and
verfied, by cppcheck static analysisi tool:
http://cppcheck.sourceforge.net/

You can install it through the official web site or, if you are using
a debian based systen, with the command

```
> sudo apt install cppcheck
```

To run checks you can use the check.sh script inside project or run it
through the command:

```
> cppcheck --enable=all src test
```
