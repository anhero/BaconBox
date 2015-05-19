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

# We need to --rebuild all the calls since the current libbuildtool will
# think it has already built the targets since the built status is global
# and not by platform.

# First, build the simulator libraries
@ libbuildtool --rebuild -p IOS -- --sdk=iPhoneSimulator8.1 --arch=x86_64

# Then, for each device architectures
for arch in armv7 armv7s arm64; do
	@ libbuildtool --rebuild -p IOS -- --sdk=iPhoneOS8.1 --arch=$arch
done

# Then lipofy stuff
@ libbuildtool --rebuild -p IOS -- --arch=universal
