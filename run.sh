#!/bin/bash
BUILD_DIR=.build

gcc main.c graph.c -o $BUILD_DIR/main.out

if [ $? -eq 0 ]; then
	$BUILD_DIR/main.out "$@"
else
	echo "Compilation failed"
fi
