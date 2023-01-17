set -x
index_file="week2-1/e/index.cpp"

g++ $index_file -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -Werror -Wsign-compare -o solution.exe
./solution.exe
rm solution.exe