#!/bin/bash

LIBS="https://github.com/dedeme/libdmc.git libdmc "

# Do not change --------------------------------------------

# Work from lib
# Variables: GIT, LIB
clone() {
  if [ -e tmp ]
  then
    rm -fR tmp
  fi
  mkdir tmp
  cd tmp
  git clone $GIT
  cp -R $LIB/include ../../../
  cp -R $LIB/src ../../../
}

if [ ! -e bin ]
then
  mkdir bin
fi

if [ ! -e lib ]
then
  mkdir lib
fi

cd lib

GIT=""
LIB=""
IX="0"
for GIT_LIB in $LIBS
do
  if [ $IX == "0" ]
  then
    GIT=$GIT_LIB
    IX="1"
  else
    LIB=$GIT_LIB
    clone
    IX="0"
  fi
done
