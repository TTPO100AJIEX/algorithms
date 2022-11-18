struct Node
{
    int height;
    Node *left;
    Node *right;
    int value;
};

class AVLTree
{
public:
    AVLTree() = default;

    int getHeight() const;

    void insert(int value);

    void erase(int value);

    int *find(int value) const;

    int *traversal() const;

    int *lowerBound(int value) const;

    bool empty() const;

    Node *getRoot() const;

    int getSize() const;

    ~AVLTree();

private:
};