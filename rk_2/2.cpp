#include <iostream>
#include <stack>
#include <string>
#include <sstream>


template<typename T>
struct BinarySearchTreeNode {
    T data;
    BinarySearchTreeNode* left;  
    BinarySearchTreeNode* right;
    int minHeight;
    BinarySearchTreeNode(const T& value)
    : data(value), left(nullptr), right(nullptr), minHeight(1)
    {
    }
};

template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
public:
    BinarySearchTree()
    : root(nullptr), cmp(Comparator())
    {
    }

    ~BinarySearchTree()
    {
        std::stack<BinarySearchTreeNode<T>*> BST;
        if (root)
        {
            BST.push(root);
        }

        while (!BST.empty())
        {
            BinarySearchTreeNode<T>* node = BST.top();
            BST.pop();

            if (node->left)
            {
                BST.push(node->left);
            }

            if (node->right)
            {
                BST.push(node->right);
            }

            delete node;
        }
    }

    void Add(const T &value)
    {
        root = AddInternal(root, value);
    }

    int ShortestPathToLeaf() const
    {
        return root ? root->minHeight : 0;
    }

private:
    BinarySearchTreeNode<T>* root;
    Comparator cmp;

    BinarySearchTreeNode<T>* AddInternal(BinarySearchTreeNode<T>* node, const T& value)
    {
        if (node == nullptr)
        {
            return new BinarySearchTreeNode<T>(value);
        }

        if (cmp(value, node->data))
        {
            node->left = AddInternal(node->left, value);
        }
        else
        {
            node->right = AddInternal(node->right, value);
        }

        UpdateMinHeight(node);
        return node;
    }

    void UpdateMinHeight(BinarySearchTreeNode<T>* node)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            node->minHeight = 1;
        }
        else if (node->left == nullptr)
        {
            node->minHeight = 1 + node->right->minHeight;
        }
        else if (node->right == nullptr)
        {
            node->minHeight = 1 + node->left->minHeight;
        }
        else
        {
            node->minHeight = 1 + std::min(node->left->minHeight, node->right->minHeight);
        }
    }
};

int main()
{
    std::string input;
    std::getline(std::cin, input);

    BinarySearchTree<int> BST;

    std::istringstream iss(input);
    int value;

    while (iss >> value) {
        BST.Add(value);
    }

    std::cout << BST.ShortestPathToLeaf() << std::endl;

    return 0;
}