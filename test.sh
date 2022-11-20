set -x
index_file="week6/b/index.cpp"

g++ $index_file -fno-sanitize-recover=all -std=c++17 -Wall -Werror -Wsign-compare -o solution.exe
./solution.exe
rm solution.exe