#include <initializer_list>
#include <utility>

enum class Color { RED, BLACK };
template <typename ValueType> class RBTree;

template <typename ValueType>
struct Node
{
    friend class RBTree<ValueType>;
private:
    bool isLeftChild() const { return (this->parent ? (this->parent->left == this) : false); }
    bool isRightChild() const { return (this->parent ? (this->parent->right == this) : false); }

    Node(const ValueType& value, Node<ValueType>* parent) : value(value), parent(parent) { };

public:
    ValueType value;
    Node<ValueType>* left = nullptr;
    Node<ValueType>* right = nullptr;
    Node<ValueType>* parent = nullptr;
    Color color = Color::RED;
    
    Node() = default;
    explicit Node(const ValueType& value) : value(value) { };
};


template <typename ValueType>
class RBTree
{
private:
    size_t length = 0;

    enum class Rotations { LEFT, RIGHT };
    void rotation(Node<ValueType>* root, Rotations type);
    void fix_balance(Node<ValueType>* current);

public:
    Node<ValueType>* root = nullptr;
    struct Iterator;

    RBTree() = default;
    RBTree(std::initializer_list<ValueType> list) { for (const ValueType& key : list) this->insert(key); } // O(nlog(n))
    RBTree(const RBTree<ValueType>& other); // O(n)
    RBTree<ValueType>& operator=(const RBTree<ValueType>& other); // O(n)

    void destroy(Node<ValueType>* node)
    {
        if (!node) return;
        this->destroy(node->left);
        this->destroy(node->right);
        delete node;
    }
    ~RBTree() { this->destroy(this->root); } // O(n)

    void insert(const ValueType& key); // O(log(n))
    void erase(const ValueType& value); // O(log(n))

    Iterator lowerBound(const ValueType& value) const; // O(log(n))
    Iterator find(const ValueType& value) const; // O(log(n))
    Iterator begin() const; // O(1)
    Iterator end() const; // O(1)

    size_t size() const { return(this->length); } // O(1)
    bool empty() const { return (!this->length); } // O(1)

    struct Iterator
    {
    private:
        Node<ValueType>* node = nullptr;

    public: 
        Iterator() = default;
        explicit Iterator(Node<ValueType>* node) : node(node) { }

        const ValueType& operator*() const { return *node; }
        const ValueType* operator->() const { return node;}

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        bool operator== (const Iterator& other) const { return this.node == other.node; }
        bool operator!= (const Iterator& other) const { return this.node != oter.node; }
    };

};


/*

template <typename T>
void RBTree<T>::rotation(Node<T>* current, RBTree<T>::Rotations type)
{
    Node<T>* pivot = nullptr;
    if (type == RBTree<T>::Rotations::RIGHT) pivot = current->left;
    else pivot = current->right;

    if (this->root == current) { this->root = pivot; pivot->parent = nullptr; }
    else
    {
        if (current->isLeftChild()) current->parent->left = pivot;
        else current->parent->right = pivot;
        pivot->parent = current->parent;
    }

    if (type == RBTree<T>::Rotations::RIGHT)
    {
        current->left = pivot->right;
        if (pivot->right) pivot->right->parent = current;
        pivot->right = current;
        current->parent = pivot;
    }
    else
    {
        current->right = pivot->left;
        if (pivot->left) pivot->left->parent = current;
        pivot->left = current;
        current->parent = pivot;
    }
}
template <typename T>
void RBTree<T>::fix_balance(Node<T>* current)
{
    if (this->root == current) { current->color = Color::BLACK; return; }
    if (!current || current->color == Color::BLACK || current->parent->color == Color::BLACK) return;
    Node<T>* parent = current->parent; // definitely exists, definitely red
    Node<T>* grandparent = parent->parent; // definitely exists because parent is red (thus, not root)
    Node<T>* uncle = parent->isLeftChild() ? grandparent->right : grandparent->left; // may not exist
    if (uncle && uncle->color == Color::RED)
    {
        // repaint
        grandparent->color = Color::RED;
        parent->color = Color::BLACK;
        if (uncle) uncle->color = Color::BLACK;
    }
    else
    {
        // repaint + rotation
        if (parent->isLeftChild())
        {
            if (current->isRightChild())
            {
                this->rotation(parent, RBTree<T>::Rotations::LEFT);
                std::swap(parent, current);
            }
            parent->color = Color::BLACK;
            grandparent->color = Color::RED;
            this->rotation(grandparent, RBTree<T>::Rotations::RIGHT);
        }
        else
        {
            if (current->isLeftChild())
            {
                this->rotation(parent, RBTree<T>::Rotations::RIGHT);
                std::swap(parent, current);
            }
            parent->color = Color::BLACK;
            grandparent->color = Color::RED;
            this->rotation(grandparent, RBTree<T>::Rotations::LEFT);
        }
    }
    this->fix_balance(parent);
    this->fix_balance(grandparent);
}

template <typename T>
void RBTree<T>::insert(const T&  key)
{
    if (this->length == 0) { this->root = new Node<T>(key); this->length++; this->fix_balance(this->root); return; }
    Node<T>* current = this->root;
    while (key != current->key)
    {
        if (key < current->key)
        {
            if (!current->left) { current->left = new Node<T>(key, current); this->length++; this->fix_balance(current->left); return; }
            current = current->left;
        }
        else
        {
            if (!current->right) { current->right = new Node<T>(key, current); this->length++; this->fix_balance(current->right); return; }
            current = current->right;
        }
    }
}

template <typename T>
T* RBTree<T>::find(const T& key) const
{
    Node<T>* current = this->root;
    while (current && key != current->key)
    {
        if (key < current->key) current = current->left;
        else current = current->right;
    }
    return (current ? &(current->key) : nullptr);
}
template <typename T>
T* RBTree<T>::lowerBound(const T& key) const
{
    Node<T>* answer = nullptr; Node<T>* current = this->root;
    while (current)
    {
        if (key == current->key) return &(current->key); 
        if (key < current->key) { answer = current; current = current->left; }
        else current = current->right;
    }
    return (answer ? &(answer->key) : nullptr);
}*/