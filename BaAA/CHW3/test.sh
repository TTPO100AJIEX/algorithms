g++ algorithms/ford-bellman.cpp -O2 -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++20 -Werror -Wall -Wextra -o index.exe
# g++ algorithms/ford-bellman.cpp -O2 -std=c++20 -Werror -Wall -Wextra -o index.exe
./index.exe tests/full/1010.txt