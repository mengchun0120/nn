#!/bin/bash

folders="bin test/unit/bin test/tools/bin test/integration/bin"

for folder in $folders; do
    if [ -d $folder ]; then
        continue
    fi

    if [ -f $folder ]; then
        rm -f $folder
    fi

    mkdir $folder
done
