set -x
index_file="BaAA/week11/d/index.cpp"

g++ $index_file -DDEBUG -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -Werror -Wsign-compare -o solution.exe
./solution.exe
rm solution.exe