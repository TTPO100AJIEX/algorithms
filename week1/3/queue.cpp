#include <stack>

class Queue
{
public:
    void push(int value);
 
    int pop();

    int min() const;

private:
    struct Item
    {
        int value;
        int minBefore;

        Item(int Value, int MinBefore) : value(Value), minBefore(MinBefore) {};
    };

    void PushToStack(int value, int stackIndex);

    std::stack <Item> stack1;
    std::stack <Item> stack2;
};


void Queue::PushToStack(int value, int stackIndex)
{
    int currentMinimum = value;
    std::stack <Item>* stack = (stackIndex == 1) ? &(this->stack1) : &(this->stack2);
    if (!stack->empty()) currentMinimum = std::min(currentMinimum, stack->top().minBefore);
    stack->emplace(value, currentMinimum);
}
void Queue::push(int value)
{
    this->PushToStack(value, 1);
}

int Queue::pop()
{
    if (this->stack2.empty())
    {
        while (!this->stack1.empty())
        {
            int value = this->stack1.top().value;
            this->PushToStack(value, 2);
            this->stack1.pop();
        }
    }
    int returnValue = this->stack2.top().value;
    this->stack2.pop();
    return(returnValue);
}

int Queue::min() const
{
    if (this->stack1.empty()) return(this->stack2.top().minBefore);
    if (this->stack2.empty()) return(this->stack1.top().minBefore);
    return(std::min(this->stack1.top().minBefore, this->stack2.top().minBefore));
}