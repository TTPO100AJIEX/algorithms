#include <iostream>
#include <cmath>
#include <utility>
#include <list>
#include <vector>

class RootDecomposition
{
public:
    enum Operation { SUM, XOR };

private:
    Operation operation;
    int mod;
    std::list<int> data;
    std::vector< std::pair<int, std::list<int>::iterator> > parts;

    void full_build();

public:
    RootDecomposition(Operation operation, int mod, std::istream& instream);
    
    void insert(unsigned int index, int value);
    void erase(unsigned int index);
    void change(unsigned int index, int value);
    
    int at(unsigned int index) const;
    int compute(unsigned int left, unsigned int right) const;
    unsigned int size() const;
};

RootDecomposition::RootDecomposition(Operation operation, int mod, std::istream& instream) : operation(operation), mod(mod)
{
    unsigned int size; std::cin >> size; int number;
    for (unsigned int i = 0; i < size; i++) { instream >> number; this->data.push_back(number); }
    this->full_build();
}
void RootDecomposition::full_build()
{
    unsigned int data_size = this->data.size(), parts_size = sqrt(data_size) + 1;
    this->parts.resize(parts_size); this->parts[parts_size - 1] = { 0, this->data.end() };
    std::list<int>::iterator current = this->data.begin();
    for (unsigned int i = 0, part = -1; i < data_size; i++, current++)
    {
        if (i % parts_size == 0) this->parts[++part] = { *current, current };
        else
        {
            std::pair<int, std::list<int>::iterator>& part_obj = this->parts[part];
            if (this->operation == Operation::SUM) part_obj.first = (part_obj.first + *current) % this->mod;
            else part_obj.first ^= *current;
        }
    }
}

void RootDecomposition::insert(unsigned int index, int value)
{
    unsigned int data_size = this->data.size(), parts_size = this->parts.size();
    unsigned int part = index / parts_size; index %= parts_size;
    bool on_split_point = (index == 0);
    std::list<int>::iterator inserted = this->parts[part].second;
    while ((index--) != 0) inserted++;
    inserted = this->data.insert(inserted, value);
    //if (parts_size * parts_size <= ++data_size) { full_build(); return; } //TODO <= to <
    unsigned int new_part_size = sqrt(data_size + 1) + 1;
    if (new_part_size != parts_size) { full_build(); return; }

    for ( ; part < parts_size; part++)
    {
        std::pair<int, std::list<int>::iterator>& part_obj = this->parts[part];
        if (on_split_point) part_obj.second = inserted;
        if (this->operation == Operation::SUM) part_obj.first = (part_obj.first + *inserted) % this->mod;
        else part_obj.first ^= *inserted;

        if (part + 1 >= parts_size || (this->parts[part + 1].second == this->data.end() && data_size % parts_size != 1)) break;
        inserted = this->parts[part + 1].second; inserted--;
        if (this->operation == Operation::SUM) part_obj.first = (part_obj.first - *inserted) % this->mod;
        if (this->operation == Operation::XOR) part_obj.first ^= *inserted;
        on_split_point = true;
    }
}
void RootDecomposition::erase(unsigned int index)
{
    unsigned int data_size = this->data.size(), parts_size = this->parts.size();
    unsigned int part = index / parts_size; index %= parts_size;
    std::list<int>::iterator removed = this->parts[part].second;
    while ((index--) != 0) removed++;
    //if ((parts_size - 1) * (parts_size - 1) > --data_size) { full_build(); return; } //TODO > to >=
    unsigned int new_part_size = sqrt(data_size - 1) + 1;
    if (new_part_size != parts_size) { full_build(); return; }

    std::list<int>::iterator to_erase = removed;
    for ( ; part < parts_size; part++)
    {
        std::pair<int, std::list<int>::iterator>& part_obj = this->parts[part];
        if (removed == part_obj.second) part_obj.second++;
        if (this->operation == Operation::SUM) part_obj.first = (part_obj.first - *removed) % this->mod;
        else part_obj.first ^= *removed;

        if (part + 1 >= parts_size || this->parts[part + 1].second == this->data.end()) break;
        removed = this->parts[part + 1].second;
        if (this->operation == Operation::SUM) part_obj.first = (part_obj.first + *removed) % this->mod;
        else part_obj.first ^= *removed;
    }
    this->data.erase(to_erase);
}
void RootDecomposition::change(unsigned int index, int value)
{
    unsigned int parts_size = this->parts.size(), part = index / parts_size; index %= parts_size;
    std::list<int>::iterator current = this->parts[part].second;
    while ((index--) != 0) current++;

    if (this->operation == Operation::SUM)
    {
        this->parts[part].first = (this->parts[part].first - *current) % this->mod;
        this->parts[part].first = (this->parts[part].first + value) % this->mod;
    }
    else this->parts[part].first ^= *current ^ value;
    *current = value;
}

int RootDecomposition::at(unsigned int index) const
{
    unsigned int part = index / this->parts.size(); index %= this->parts.size();
    std::list<int>::iterator it = this->parts[part].second;
    while ((index--) != 0) it++;
    return(*it);
}
int RootDecomposition::compute(unsigned int left, unsigned int right) const
{
    unsigned int left_part = left / this->parts.size(); left %= this->parts.size();
    std::list<int>::iterator left_it = this->parts[left_part].second;
    while ((left--) != 0) left_it++;
    unsigned int right_part = right / this->parts.size(); right %= this->parts.size();
    std::list<int>::iterator right_it = this->parts[right_part].second;
    while ((right--) != 0) right_it++;
    right_it++;
    
    if (left_part == right_part)
    {
        int answer = 0;
        while (left_it != right_it)
        {
            if (this->operation == Operation::SUM) answer = (answer + *(left_it++)) % this->mod;
            if (this->operation == Operation::XOR) answer ^= *(left_it++);
        }
        if (this->operation == Operation::SUM && answer < 0) answer += this->mod;
        return answer;
    }
    else
    {
        int answer = 0;
        while (left_it != this->parts[left_part].second)
        {
            if (this->operation == Operation::SUM) answer = (answer - *(--left_it)) % this->mod;
            if (this->operation == Operation::XOR) answer ^= *(--left_it);
        }
        while (left_part != right_part)
        {
            if (this->operation == Operation::SUM) answer = (answer + this->parts[left_part++].first) % this->mod;
            if (this->operation == Operation::XOR) answer ^= this->parts[left_part++].first;
        }
        while (right_it != this->parts[right_part].second)
        {
            if (this->operation == Operation::SUM) answer = (answer + *(--right_it)) % this->mod;
            if (this->operation == Operation::XOR) answer ^= *(--right_it);
        }
        if (this->operation == Operation::SUM && answer < 0) answer += this->mod;
        return answer;
    }
}
unsigned int RootDecomposition::size() const { return this->data.size(); }

int main(void)
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    char op; std::cin >> op;
    int mod = 1; if (op == '+') std::cin >> mod;
    RootDecomposition solver(op == '+' ? RootDecomposition::Operation::SUM : RootDecomposition::Operation::XOR, mod, std::cin);

    unsigned int queries; std::cin >> queries;
    std::string command; unsigned int i, l, r; int x;
    for (unsigned int query = 0; query < queries; query++)
    {
        std::cin >> command;
        if (command == "insert") { std::cin >> i >> x; solver.insert(i - 1, x); }
        if (command == "erase") { std::cin >> i; solver.erase(i - 1); }
        if (command == "change") { std::cin >> i >> x; solver.change(i - 1, x); }
        if (command == "at") { std::cin >> i; std::cout << solver.at(i - 1) << "\n"; }
        if (command == "compute") { std::cin >> l >> r; std::cout << solver.compute(l - 1, r - 1) << "\n"; }
        if (command == "size") { std::cout << solver.size() << "\n"; }
    }

    return 0;
}