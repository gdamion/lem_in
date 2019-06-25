#!/bin/bash

GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

for file in maps/$1/*
do
if [ -d "$file" ]
then
echo "$file is a directory"
elif [ -f "$file" ]
then
printf "\n${GREEN}Test the $file file:\n${CYAN}\n"
#valgrind --le./lem_in < $file 
time ./lem_in < $file
echo -e "${GREEN}"
read -p "Press enter to continue..."
clear
fi
done
