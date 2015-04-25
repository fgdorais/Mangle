#!/bin/sh

test -e NEWS || touch NEWS
test -e README || touch README
test -e AUTHORS || touch AUTHORS
test -e ChangeLog || touch ChangeLog

autoreconf --install || exit 1
