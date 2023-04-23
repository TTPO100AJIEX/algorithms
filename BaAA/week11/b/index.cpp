#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Person
{
    std::string name;
    std::vector<Person*> siblings;
    bool visited = false;
};

bool peopleComparator(const Person* first, const Person* second)
{
    return first->name < second->name;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m; std::cin >> n >> m;
    std::vector<Person> people(n);
    for (unsigned int i = 0; i < n; i++)
    {
        unsigned int index; std::cin >> index;
        std::cin.ignore(1);
        std::getline(std::cin, people[index].name);
    }
    for (unsigned int i = 0; i < m; i++)
    {
        unsigned int from, to;
        std::cin >> from >> to;
        people[from].siblings.push_back(&people[to]);
        people[to].siblings.push_back(&people[from]);
    }
    unsigned int number; std::cin >> number;
    std::vector<Person*> current, next;
    next.push_back(&people[number]);
    people[number].visited = true;
    while (!next.empty())
    {
        std::swap(current, next);
        next.clear();
        std::sort(current.begin(), current.end(), peopleComparator);
        for (Person* to_print : current)
        {
            std::cout << to_print->name << '\n';
            for (Person* sibling : to_print->siblings)
            {
                if (sibling->visited) continue;
                sibling->visited = true;
                next.push_back(sibling);
            }
        }
    }

    return 0;
}