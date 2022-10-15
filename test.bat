set index_file=week4\c\index.cpp

g++ %index_file% -std=c++17 -O2 -o solution.exe
start /b /w solution.exe
del solution.exe
PAUSE