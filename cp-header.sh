#!/bin/sh

for HEADER in `find src/ -name "*.h"|cut -d/ -s -f2-10`;
	do
	mkdir -p debian/libinge-dev/usr/include/InGE/${HEADER};
	rm -rf debian/libinge-dev/usr/include/InGE/${HEADER};
	cp src/${HEADER} debian/libinge-dev/usr/include/InGE/${HEADER};
done
