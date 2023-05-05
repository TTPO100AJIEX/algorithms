#include <ios>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Person {
    std::string name;
    std::vector<Person*> siblings;
    bool used = false;
    int index;
};
std::vector<Person*> order;

void dfs(Person* person) {
    if (person->used) {
        return;
    }
    person->used = true;
    for (Person* sibling : person->siblings) {
        dfs(sibling);
    }
    order.push_back(person);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;

    std::vector<Person*> people(n);
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int index;
        std::cin >> index;
        --index;
        people[index] = new Person();
        people[index]->index = index + 1;
        std::cin.ignore(1);
        std::getline(std::cin, people[index]->name);
    }

    std::vector<bool> is_src(n, true);
    for (unsigned int i = 0; i < m; ++i) {
        unsigned int from, to;
        std::cin >> from >> to;
        --from;
        --to;
        people[from]->siblings.push_back(people[to]);
        is_src[to] = false;
    }

    std::vector<Person*> srces;
    for (unsigned int i = 0; i < n; ++i) {
        if (is_src[i]) {
            srces.push_back(people[i]);
        }
    }

    for (unsigned int i = 0; i < n; ++i) {
        std::sort(
            people[i]->siblings.begin(), people[i]->siblings.end(),
            [](const Person* first, const Person* second) { return first->name < second->name; });
    }
    std::sort(srces.begin(), srces.end(),
              [](const Person* first, const Person* second) { return first->name < second->name; });

    order.reserve(n);
    for (Person* person : srces) {
        dfs(person);
    }

    for (unsigned int i = order.size(); i > 0; --i) {
        std::cout << order[i - 1]->name << '\n';
    }

    for (unsigned int i = 0; i < n; ++i) {
        delete people[i];
    }
}