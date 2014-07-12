#! /usr/bin/env bash

# Copyright (c) 2014 Damian Jason Lapidge
#
# The contents of this file are subject to the terms and conditions defined 
# within the file LICENSE.txt, located within this project's root directory.

CC="cc"; # c compiler command

SRC="greyio.c wiresting.c";
OUT="../bin/wiresting";

# compiler & linker flags
CFLAGS="";
IFLAGS="";
LFLAGS="";

LIBS="-lpcap";

# create output directory
mkdir -p ../bin;

if [ "$(which $CC)" == "" ];
then
    echo "error: failure to locate C compiler ($CC)" 1>&2;
    exit 1; # exit failure
fi

# compile/link source code
$CC $CFLAGS -o $OUT $SRC $IFLAGS $LFLAGS $LIBS;

