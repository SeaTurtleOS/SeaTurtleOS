#!/bin/bash

BLUE="\033[0;36m"
GREEN="\033[0;32m"
RESET="\033[0m"

./clean.sh
./headers.sh
./iso.sh
./qemu.sh