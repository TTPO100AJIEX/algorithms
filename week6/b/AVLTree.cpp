#include <cstdlib>

struct Node
{
    friend class AVLTree;
private:
    Node* parent = nullptr;

public:
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    int value = 0;

    Node() = default;
    Node(int value) : value(value) { };
    ~Node() { delete this->left; delete this->right; }
    
};

class AVLTree
{
private:
    Node* root = nullptr;
    int size = 0;

    Node* left_rotation(Node* root);
    Node* right_rotation(Node* root);
    Node* fix_balance(Node* root);
    
    void insert(Node* root, int value);
    void erase(Node* root, int value);

    int* find(Node* root, int value) const;
    int* lowerBound(Node* root, int value) const;
    void traverse_to_buffer(Node* root, int* buffer, int* filled_length) const;

public:
    AVLTree() = default;
    ~AVLTree() { delete this->root; }

    void insert(int value);
    void erase(int value);

    int* find(int value) const { return this->find(this->root, value); }
    int* lowerBound(int value) const { return this->lowerBound(this->root, value); }
    int* traversal() const;

    Node* getRoot() const { return this->root; }
    int getHeight() const { return this->root == nullptr ? 0 : this->root->height; }
    int getSize() const { return this->size; }
    bool empty() const { return this->root == nullptr; }
};

Node* AVLTree::left_rotation(Node* root)
{
    Node* pivot = root->right;
    Node* parent = root->parent;
    if (this->root == root) this->root = pivot;
    root->right = pivot->left;
    if (pivot->left) pivot->left->parent = root;
    pivot->left = root;
    root->parent = pivot;
    if (parent)
    {
        if (parent->left == root) parent->left = pivot;
        else parent->right = pivot;
        pivot->parent = parent;
    }
    return pivot;
    // TODO: height
}
Node* AVLTree::right_rotation(Node* root)
{
    Node* pivot = root->left;
    Node* parent = root->parent;
    if (this->root == root) this->root = pivot;
    root->left = pivot->right;
    if (pivot->right) pivot->right->parent = root;
    pivot->right = root;
    root->parent = pivot;
    if (parent)
    {
        if (parent->left == root) parent->left = pivot;
        else parent->right = pivot;
        pivot->parent = parent;
    }
    return pivot;
    // TODO: height
}
Node* AVLTree::fix_balance(Node* root)
{
    int left_height = root->left == nullptr ? 0 : root->left->height;
    int right_height = root->right == nullptr ? 0 : root->right->height;
    if (left_height - right_height > 1)
    {
        // too many vertexes on the left
        if (root->left->right != nullptr) { /* left + right rotation */ this->left_rotation(root->left); this->right_rotation(root); }
        else { /* right rotation */ this->right_rotation(root); }
    }
    if (right_height - left_height > 1)
    {
        // too many vertexes on the right
        if (root->right->left != nullptr) { /* left + right rotation */ this->right_rotation(root->right); this->left_rotation(root); }
        else { /* right rotation */ this->left_rotation(root); }
    }
    // WRONG: root->height = 1 + (left_height > right_height ? left_height : right_height);
    return root;
    // TODO: height
}

int* AVLTree::find(Node* root, int value) const
{
    if (root == nullptr) return nullptr;
    if (value < root->value) return this->find(root->left, value);
    if (value > root->value) return this->find(root->right, value);
    return &(root->value);
}
int* AVLTree::lowerBound(Node* root, int value) const
{
    Node* answer = nullptr;
    while (root != nullptr)
    {
        if (value == root->value) return &(root->value); 
        if (value < root->value) { answer = root; root = root->left; }
        else root = root->right;
    }
    return answer ? &(answer->value) : nullptr; 
}
void AVLTree::traverse_to_buffer(Node* root, int* buffer, int* filled_length) const
{
    if (root == nullptr) return;
    this->traverse_to_buffer(root->left, buffer, filled_length);
    buffer[(*filled_length)++] = root->value;
    this->traverse_to_buffer(root->right, buffer, filled_length);
}

void AVLTree::insert(int value)
{
    if (this->root == nullptr) { this->root = new Node(value); this->size++; }
    else this->insert(this->root, value);
}
void AVLTree::insert(Node* root, int value)
{
    if (value < root->value)
    {
        if (root->left == nullptr) { root->left = new Node(value); root->left->parent = root; this->size++; }
        else this->insert(root->left, value);
    }
    if (value > root->value)
    {
        if (root->right == nullptr) { root->right = new Node(value); root->right->parent = root; this->size++; }
        else this->insert(root->right, value);
    }
    this->fix_balance(root);
}

void AVLTree::erase(int value)
{
    if (this->root == nullptr) return;
    if (this->size == 1) { delete this->root; this->root = nullptr; return; }
    else this->erase(this->root, value);
}
void AVLTree::erase(Node* root, int value)
{
    if (value == root->value)
    {
        // root to delete
        Node* parent = nullptr;
        if (!root->left && !root->right)
        {
            parent = root->parent;
            if (parent->left == root) parent->left = nullptr;
            if (parent->right == root) parent->right = nullptr;
            delete root;
            while (parent) { parent = this->fix_balance(parent); parent = parent->parent; }
            return;
        }
        if (root->left && !root->right)
        {
            parent = root->parent;
            if (!parent)
            {
                this->root = root->left;
                this->root->parent = nullptr;
            }
            else
            {
                if (parent->left == root) parent->left = root->left;
                else parent->right = root->left;
                root->left->parent = parent;
            }
            delete root;
            while (parent) { parent = this->fix_balance(parent); parent = parent->parent; }
            return;
        }
        if (!root->left && root->right)
        {
            parent = root->parent;
            if (!parent)
            {
                this->root = root->right;
                this->root->parent = nullptr;
            }
            else
            {
                if (parent->left == root) parent->left = root->right;
                else parent->right = root->right;
                root->right->parent = parent;
            }
            delete root;
            while (parent) { parent = this->fix_balance(parent); parent = parent->parent; }
            return;
        }
        if (root->left && root->right)
        {
            Node* iop = root->left;
            while (iop->right) iop = iop->right;
            root->value = iop->value;
            this->erase(iop, iop->value);
        }
        return;
    }
    if (value < root->value) this->erase(root->left, value);
    else this->erase(root->right, value);
}

int* AVLTree::traversal() const
{
    int length = 0;
    int* data = (int*)(malloc(this->size * sizeof(int)));
    this->traverse_to_buffer(this->root, data, &length);
    return data;
}