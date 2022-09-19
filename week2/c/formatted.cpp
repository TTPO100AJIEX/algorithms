#include <iostream>
#include <vector>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> numbers(2 * n);
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
}
    for (int i = n; i < 2 * n; i++) {
        numbers[i] = numbers[i - n];
}

    std::vector<int> answers = {0};
    int max_ham_dist = 0;
    for (int i = 1; i < n; i++) {
        int ham_dist = 0;
        for (int j = 0; j < n; j++) {
            ham_dist += (numbers[i + j] != numbers[j]);
        }
        if (ham_dist > max_ham_dist) {
            answers.clear();
            max_ham_dist = ham_dist;
        }
        if (ham_dist == max_ham_dist) {
            answers.push_back(i);
        }
    }

    std::cout << max_ham_dist << "\n";
    for (unsigned int i = 0; i < answers.size(); i++) {
        std::cout << numbers[answers[i]];
        for (int j = 1; j < n; j++) {
            std::cout << " " << numbers[answers[i] + j];
}
        std::cout << "; " << answers[i] << "\n";
    }

    return 0;
}