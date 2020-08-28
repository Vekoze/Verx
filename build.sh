#!/bin/bash

OUT="build/verx"
CFLAGS="-Wall"
INCLUDES_PATH=(
"include/"
)
SRC_PATH=(
"src/"
"src/modules/"
"src/modules/wordlist/"
"src/utils/"
)

sources=""
includes=""

for i in "${INCLUDES_PATH[@]}"
do
	includes+=$i"*.h "
done 

for i in "${SRC_PATH[@]}"
do
	sources+=$i"*.cpp "
done 

echo g++ -o ${OUT} ${includes::-1} ${sources::-1} ${CFLAGS}
read -p "$*"