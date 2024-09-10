#!/bin/bash

read -p "Enter the number of assignments: "  num_assignments
absolute_path=$(pwd)


echo "Absolute path: '$absolute_path' "

for(( i=1; i<=num_assignments ; i++ ))
do
    folder_name="$absolute_path/Prg${i}"
    if [ -d "$folder_name" ]; then
        echo "Folder '$folder_name' already exists , Skipping"
    else
        mkdir "$folder_name"
        touch "$folder_name/prg${i}_bt21cse028.c"
        echo "Folder '$folder_name' created"
    fi
done
