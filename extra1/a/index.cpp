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

public:
    RootDecomposition(Operation operation, int mod, std::istream& instream);
    
    void insert(unsigned int index, int value);
    void erase(unsigned int index);
    void change(unsigned int index, int value);
    int at(unsigned int index);
    int compute(unsigned int left, unsigned int right);
    unsigned int size();
    void print();
};

RootDecomposition::RootDecomposition(Operation operation, int mod, std::istream& instream) : operation(operation), mod(mod)
{
    unsigned int size; std::cin >> size;
    this->parts.resize(sqrt(size) + 1, { 0, this->data.end() });
    std::list<int>::iterator last_element = this->data.begin();
    for (unsigned int i = 0; i < size; i++)
    {
        int number; instream >> number;
        this->data.push_back(number);
        if (i == 0) last_element = this->data.begin();
        else last_element++;
        if (i % this->parts.size() == 0) this->parts[i / this->parts.size()] = { 0, last_element };
        if (this->operation == Operation::SUM) this->parts[i / this->parts.size()].first = (this->parts[i / this->parts.size()].first + number) % this->mod;
        if (this->operation == Operation::XOR) this->parts[i / this->parts.size()].first ^= number;
    }
}

void RootDecomposition::insert(unsigned int index, int value)
{
    unsigned int part = index / this->parts.size(); index %= this->parts.size();
    std::list<int>::iterator it = this->parts[part].second;
    bool on_split_point = false;
    if (index == 0) on_split_point = true;
    while ((index--) != 0) it++;
    it = this->data.insert(it, value);

    unsigned int new_part_size = sqrt(this->data.size()) + 1;
    if (new_part_size != this->parts.size())
    {
        //full rebuild in O(n)
        this->parts.resize(new_part_size);
        for (unsigned int i = 0; i < this->parts.size(); i++) this->parts[i] = { 0, this->data.end() };
        std::list<int>::iterator last_element = this->data.begin();
        for (unsigned int i = 0; i < this->data.size(); i++, last_element++)
        {
            if (i % this->parts.size() == 0) this->parts[i / this->parts.size()] = { 0, last_element };
            if (this->operation == Operation::SUM) this->parts[i / this->parts.size()].first = (this->parts[i / this->parts.size()].first + (*last_element)) % this->mod;
            if (this->operation == Operation::XOR) this->parts[i / this->parts.size()].first ^= (*last_element);
        }
        return;
    }
    else
    {
        //fix in O(sqrt(n))
        for ( ; part < this->parts.size(); part++)
        {
            // insert into part
            if (on_split_point) this->parts[part].second = it;
            if (this->operation == Operation::SUM) this->parts[part].first = (this->parts[part].first + (*it)) % this->mod;
            if (this->operation == Operation::XOR) this->parts[part].first ^= (*it);
            /*
                4: [ 1 2 3 ] [ 4 - - ] [ - - - ] -> stop
                5: [ 1 2 3 ] [ 4 5 - ] [ - - - ] -> stop
                6: [ 1 2 3 ] [ 4 5 6 ] [ - - - ] 
                7: [ 1 2 3 ] [ 4 5 6 ] [ 7 - - ] -> stop
            */
            if (part + 1 >= this->parts.size()) break; // case 7
            if (this->parts[part + 1].second == this->data.end() && this->data.size() % this->parts.size() != 1) break; // case 4-5

            it = this->parts[part + 1].second; it--;
            if (this->operation == Operation::SUM) this->parts[part].first = (this->parts[part].first - (*it)) % this->mod;
            if (this->operation == Operation::XOR) this->parts[part].first ^= (*it);
            on_split_point = true;
        }
    }
}
void RootDecomposition::erase(unsigned int index)
{
    unsigned int part = index / this->parts.size(); index %= this->parts.size();
    std::list<int>::iterator it = this->parts[part].second;
    while ((index--) != 0) it++;

    unsigned int new_part_size = sqrt(this->data.size()) + 1;
    if (new_part_size != this->parts.size())
    {
        this->data.erase(it);
        //full rebuild in O(n)
        this->parts.resize(new_part_size);
        for (unsigned int i = 0; i < this->parts.size(); i++) this->parts[i] = { 0, this->data.end() };
        std::list<int>::iterator last_element = this->data.begin();
        for (unsigned int i = 0; i < this->data.size(); i++, last_element++)
        {
            if (i % this->parts.size() == 0) this->parts[i / this->parts.size()] = { 0, last_element };
            if (this->operation == Operation::SUM) this->parts[i / this->parts.size()].first = (this->parts[i / this->parts.size()].first + (*last_element)) % this->mod;
            if (this->operation == Operation::XOR) this->parts[i / this->parts.size()].first ^= (*last_element);
        }
        return;
    }
    else
    {
        //fix in O(sqrt(n))
        std::list<int>::iterator save = it;
        for ( ; part < this->parts.size(); part++)
        {
            if (it == this->parts[part].second) this->parts[part].second++;
            if (this->operation == Operation::SUM) this->parts[part].first = (this->parts[part].first - (*it)) % this->mod;
            if (this->operation == Operation::XOR) this->parts[part].first ^= (*it);
            /*
                5: [ 1 2 3 ] [ 4 5 - ] [ - - - ]
                6: [ 1 2 3 ] [ 4 5 6 ] [ - - - ] 
                7: [ 1 2 3 ] [ 4 5 6 ] [ 7 - - ]
                8: [ 1 2 3 ] [ 4 5 6 ] [ 7 8 - ]
            */
            if (part + 1 >= this->parts.size()) break; // case 6-7
            if (this->parts[part + 1].second == this->data.end()) break; // case 5-6

            it = this->parts[part + 1].second;
            if (this->operation == Operation::SUM) this->parts[part].first = (this->parts[part].first + (*it)) % this->mod;
            if (this->operation == Operation::XOR) this->parts[part].first ^= (*it);
        }
        this->data.erase(save);
    }
}
void RootDecomposition::change(unsigned int index, int value)
{
    unsigned int part = index / this->parts.size(); index %= this->parts.size();
    std::list<int>::iterator it = this->parts[part].second;
    while ((index--) != 0) it++;
    if (this->operation == Operation::SUM)
    {
        this->parts[part].first = (this->parts[part].first - *it) % this->mod;
        this->parts[part].first = (this->parts[part].first + value) % this->mod;
    }
    if (this->operation == Operation::XOR)
    {
        this->parts[part].first ^= *it;
        this->parts[part].first ^= value;
    }
    *it = value;
}
int RootDecomposition::at(unsigned int index)
{
    unsigned int part = index / this->parts.size(); index %= this->parts.size();
    std::list<int>::iterator it = this->parts[part].second;
    while ((index--) != 0) it++;
    return(*it);
}
int RootDecomposition::compute(unsigned int left, unsigned int right)
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
unsigned int RootDecomposition::size() { return this->data.size(); }
void RootDecomposition::print()
{
    std::cout << "------------------------------------\n";
    for (std::list<int>::iterator it = this->data.begin(); it != this->data.end(); it++) std::cout << *it << " ";
    std::cout << "\n";
    for (std::vector< std::pair<int, std::list<int>::iterator> >::iterator it = this->parts.begin(); it != this->parts.end(); it++)
    {
        if (it->second != this->data.end()) std::cout << it->first << "|" << *(it->second) << " ";
        else std::cout << it->first << "|end ";
    }
    std::cout << "------------------------------------\n";
}

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
        
        if (command == "print") { solver.print(); }
    }

    return 0;
}