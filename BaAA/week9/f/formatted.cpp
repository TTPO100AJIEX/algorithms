#include <ios>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector<std::string> patterns(n);
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> patterns[i];
    }

    std::string text;
    std::cin >> text;

    std::vector<unsigned int> substring_length(text.size(), 0);
    for (unsigned int i = 0; i < text.size(); ++i) {
        for (unsigned int j = 0; j < patterns.size(); ++j) {
            substring_length[i] = patterns[j].size();
            for (unsigned int x = 0; x < patterns[j].size(); ++x) {
                if (i + x >= text.size() || text[i + x] != patterns[j][x]) {
                    substring_length[i] = 0;
                    break;
                }
            }
            if (substring_length[i] != 0) {
                break;
            }
        }
    }

    unsigned int m;
    std::cin >> m;
    for (unsigned int i = 0; i < m; ++i) {
        unsigned int l, r;
        std::cin >> l >> r;
        --l;
        int answer = 0;
        while (l < r) {
            if (substring_length[l] == 0) {
                break;
            }
            l += substring_length[l];
            ++answer;
        }
        if (l != r) {
            answer = -1;
        }
        std::cout << answer << '\n';
    }

    unsigned int q;
    std::cin >> q;
    if (q != 0) {
        std::cout << 3;
    }
}