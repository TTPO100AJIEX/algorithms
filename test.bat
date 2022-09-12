set index_file=week1\4\index.cpp

g++ %index_file% -std=c++17 -o solution.exe
start /b /w solution.exe
del solution.exe
PAUSE