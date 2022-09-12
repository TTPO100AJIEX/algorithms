#include <deque>

class Deque
{
public:
    void pushBack(int value);
    void pushMiddle(int value);
 
    int popFront();

    int front() const;
    int back() const;
    size_t size() const;

private:
    std::deque <int> storage_;
};


void Deque::pushBack(int value)
{
    this->storage_.push_back(value);
}
void Deque::pushMiddle(int value)
{
    const int index = (this->storage_.size() + 1) / 2;
    this->storage_.insert(this->storage_.begin() + index, value);
}

int Deque::popFront()
{
    int item = this->storage_.front();
    this->storage_.pop_front();
    return (item);
}

int Deque::front() const
{
    return(this->storage_.front());
}
int Deque::back() const
{
    return(this->storage_.back());
}
size_t Deque::size() const
{
    return(this->storage_.size());
}