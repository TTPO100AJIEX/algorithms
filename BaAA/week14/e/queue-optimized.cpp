#include <ios>
#include <iostream>
#include <cstdint>
#include <climits>
#include <set>
#include <vector>
#include <utility>
#include <functional>

class PriorityQueue
{
private:
    using Comparator = std::function<bool(uint16_t, uint16_t)>;
    Comparator comparator;
    std::vector<uint16_t> storage;
    std::vector<uint16_t> index;

    void swap(uint16_t first, uint16_t second)
    {
        std::swap(this->index[this->storage[first]], this->index[this->storage[second]]);
        std::swap(this->storage[first], this->storage[second]);
    }
    
    void siftUp(uint16_t index)
    {
        if (index == 0) return;
        const uint16_t parent = (index - 1) >> 1;
        if (this->comparator(this->storage[index], this->storage[parent]))
        {
            this->swap(index, parent);
            this->siftUp(parent);
        }
    }

    void siftDown(uint16_t index)
    {
        const uint16_t left = (index << 1) + 1, right = (index << 1) + 2;
        if (left >= this->storage.size()) return;
        uint16_t to_swap = this->storage.size();
        if (right < this->storage.size())
        {
            // both children exist
            if (this->comparator(this->storage[left], this->storage[index]) || this->comparator(this->storage[right], this->storage[index]))
                to_swap = this->comparator(this->storage[left], this->storage[right]) ? left : right;
        }
        else
        {
            // only left exists
            if (this->comparator(this->storage[left], this->storage[index])) to_swap = left;
        }
        if (to_swap != this->storage.size())
        {
            this->swap(index, to_swap);
            this->siftDown(to_swap);
        }
    }

public:
    PriorityQueue(uint16_t maxKey, Comparator comparator) : comparator(comparator) { this->index.resize(maxKey, UINT16_MAX); }

    void insert(uint16_t item)
    {
        if (this->index[item] == UINT16_MAX)
        {
            this->index[item] = this->storage.size();
            this->storage.push_back(item);
        }
        this->siftUp(this->index[item]);
    }

    uint16_t extract()
    {
        uint16_t to_return = this->storage[0];
        this->index[to_return] = UINT16_MAX;
        this->storage[0] = this->storage[this->storage.size() - 1];
        this->index[this->storage[0]] = 0;
        this->storage.pop_back();
        this->siftDown(0);
        return to_return;
    }

    bool empty() { return this->storage.empty(); }
};

unsigned int getSumDigits(uint16_t number)
{
    unsigned int answer = 0;
    while (number > 0)
    {
        answer += (number % 10);
        number /= 10;
    }
    return answer;
}

void printPath(const std::vector<uint16_t>& parents, uint16_t vertex, uint16_t dist = 0)
{
    if (parents[vertex] == 0) { std::cout << dist << '\n'; return; }
    printPath(parents, parents[vertex], dist + 1);
    int16_t operation = vertex - parents[vertex];
    if (operation > 0) std::cout << '+';
    std::cout << operation << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t n, a, b;
    std::cin >> n >> a >> b;
    ++n;

    constexpr unsigned int INF = UINT_MAX;
    std::vector<uint16_t> parents(n, 0);
    std::vector<unsigned int> distances(n, INF);
    distances[a] = 0;

    PriorityQueue to_update(n, [&](uint16_t a, uint16_t b) { return distances[a] < distances[b]; });
    to_update.insert(a);
    while (!to_update.empty())
    {
        const uint16_t from = to_update.extract();
        const unsigned int current_distance = distances[from];
        if (from == b)
        {
            std::cout << current_distance << '\n';
            printPath(parents, b);
            return 0;
        }

        uint16_t prefix = from;
        while (prefix > 0)
        {
            uint16_t suffix = prefix;
            unsigned int power10 = 1;
            do
            {
                uint16_t y = suffix % (power10 *= 10);
                unsigned int attempt_distance = current_distance + getSumDigits(y);
                if (from + y < n && attempt_distance < distances[from + y])
                {
                    distances[from + y] = attempt_distance;
                    parents[from + y] = from;
                    to_update.insert(from + y);
                }
                if (from != y && attempt_distance < distances[from - y])
                {
                    distances[from - y] = attempt_distance;
                    parents[from - y] = from;
                    to_update.insert(from - y);
                }
            } while (suffix % power10 != prefix);
            prefix /= 10;
        }
    }

    std::cout << -1;
}