#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Specify the search path for dynamic link libraries
export LD_LIBRARY_PATH="$DIR/../lib:$LD_LIBRARY_PATH"


$DIR/../bin/main 