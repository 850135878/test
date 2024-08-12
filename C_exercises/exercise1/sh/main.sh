#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ $# -eq 0 ]; then
    $DIR/../bin/main

elif [ $# -eq 1 ]; then
    IMG_DIR=$1
    $DIR/../bin/main $IMG_DIR
    
else
    echo "input arg error!"
fi