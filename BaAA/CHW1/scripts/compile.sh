g++ sort/index.cpp -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -Werror -Wsign-compare -DBINARY_INSERTION -DCOUNT_TIME -o solution.exe