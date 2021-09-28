#!/usr/bin/bash
MAKEFILE_DIR=./../..

cp $MAKEFILE_DIR/Makefile .
make $1 $2 SRCSDIR=srcs HDRSDIR=hdrs EXTRA_LFLAGS="-lsfml-graphics -lsfml-window -lsfml-system" CENTRAL_MAKEFILE_DIR="$MAKEFILE_DIR"
rm -f Makefile