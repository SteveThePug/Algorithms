#!/bin/bash
BUILD_DIR=.build

gcc main.c graph.c -o $BUILD_DIR/main.out && $BUILD_DIR/main.out
