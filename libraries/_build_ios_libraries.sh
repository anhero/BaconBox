#!/bin/bash

set -e
set -u

@() {
	echo "> $*"
	"$@"
}

if [[  "${1-}" == "--delete" 
	|| "${1-}" == "--rebuild"
	|| "${1-}" == "-r"
	|| "${1-}" == "-d"
	]]; then
	@ rm -rf iOS;
fi

VERSION=8.3

# We need to --rebuild all the calls since the current libbuildtool will
# think it has already built the targets since the built status is global
# and not by platform.

# First, build the simulator libraries
for arch in i386 x86_64; do
	@ libbuildtool --rebuild -p IOS -- --sdk=iPhonesimulator${VERSION} --arch=$arch
done

# Then, for each device architectures
for arch in armv7 armv7s arm64; do
	@ libbuildtool --rebuild -p IOS -- --sdk=iPhoneOS${VERSION} --arch=$arch
done

# Then lipofy stuff
@ libbuildtool --rebuild -p IOS -- --arch=universal
