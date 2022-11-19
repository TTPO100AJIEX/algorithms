#include <cstdlib>
#include <string>
#include <iostream>

struct Node
{
    friend class AVLTree;
private:
    Node* parent = nullptr;

    bool IsLeftSon() const { return this->parent ? (this->parent->left == this) : false; }
    bool IsRightSon() const { return this->parent ? (this->parent->right == this) : false; }
    
    void recalculate_height()
    {
        int left_height = (this->left ? this->left->height : 0), right_height = (this->right ? this->right->height : 0);
        this->height = 1 + (left_height > right_height ? left_height : right_height);
    }
    int Balance() const { return ((this->left ? this->left->height : 0) - (this->right ? this->right->height : 0)); }

public:
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    int value = 0;

    Node(int value) : value(value) { }
    Node(int value, Node* parent) : parent(parent), value(value) { }
    
};

class AVLTree
{
private:
    Node* root = nullptr;
    int size = 0;

    enum class Rotations { LEFT, RIGHT };
    Node* rotation(Node* root, Rotations type);
    void fix_balance(Node* root);

    int* find(Node* root, int value) const;
    int* lowerBound(Node* root, int value) const;
    void traverse_to_buffer(Node* root, int* buffer, int* filled_length) const;

public:
    AVLTree() = default;
    void destroy(Node* node)
    {
        if (!node) return;
        this->destroy(node->left);
        this->destroy(node->right);
        delete node;
    }
    ~AVLTree() { this->destroy(this->root); }

    void insert(int value);
    void erase(int value);

    Node* getRoot() const { return this->root; }
    int getHeight() const { return this->root ? this->root->height : 0; }
    int getSize() const { return this->size; }
    bool empty() const { return (!this->root); }

    int* find(int value) const { return this->find(this->root, value); }
    int* lowerBound(int value) const { return this->lowerBound(this->root, value); }
    int* traversal() const;



    void output() { this->output(this->root, ""); }
    void output(Node* root, std::string path)
    {
        if (!root) return;
        std::cout << root->value << " " << root->height << " " << (root->parent ? root->parent->value : -1) << " "
                    << (root->left ? root->left->value : -1) << " " << (root->right ? root->right->value : -1) << " " << path << std::endl;
        this->output(root->left, path + "l");
        this->output(root->right, path + "r");
    }
    void test()
    {
        this->root = new Node(1);

        this->root->right = new Node(2);
        this->root->right->parent = this->root;

        this->root->right->right = new Node(3);
        this->root->right->right->parent = this->root->right;
        
        this->root->left = new Node(4);
        this->root->left->parent = this->root;
        
        this->root->right->left = new Node(5);
        this->root->right->left->parent = this->root->right;
        
        this->root->right->right->left = new Node(6);
        this->root->right->right->left->parent = this->root->right->right;
        
        this->root->right->right->right = new Node(7);
        this->root->right->right->right->parent = this->root->right->right;

        this->root->right->right->right->recalculate_height();
        this->root->right->right->left->recalculate_height();
        this->root->right->right->recalculate_height();
        this->root->right->left->recalculate_height();
        this->root->right->recalculate_height();
        this->root->left->recalculate_height();
        this->root->recalculate_height();

        Node* new_root = new Node(0);
        new_root->right = this->root;
        this->root->parent = new_root;
        this->root = new_root;

        this->root->left = new Node(8);
        this->root->left->parent = this->root;

        this->root->left->recalculate_height();
        this->root->recalculate_height();

        this->output();
        std::cout << std::endl;


        this->fix_balance(this->root->right->right->right->right);


        this->output();
        std::cout << std::endl;
    }
};

Node* AVLTree::rotation(Node* current, AVLTree::Rotations type)
{
    //std::cout << (type == AVLTree::Rotations::RIGHT ? "RIGHT" : "LEFT") << std::endl;
    Node* pivot = nullptr;
    if (type == AVLTree::Rotations::RIGHT) pivot = current->left;
    else pivot = current->right;

    if (this->root == current) { this->root = pivot; pivot->parent = nullptr; }
    else
    {
        if (current->IsLeftSon()) current->parent->left = pivot;
        else current->parent->right = pivot;
        pivot->parent = current->parent;
    }

    if (type == AVLTree::Rotations::RIGHT)
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
    current->recalculate_height();
    pivot->recalculate_height();
    if (pivot->parent) pivot->parent->recalculate_height();
    return pivot;
}
void AVLTree::fix_balance(Node* current)
{
    if (!current) return;
    current->recalculate_height();
    if (current->Balance() > 1)
    {
        //std::cout << "left: " << current->value << std::endl;
        // too many vertexes on the left
        if (current->left->Balance() < 0) current->left = this->rotation(current->left, AVLTree::Rotations::LEFT);
        current = this->rotation(current, AVLTree::Rotations::RIGHT);
        this->fix_balance(current);
        return;
    }
    if (current->Balance() < -1)
    {
        //std::cout << "right: " << current->value << std::endl;
        // too many vertexes on the right
        if (current->right->Balance() > 0) current->right = this->rotation(current->right, AVLTree::Rotations::RIGHT);
        current = this->rotation(current, AVLTree::Rotations::LEFT);
        this->fix_balance(current);
        return;
    }
    this->fix_balance(current->parent);
}

void AVLTree::insert(int value)
{
    if (this->size == 0) { this->root = new Node(value); this->size = 1; return; }
    Node* current = this->root;
    while (value != current->value)
    {
        if (value < current->value)
        {
            if (!current->left) { current->left = new Node(value, current); this->size++; this->fix_balance(current); return; }
            current = current->left;
        }
        else
        {
            if (!current->right) { current->right = new Node(value, current); this->size++; this->fix_balance(current); return; }
            current = current->right;
        }
    }
}
void AVLTree::erase(int value)
{
    Node* current = this->root;
    while (current && value != current->value)
    {
        if (value < current->value) current = current->left;
        else current = current->right;
    }
    if (!current) return;
    this->size--;
    if (current->left && current->right)
    {
        Node* iop = current->left;
        while (iop->right) iop = iop->right;
        current->value = iop->value;
        current = iop;
    }
    
    Node* parent = nullptr;
    if (!current->left && !current->right)
    {
        parent = current->parent;
        if (!parent) { this->root = nullptr; this->size = 0; delete current; return; }
        if (current->IsLeftSon()) parent->left = nullptr;
        else parent->right = nullptr;
        delete current;
        this->fix_balance(parent);
        return;
    }
    if (current->left && !current->right)
    {
        parent = current->parent;
        if (!parent) { this->root = current->left; this->root->parent = nullptr; delete current; return; }
        if (current->IsLeftSon()) parent->left = current->left;
        else parent->right = current->left;
        current->left->parent = parent;
        delete current;
        this->fix_balance(parent);
        return;
    }
    if (!current->left && current->right)
    {
        parent = current->parent;
        if (!parent) { this->root = current->right; this->root->parent = nullptr; delete current; return; }
        if (current->IsLeftSon()) parent->left = current->right;
        else parent->right = current->right;
        current->right->parent = parent;
        delete current;
        this->fix_balance(parent);
        return;
    }
}

int* AVLTree::find(Node* current, int value) const
{
    // TODO: iterative
    if (!current) return nullptr;
    if (value < current->value) return this->find(current->left, value);
    if (value > current->value) return this->find(current->right, value);
    return &(current->value);
}
int* AVLTree::lowerBound(Node* current, int value) const
{
    // TODO: iterative
    int* data = this->traversal();
    for (int i = 0; i < this->size; ++i)
    {
        if (data[i] >= value) { int* ans = this->find(data[i]); free(data); return(ans); }
    }
    free(data);
    return nullptr;
    /*Node* answer = nullptr;
    while (root)
    {
        if (value == root->value) return &(root->value); 
        if (value < root->value) { answer = root; root = root->left; }
        else root = root->right;
    }
    if (!answer) return nullptr;
    return &(answer->value);*/
}
void AVLTree::traverse_to_buffer(Node* current, int* buffer, int* filled_length) const
{
    if (current == nullptr) return;
    this->traverse_to_buffer(current->left, buffer, filled_length);
    buffer[(*filled_length)++] = current->value;
    this->traverse_to_buffer(current->right, buffer, filled_length);
}
int* AVLTree::traversal() const
{
    int length = 0;
    int* data = static_cast<int*>(malloc(this->size * sizeof(int)));
    this->traverse_to_buffer(this->root, data, &length);
    return data;
}