#!/bin/bash
gcc -lstdc++ ./test/clock.cpp ./test/canvas.cpp ./lib/terminal/terminal.cpp -I./lib/terminal -I./test -I ./include -lunity -o clock

if [ $? -eq 0 ]
then
    ./clock
    rm clock
else
    echo "Compilation failed!"
fi
