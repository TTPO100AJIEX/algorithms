g++ algorithms/implementations/kmp-optimized.cpp algorithms/index.cpp -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++20 -Werror -Wsign-compare -o bin/index.exe
./bin/index.exe text.txt pattern.txt