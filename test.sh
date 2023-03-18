set -x
index_file="BaAA/week7/a/index.cpp"

g++ $index_file -fsanitize=address,undefined,leak -fno-sanitize-recover=all -std=c++17 -Werror -Wsign-compare -o solution.exe
./solution.exe
rm solution.exe