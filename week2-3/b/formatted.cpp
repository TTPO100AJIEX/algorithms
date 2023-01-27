#include <ios>
#include <iostream>
#include <vector>
#include <utility>

class Heap {
private:
    std::vector<int> data_;

    void bubbleUp(unsigned int index) {
        if (index == 0) {
            return;
        }
        const unsigned int parent = (index - 1) >> 1;
        if (this->data_[parent] > this->data_[index]) {
            std::swap(this->data_[parent], this->data_[index]);
            this->bubbleUp(parent);
        }
    }
    void bubbleDown(unsigned int index) {
        const unsigned int size = this->data_.size(), left_index = (index << 1) + 1,
                           right_index = (index << 1) + 2;
        unsigned int swap_with = size;
        if (left_index<size&& this->data_[index]> this->data_[left_index]) {
            swap_with = left_index;
        }
        if (right_index<size&& this->data_[index]> this->data_[right_index] &&
            this->data_[left_index] > this->data_[right_index]) {
            swap_with = right_index;
        }
        if (swap_with == size) {
            return;
        }
        std::swap(this->data_[swap_with], this->data_[index]);
        this->bubbleDown(swap_with);
    }

public:
    bool empty() const {
        return this->data_.empty();
    }

    void insert(const int value) {
        this->data_.push_back(value);
        this->bubbleUp(this->data_.size() - 1);
    }
    int extract() {
        int answer = this->data_[0];
        this->data_[0] = this->data_[this->data_.size() - 1];
        this->data_.pop_back();
        this->bubbleDown(0);
        return answer;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Heap sorter;
    unsigned int n;
    std::cin >> n;
    for (unsigned int i = 0; i < n; i++) {
        int value;
        std::cin >> value;
        sorter.insert(value);
    }
    while (!sorter.empty()) {
        std::cout << sorter.extract() << " ";
    }
}