#!/bin/bash

BLUE="\033[0;36m"
RESET="\033[0m"

git add .
echo -e "${BLUE}Added all files${RESET}"
git commit -m "$1"
echo -e "${BLUE}Committed with message \"$1\"${RESET}"
git push -u origin main
echo -e "${BLUE}Completed push successfully${RESET}"
