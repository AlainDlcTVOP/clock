#!/bin/bash
gcc -lstdc++ ./test/clock.cpp ./lib/terminal/terminal.cpp -I./test -I ./include -lunity -o clock

if [ $? -eq 0 ]
then
    ./clock
    rm clock
else
    echo "Compilation failed!"
fi
