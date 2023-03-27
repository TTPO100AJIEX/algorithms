#include <ios>
#include <iostream>
#include <memory>
#include <string>

struct Trie {
    char letter = 0;
    std::unique_ptr<Trie> left = nullptr;
    std::unique_ptr<Trie> right = nullptr;

    void add(char letter) {
        char code;
        std::cin >> code;
        if (code == '\n') {
            this->letter = letter;
            return;
        }
        if (code == '1') {
            if (this->left == nullptr) {
                this->left = std::make_unique<Trie>();
            }
            this->left->add(letter);
        } else {
            if (this->right == nullptr) {
                this->right = std::make_unique<Trie>();
            }
            this->right->add(letter);
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int k, l;
    std::cin >> k >> l;

    std::unique_ptr<Trie> root = std::make_unique<Trie>();
    std::cin >> std::noskipws;
    std::cin.ignore(1);
    for (unsigned int i = 0; i < k; ++i) {
        char letter;
        std::cin >> letter;
        std::cin.ignore(2);
        root->add(letter);
    }

    std::cin >> std::skipws;
    std::string encoded;
    std::cin >> encoded;
    Trie* current = root.get();
    for (unsigned int i = 0; i < encoded.size(); ++i) {
        if (encoded[i] == '1') {
            current = current->left.get();
        } else {
            current = current->right.get();
        }

        if (current->letter != 0) {
            std::cout << current->letter;
            current = root.get();
        }
    }
}