#include <iostream>
#include <vector>
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

    std::vector<T> PostOrderTraversal()
    {
        std::vector<T> BST;
        if (root == nullptr)
        {
            return BST;
        }

        std::vector<BinarySearchTreeNode<T>*> vector1;
        std::vector<BinarySearchTreeNode<T>*> vector2;

        vector1.push_back(root);
        while (!vector1.empty())
        {
            BinarySearchTreeNode<T>* node = vector1.back();
            vector1.pop_back();
            vector2.push_back(node);

            if (node->left)
            {
                vector1.push_back(node->left);
            }

            if (node->right)
            {
                vector1.push_back(node->right);
            }
        }

        while (!vector2.empty())
        {
            BST.push_back(vector2.back()->data);
            vector2.pop_back();
        }
        return BST;
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

    std::vector<int> postOrder = BST.PostOrderTraversal();

    for (int value : postOrder) 
    {
        std::cout << value << " ";
    }

    return 0;
}