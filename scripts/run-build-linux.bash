#!/bin/bash

dir_script="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
dir_build="$dir_script"/../build/linux-release
dir_source="$dir_script"/../

rm -rf "$dir_build"
mkdir -p "$dir_build"
cd "$dir_build" || exit

cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" "$dir_source"
cmake --build . -- -j8

if [ -d "$dir_build"/test ]; then
	cd test && ctest
else
	echo 'INFO: test directory not found, skipping tests.'
fi

