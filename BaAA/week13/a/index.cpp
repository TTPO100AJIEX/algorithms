#include <ios>
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

class Vertex
{
public:
    static constexpr unsigned int NONE = UINT_MAX;
    static std::vector<Vertex> vertexes;

public:
    unsigned int index;
    unsigned int next_vertex = Vertex::NONE;

private:
    unsigned int component_start = Vertex::NONE;
    unsigned int component_end = Vertex::NONE;

    unsigned int getComponentStart()
    {
        if (this->isStart()) return this->index;
        return (this->component_start = Vertex::vertexes[this->component_start].getComponentStart());
    }
    unsigned int getComponentEnd()
    {
        if (this->isEnd()) return this->index;
        return (this->component_end = Vertex::vertexes[this->component_end].getComponentEnd());
    }

public:
    Vertex(unsigned int index) : index(index) { }

    void addEdge(unsigned int vertex)
    {
        Vertex& from = Vertex::vertexes[this->getComponentEnd()];
        Vertex& to = Vertex::vertexes[Vertex::vertexes[vertex].getComponentStart()];
        from.next_vertex = to.index;
        from.component_end = to.index;
        to.component_start = from.index;
    }

    bool isStart() const { return this->component_start == Vertex::NONE; }
    bool isEnd() const { return this->component_end == Vertex::NONE; }
};
std::vector<Vertex> Vertex::vertexes = std::vector<Vertex>();

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    Vertex::vertexes.reserve(n);
    for (unsigned int i = 0; i < n; ++i) Vertex::vertexes.emplace_back(i);
    
    for (unsigned int i = 1; i < n; ++i)
    {
        unsigned int first, second;
        std::cin >> first >> second;
        --first; --second;
        Vertex::vertexes[first].addEdge(second);
    }

    unsigned int current = std::find_if(Vertex::vertexes.begin(), Vertex::vertexes.end(), [](const Vertex& vertex) { return vertex.isStart(); })->index;
    while (current != Vertex::NONE)
    {
        std::cout << current + 1 << ' ';
        current = Vertex::vertexes[current].next_vertex;
    }
}