set -x
index_file="week6/d/index.cpp"

g++ $index_file -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -Wall -Werror -Wsign-compare -o solution.exe
./solution.exe
rm solution.exe