#include <iostream>
#include <queue>
#include <stack>


template<typename T>
struct BinarySearchTreeNode {
    T data;
    BinarySearchTreeNode* left;  
    BinarySearchTreeNode* right;

    BinarySearchTreeNode(const T& value)
    : data(value), left(nullptr), right(nullptr) 
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
        if (root == nullptr)
        {
            root = new BinarySearchTreeNode<T>(value);
            return;
        }

        BinarySearchTreeNode<T>* current = root;
        BinarySearchTreeNode<T>* parent = nullptr;
        while (current != nullptr)
        {
            parent = current;

            if (cmp(value, current->data))
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        BinarySearchTreeNode<T>* newNode = new BinarySearchTreeNode<T>(value);

        if (cmp(value, parent->data)) 
        {
            parent->left = newNode;
        } 
        else 
        {
            parent->right = newNode;
        }
    }

    bool AllNodesEqualBFS()
    {
        if (root == nullptr) 
            return true;

        std::queue<BinarySearchTreeNode<T>*> queue;
        queue.push(root);
        T value = root->data;

        while (!queue.empty())
        {
            BinarySearchTreeNode<T>* node = queue.front();
            queue.pop();

            if (node->data != value)
            {
                return false;
            }
            if (node->left)
            {
                queue.push(node->left);
            } 
            if (node->right)
            {
                queue.push(node->right);
            }
        }
        return true;
    }

private:
    BinarySearchTreeNode<T>* root;
    Comparator cmp;
};

int main()
{
    int N;
    std::cin >> N;

    BinarySearchTree<int> BST;

    for (int i = 0; i < N; i++) 
    {
        int value;
        std::cin >> value;
        BST.Add(value);
    }

    std::cout << (BST.AllNodesEqualBFS() ? 1 : 0) << std::endl;

    return 0;
}