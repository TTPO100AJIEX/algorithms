#include <iostream>
#include <vector>

unsigned int ham_dist(int* array1, int* array2, unsigned int size)
{
    unsigned int answer = 0;
    for (unsigned int i = 0; i < size; i++, array1++, array2++) answer += (*array1 != *array2);
    return answer;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n; std::cin >> n;
    std::vector <int> numbers(n << 1);
    for (unsigned int i = 0; i < n; i++) std::cin >> numbers[i];
    for (unsigned int i = n; i < 2 * n; i++) numbers[i] = numbers[i - n];

    std::vector <int> answers = { 0 }; unsigned int max_ham_dist = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        unsigned int dist = ham_dist(&numbers[0], &numbers[n - i], n);
        if (dist > max_ham_dist) { answers.clear(); max_ham_dist = dist; }
        if (dist == max_ham_dist) answers.push_back(i);
    }
    
    std::cout << max_ham_dist << "\n";
    for (unsigned int i = 0; i < answers.size(); i++)
    {
        bool unique = true;
        for (unsigned int j = 0; j < i; j++)
        {
            if (ham_dist(&numbers[n - answers[i]], &numbers[n - answers[j]], n) == 0) { unique = false; break; }
        }
        if (!unique) continue;
        std::cout << numbers[n - answers[i]];
        for (unsigned int j = 1; j < n; j++) std::cout << " " << numbers[n - answers[i] + j];
        std::cout << "; " << answers[i] << "\n";
    }

    return 0;
}