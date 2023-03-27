#include <ios>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>

constexpr unsigned int kSymbolsSize = 'z' - 'a' + 1;

struct Node {
    char symbol = 0;
    unsigned int weight;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(char symbol, unsigned int weight) : symbol(symbol), weight(weight) {
    }
    Node(unsigned int weight, std::unique_ptr<Node>& left, std::unique_ptr<Node>& right)
        : weight(weight), left(std::move(left)), right(std::move(right)) {
    }

    void buildCodes(std::vector<std::string>& storage, std::string cur = "") {
        if (this->symbol == 0) {
            this->left->buildCodes(storage, cur + "1");
            this->right->buildCodes(storage, cur + "0");
        } else {
            if (cur.empty()) {
                cur = "1";
            }
            storage[this->symbol - 'a'] = cur;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string data;
    std::cin >> data;

    unsigned int counter[kSymbolsSize];
    for (unsigned int i = 0; i < kSymbolsSize; ++i) {
        counter[i] = 0;
    }
    for (char symbol : data) {
        ++counter[symbol - 'a'];
    }

    unsigned int k = 0;
    std::vector<std::unique_ptr<Node> > nodes;
    for (unsigned int i = 0; i < kSymbolsSize; ++i) {
        if (counter[i] != 0) {
            nodes.push_back(std::make_unique<Node>(i + 'a', counter[i]));
            ++k;
        }
    }

    while (nodes.size() != 1) {
        std::sort(nodes.begin(), nodes.end(),
                  [](const std::unique_ptr<Node>& first, const std::unique_ptr<Node>& second) {
                      return first->weight > second->weight;
                  });
        std::unique_ptr<Node> first = std::move(*(nodes.rbegin()));
        nodes.pop_back();
        std::unique_ptr<Node> second = std::move(*(nodes.rbegin()));
        nodes.pop_back();
        nodes.push_back(std::make_unique<Node>(first->weight + second->weight, first, second));
    }

    std::vector<std::string> codes(kSymbolsSize, "");
    nodes[0]->buildCodes(codes);
    std::string encoded;
    for (unsigned int i = 0; i < data.size(); ++i) {
        encoded += codes[data[i] - 'a'];
    }

    std::cout << k << ' ' << encoded.size() << '\n';
    for (unsigned int i = 0; i < kSymbolsSize; ++i) {
        if (!codes[i].empty()) {
            std::cout << static_cast<char>('a' + i) << ": " << codes[i] << '\n';
        }
    }
    std::cout << encoded << "\n\n";
}