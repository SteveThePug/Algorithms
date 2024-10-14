#!/bin/bash
BUILD_DIR=.build

gcc -g main.c list.c graph.c -o $BUILD_DIR/main.out

if [ $? -eq 0 ]; then
    echo "Compilation successful"
    gdb $BUILD_DIR/main.out
else
    echo "Compilation failed"
fi
