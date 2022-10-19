#include <iostream>
#include <cmath>
#include <utility>
#include <list>
#include <vector>

class RootDecomposition {
public:
    enum Operation { SUM, XOR };

private:
    Operation operation_;
    int mod_;
    std::list<int> data_;
    std::vector<std::pair<int, std::list<int>::iterator> > parts_;

    void fullBuild();

public:
    RootDecomposition(Operation operation, int mod, std::istream& instream);

    void insert(unsigned int index, int value);
    void erase(unsigned int index);
    void change(unsigned int index, int value);

    int at(unsigned int index) const;
    int compute(unsigned int left, unsigned int right) const;
    unsigned int size() const;
};

RootDecomposition::RootDecomposition(Operation operation, int mod, std::istream& instream)
    : operation_(operation), mod_(mod) {
    unsigned int size;
    std::cin >> size;
    int number;
    for (unsigned int i = 0; i < size; i++) {
        instream >> number;
        this->data_.push_back(number);
    }
    this->fullBuild();
}
void RootDecomposition::fullBuild() {
    unsigned int data_size = this->data_.size(), parts_size = sqrt(data_size) + 1;
    this->parts_.resize(parts_size);
    this->parts_[parts_size - 1] = {0, this->data_.end()};
    std::list<int>::iterator current = this->data_.begin();
    for (unsigned int i = 0, part = -1; i < data_size; i++, current++) {
        if (i % parts_size == 0) {
            this->parts_[++part] = {*current, current};
        } else {
            std::pair<int, std::list<int>::iterator>& part_obj = this->parts_[part];
            if (this->operation_ == Operation::SUM) {
                part_obj.first = (part_obj.first + *current) % this->mod_;
            } else {
                part_obj.first ^= *current;
            }
        }
    }
}

void RootDecomposition::insert(unsigned int index, int value) {
    unsigned int data_size = this->data_.size(), parts_size = this->parts_.size();
    unsigned int part = index / parts_size;
    index %= parts_size;
    bool on_split_point = (index == 0);
    std::list<int>::iterator inserted = this->parts_[part].second;
    while ((index--) != 0) {
        inserted++;
    }
    inserted = this->data_.insert(inserted, value);
    // if (parts_size * parts_size <= ++data_size) { full_build(); return; } //TODO <= to <
    unsigned int new_part_size = sqrt(data_size + 1) + 1;
    if (new_part_size != parts_size) {
        fullBuild();
        return;
    }

    for (; part < parts_size; part++) {
        std::pair<int, std::list<int>::iterator>& part_obj = this->parts_[part];
        if (on_split_point) {
            part_obj.second = inserted;
        }
        if (this->operation_ == Operation::SUM) {
            part_obj.first = (part_obj.first + *inserted) % this->mod_;
        } else {
            part_obj.first ^= *inserted;
        }

        if (part + 1 >= parts_size ||
            (this->parts_[part + 1].second == this->data_.end() && data_size % parts_size != 1)) {
            break;
        }
        inserted = this->parts_[part + 1].second;
        inserted--;
        if (this->operation_ == Operation::SUM) {
            part_obj.first = (part_obj.first - *inserted) % this->mod_;
        }
        if (this->operation_ == Operation::XOR) {
            part_obj.first ^= *inserted;
        }
        on_split_point = true;
    }
}
void RootDecomposition::erase(unsigned int index) {
    unsigned int data_size = this->data_.size(), parts_size = this->parts_.size();
    unsigned int part = index / parts_size;
    index %= parts_size;
    std::list<int>::iterator removed = this->parts_[part].second;
    while ((index--) != 0) {
        removed++;
    }
    // if ((parts_size - 1) * (parts_size - 1) > --data_size) { full_build(); return; } //TODO > to
    // >=
    unsigned int new_part_size = sqrt(data_size - 1) + 1;
    if (new_part_size != parts_size) {
        fullBuild();
        return;
    }

    std::list<int>::iterator to_erase = removed;
    for (; part < parts_size; part++) {
        std::pair<int, std::list<int>::iterator>& part_obj = this->parts_[part];
        if (removed == part_obj.second) {
            part_obj.second++;
        }
        if (this->operation_ == Operation::SUM) {
            part_obj.first = (part_obj.first - *removed) % this->mod_;
        } else {
            part_obj.first ^= *removed;
        }

        if (part + 1 >= parts_size || this->parts_[part + 1].second == this->data_.end()) {
            break;
        }
        removed = this->parts_[part + 1].second;
        if (this->operation_ == Operation::SUM) {
            part_obj.first = (part_obj.first + *removed) % this->mod_;
        } else {
            part_obj.first ^= *removed;
        }
    }
    this->data_.erase(to_erase);
}
void RootDecomposition::change(unsigned int index, int value) {
    unsigned int parts_size = this->parts_.size(), part = index / parts_size;
    index %= parts_size;
    std::list<int>::iterator current = this->parts_[part].second;
    while ((index--) != 0) {
        current++;
    }

    if (this->operation_ == Operation::SUM) {
        this->parts_[part].first = (this->parts_[part].first - *current) % this->mod_;
        this->parts_[part].first = (this->parts_[part].first + value) % this->mod_;
    } else {
        this->parts_[part].first ^= *current ^ value;
    }
    *current = value;
}

int RootDecomposition::at(unsigned int index) const {
    unsigned int part = index / this->parts_.size();
    index %= this->parts_.size();
    std::list<int>::iterator it = this->parts_[part].second;
    while ((index--) != 0) {
        it++;
    }
    return (*it);
}
int RootDecomposition::compute(unsigned int left, unsigned int right) const {
    unsigned int left_part = left / this->parts_.size();
    left %= this->parts_.size();
    std::list<int>::iterator left_it = this->parts_[left_part].second;
    while ((left--) != 0) {
        left_it++;
    }
    unsigned int right_part = right / this->parts_.size();
    right %= this->parts_.size();
    std::list<int>::iterator right_it = this->parts_[right_part].second;
    while ((right--) != 0) {
        right_it++;
    }
    right_it++;

    if (left_part == right_part) {
        int answer = 0;
        while (left_it != right_it) {
            if (this->operation_ == Operation::SUM) {
                answer = (answer + *(left_it++)) % this->mod_;
            }
            if (this->operation_ == Operation::XOR) {
                answer ^= *(left_it++);
            }
        }
        if (this->operation_ == Operation::SUM && answer < 0) {
            answer += this->mod_;
        }
        return answer;
    } else {
        int answer = 0;
        while (left_it != this->parts_[left_part].second) {
            if (this->operation_ == Operation::SUM) {
                answer = (answer - *(--left_it)) % this->mod_;
            }
            if (this->operation_ == Operation::XOR) {
                answer ^= *(--left_it);
            }
        }
        while (left_part != right_part) {
            if (this->operation_ == Operation::SUM) {
                answer = (answer + this->parts_[left_part++].first) % this->mod_;
            }
            if (this->operation_ == Operation::XOR) {
                answer ^= this->parts_[left_part++].first;
            }
        }
        while (right_it != this->parts_[right_part].second) {
            if (this->operation_ == Operation::SUM) {
                answer = (answer + *(--right_it)) % this->mod_;
            }
            if (this->operation_ == Operation::XOR) {
                answer ^= *(--right_it);
            }
        }
        if (this->operation_ == Operation::SUM && answer < 0) {
            answer += this->mod_;
        }
        return answer;
    }
}
unsigned int RootDecomposition::size() const {
    return this->data_.size();
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char op;
    std::cin >> op;
    int mod = 1;
    if (op == '+') {
        std::cin >> mod;
    }
    RootDecomposition solver(
        op == '+' ? RootDecomposition::Operation::SUM : RootDecomposition::Operation::XOR, mod,
        std::cin);

    unsigned int queries;
    std::cin >> queries;
    std::string command;
    unsigned int i, l, r;
    int x;
    for (unsigned int query = 0; query < queries; query++) {
        std::cin >> command;
        if (command == "insert") {
            std::cin >> i >> x;
            solver.insert(i - 1, x);
        }
        if (command == "erase") {
            std::cin >> i;
            solver.erase(i - 1);
        }
        if (command == "change") {
            std::cin >> i >> x;
            solver.change(i - 1, x);
        }
        if (command == "at") {
            std::cin >> i;
            std::cout << solver.at(i - 1) << "\n";
        }
        if (command == "compute") {
            std::cin >> l >> r;
            std::cout << solver.compute(l - 1, r - 1) << "\n";
        }
        if (command == "size") {
            std::cout << solver.size() << "\n";
        }
    }

    return 0;
}