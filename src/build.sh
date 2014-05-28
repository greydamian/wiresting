#! /usr/bin/env bash

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

