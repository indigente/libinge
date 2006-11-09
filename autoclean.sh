#!/bin/sh

[ -e Makefile ] && make clean

rm -rf autom4te.cache/ aclocal.m4 auto config.guess config.h config.sub configure config.log ltmain.sh config.h.in config.status libtool stamp-h src/inge.pc

for each in Makefile Makefile.in .deps '*.loT'; do
  find . -name $each -exec rm -rf '{}' ';'
done
