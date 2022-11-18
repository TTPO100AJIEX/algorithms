set -x
index_file="week6/b/index.cpp"

g++ $index_file -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -O2 -Wall -Werror -Wsign-compare -o solution.exe
./solution.exe
rm solution.exe