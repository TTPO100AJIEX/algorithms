set -x
index_file="week4/a/index.cpp"
solution_file="week4/a/index.cpp"
formatted_file="week4/a/formatted.cpp"

cp $solution_file solution_save.cpp

clang-format -i $solution_file
clang-tidy $solution_file -fix-errors --
g++ $index_file -fsanitize=address,undefined -fno-sanitize-recover=all -std=c++17 -O2 -Wall -Werror -Wsign-compare -o solution.exe

mv $solution_file $formatted_file
cp solution_save.cpp $solution_file
rm solution_save.cpp

./solution.exe
rm solution.exe