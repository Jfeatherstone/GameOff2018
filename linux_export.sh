#!/bin/sh

# First recompile the source to make sure it is the most up to date version
g++ -std=c++17 -o Main src/*.cpp -lsfml-system -lsfml-window -lsfml-graphics -lstdc++fs

# Next up we should zip up the resources and executable
zip -r Export/$"Linux$1.zip" fonts graphics levels Main
