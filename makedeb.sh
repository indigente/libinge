#!/bin/sh

fakeroot debian/rules clean
debian/rules build
fakeroot debian/rules binary
