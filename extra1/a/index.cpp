#include <iostream>
#include <cmath>
#include <list>
#include <vector>

class RootDecomposition
{
public:
    enum Operation { SUM, XOR };

private:
    Operation operation;
    unsigned int mod;

    unsigned int data_size, part_size;
    std::list<int> data;
    std::vector< std::pair<int, std::list<int>::iterator> > parts;

public:
    RootDecomposition(Operation operation, unsigned int mod, std::istream& instream);
    
    void insert(unsigned int index, int x);
    void erase(unsigned int index);
    void change(unsigned int index, int x);
    int at(unsigned int index);
    int compute(unsigned int left, unsigned int right);
    unsigned int size();
};

RootDecomposition::RootDecomposition(Operation operation, unsigned int mod, std::istream& instream)
    : operation(operation), mod(mod)
{
    instream >> this->data_size;
    /*part_size = sqrt(this->data_size - 1) + 1;

    std::list<int>::iterator last_element = this->data.begin();
    this->parts.resize(part_size, { 0, last_element });

    for (unsigned int i = 0; i < this->data_size; i++)
    {
        int number; instream >> number;
        this->data.push_back(number);
        if (i == 0) last_element = this->data.begin();
        else last_element++;


        if (this->operation == Operation::SUM) this->parts[i / part_size].first = (this->parts[i / part_size].first + number) % this->mod;
        if (this->operation == Operation::XOR) this->parts[i / part_size].first ^= number;

        if (i % part_size == 0) this->parts[i / part_size].second = last_element;
    }*/
}

void RootDecomposition::insert(unsigned int index, int x)
{
    unsigned int part = index / this->part_size, ind = index % this->part_size;
    std::list<int>::iterator it = this->parts[part].second;
    for (unsigned int i = 1; i <= ind; i++) it++;
    this->data.insert(it, x);
    this->data_size++;

    part_size = sqrt(this->data_size - 1) + 1;
    std::list<int>::iterator last_element = this->data.begin();
    this->parts.resize(part_size, { 0, last_element });
    unsigned int i = 0;
    while (i < this->data_size)
    {
        this->parts[i / this->part_size].second = last_element;
        for (unsigned int j = 0; j < this->part_size; j++, i++)
        {
            if (i == this->data_size) break;
            if (this->operation == Operation::SUM) this->parts[i / part_size].first = (this->parts[i / part_size].first + *last_element) % this->mod;
            if (this->operation == Operation::XOR) this->parts[i / part_size].first ^= *last_element;
            last_element++;
        }
    }
}
void RootDecomposition::erase(unsigned int index)
{
    unsigned int part = index / this->part_size, ind = index % this->part_size;
    std::list<int>::iterator it = this->parts[part].second;
    for (unsigned int i = 1; i <= ind; i++) it++;
    this->data.erase(it);
    this->data_size--;

    part_size = sqrt(this->data_size - 1) + 1;
    std::list<int>::iterator last_element = this->data.begin();
    this->parts.resize(part_size, { 0, last_element });
    unsigned int i = 0;
    while (i < this->data_size)
    {
        this->parts[i / this->part_size].second = last_element;
        for (unsigned int j = 0; j < this->part_size; j++, i++)
        {
            if (i == this->data_size) break;
            if (this->operation == Operation::SUM) this->parts[i / part_size].first = (this->parts[i / part_size].first + *last_element) % this->mod;
            if (this->operation == Operation::XOR) this->parts[i / part_size].first ^= *last_element;
            last_element++;
        }
    }
}
void RootDecomposition::change(unsigned int index, int x)
{
    unsigned int part = index / this->part_size, ind = index % this->part_size;
    std::list<int>::iterator it = this->parts[part].second;
    for (unsigned int i = 1; i <= ind; i++) it++;
    
    if (this->operation == Operation::SUM)
    {
        this->parts[part].first -= *it;
        *it = x;
        this->parts[part].first += *it;
        this->parts[part].first %= this->mod;
        if (this->parts[part].first < 0) this->parts[part].first += this->mod;
    }
    else
    {
        this->parts[part].first ^= *it;
        *it = x;
        this->parts[part].first ^= *it;
    }
}
int RootDecomposition::at(unsigned int index)
{
    std::list<int>::iterator breakpoint = this->parts[index / this->part_size].second;
    index %= this->part_size;
    while (index != 0) { breakpoint++; index--; }
    return(*breakpoint);
}
int RootDecomposition::compute(unsigned int left, unsigned int right)
{
    unsigned int left_part = left / this->part_size, left_index = left % this->part_size;
    unsigned int right_part = right / this->part_size, right_index = right % this->part_size;

    std::list<int>::iterator left_it = this->parts[left_part].second;
    for (unsigned int i = 1; i <= left_index; i++) left_it++;
    std::list<int>::iterator right_it = this->parts[right_part].second;

    int answer = 0;
    if (left_part == right_part)
    {
        for (unsigned int i = left_index; i <= right_index; i++)
        {
            answer = (this->operation == RootDecomposition::Operation::SUM) ? ((answer + *left_it) % this->mod) : (answer ^ *left_it);
            left_it++;
        }
    }
    else
    {
        for (unsigned int i = left_part + 1; i < right_part; i++) { answer += this->parts[i].first; }
        while (left_index != this->part_size)
        {
            answer = (this->operation == RootDecomposition::Operation::SUM) ? ((answer + *left_it) % this->mod) : (answer ^ *left_it);
            left_it++; left_index++;
        }
        right_index++;
        do
        {
            answer = (this->operation == RootDecomposition::Operation::SUM) ? ((answer + *right_it) % this->mod) : (answer ^ *right_it);
            right_it++; right_index--;
        } while (right_index != 0);
    }
    if (this->operation == RootDecomposition::Operation::SUM && answer < 0) answer += this->mod;
    return answer;
}
unsigned int RootDecomposition::size() { return this->data_size; }

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char op; std::cin >> op;
    unsigned int mod = 1; if (op == '+') std::cin >> mod;
    RootDecomposition solver(op == '+' ? RootDecomposition::Operation::SUM : RootDecomposition::Operation::XOR, mod, std::cin);

    unsigned int queries; std::cin >> queries;
    unsigned int i, l, r; int x; 
    for (unsigned int query = 0; query < queries; query++)
    {
        std::string command; std::cin >> command;
        if (command == "insert") { std::cin >> i >> x; solver.insert(i - 1, x); }
        if (command == "erase") { std::cin >> i; solver.erase(i - 1); }
        if (command == "change") { std::cin >> i >> x; solver.change(i - 1, x); }
        if (command == "at") { std::cin >> i; std::cout << solver.at(i - 1) << "\n"; }
        if (command == "compute") { std::cin >> l >> r; std::cout << solver.compute(l - 1, r - 1) << "\n"; }
        if (command == "size") { std::cout << solver.size() << "\n"; }
    }

    return 0;
}