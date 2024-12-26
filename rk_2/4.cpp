#include <iostream>
#include <stdexcept>
#include <string>


enum Operation 
{ 
    INSERT, 
    DELETE, EXISTS, 
    NEXT, 
    PREV, 
    INVALID 
};

Operation getOperation(const std::string &operation)
{
    if (operation == "insert") return INSERT;
    if (operation == "delete") return DELETE;
    if (operation == "exists") return EXISTS;
    if (operation == "next") return NEXT;
    if (operation == "prev") return PREV;
    return INVALID;
}

template <typename T, typename Comparator = std::less<T>>
class AvlTree
{
  struct Node
  {
      Node(const T &data)
      : data(data), left(nullptr), right(nullptr), height(1), size(1)
      {
      }
      
      T data;
      Node *left;
      Node *right;
      size_t height;
      size_t size;
  };
    
public:
    AvlTree(Comparator cmp = Comparator())
    : root(nullptr), compare(cmp)
    {
    }
    
    ~AvlTree()
    {
        destroyTree(root);
    }
    
    void Add(const T &data)
    {
        if (Has(data)) {
            return;
        }
        root = addInternal(root, data);
    }
    
    bool Has(const T &data)
    {
        Node *tmp = root;
        while (tmp)
        {
            if (tmp->data == data)
                return true;
            else if (compare(tmp->data, data))
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return false;
    }
    
    void Delete(const T &data)
    {
        if (!Has(data)) {
            return;
        }
        root = deleteInternal(root, data);
    }
    
    T Next(const T &data)
    {
        Node* nextNode = findNextInternal(root, data);
        return nextNode ? nextNode->data : T();
    }

    T Prev(const T &data)
    {
        Node* prevNode = findPrevInternal(root, data);
        return prevNode ? prevNode->data : T();
    }

private:
    Node *root;
    Comparator compare;
    
    void destroyTree(Node *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    Node* addInternal(Node *node, const T &data)
    {
        if (!node)
            return new Node(data);
        if (compare(node->data, data))
            node->right = addInternal(node->right, data);
        else
            node->left = addInternal(node->left, data);
        
        return doBalance(node);
    }
    
    Node* deleteInternal(Node *node, const T &data)
    {
        if (!node)
            return nullptr;
        if (compare(data, node->data))
            node->left = deleteInternal(node->left, data);
        else if (compare(node->data, data))
            node->right = deleteInternal(node->right, data);
        else
        {
            Node *left = node->left;
            Node *right = node->right;
            
            delete node;
            
            if (!right)
                return left;
                
            if (getHeight(left) > getHeight(right))
            {
                Node *max = findAndRemoveMax(left);
                max->left = left;
                max->right = right;
                return doBalance(max);
            }
            else
            {
                Node *min = findAndRemoveMin(right);
                min->left = left;
                min->right = right;
                return doBalance(min);
            }
            
        }
        
        return doBalance(node);
    }
    
    size_t getHeight(Node *node)
    {
        return node ? node->height : 0;
    }
    
    size_t getSize(Node *node) 
    {
        return node ? node->size : 0;
    }
    
    void updateHeightAndSize(Node *node)
    {
        node->size = getSize(node->left) + getSize(node->right) + 1;
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    Node* findAndRemoveMin(Node*& node)
    {
        if (!node->left)
        {
            Node *min = node;
            node = node->right;
            return min; 
        }
        
        Node* minNode = findAndRemoveMin(node->left);
        node = doBalance(node);
        return minNode;
    }

    Node* findAndRemoveMax(Node*& node)
    {
        if (!node->right)
        {
            Node *max = node;
            node = node->left;
            return max;
        }
        
        Node* maxNode = findAndRemoveMax(node->right);
        node = doBalance(node);
        return maxNode;
    }
    
    int getBalance(Node *node)
    {
        return getHeight(node->right) - getHeight(node->left);
    }
    
    Node* rotateLeft(Node *node)
    {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        updateHeightAndSize(node);
        updateHeightAndSize(tmp);
        return tmp;
    }
    
    Node* rotateRight(Node *node)
    {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        updateHeightAndSize(node);
        updateHeightAndSize(tmp);
        return tmp;
    }
    
    Node* doBalance(Node *node)
    {
        updateHeightAndSize(node);
        switch (getBalance(node))
        {
            case 2:
            {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2:
            {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }
    
    Node* findNextInternal(Node *node, const T &data)
    {
        Node* next_by_size = nullptr;
        while (node)
        {
            if (compare(data, node->data))
            {
                next_by_size = node;
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        return next_by_size;
    }

    Node* findPrevInternal(Node *node, const T &data)
    {
        Node* prev_by_size = nullptr;
        while (node)
        {
            if (compare(node->data, data))
            {
                prev_by_size = node;
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }
        return prev_by_size;
    }
};

int main() 
{
    std::string operation;
    int value;
    AvlTree<int> tree;

    while (std::cin >> operation >> value) 
    {
        switch (getOperation(operation))
        {
            case INSERT:
                tree.Add(value);
                break;
            case DELETE:
                tree.Delete(value);
                break;
            case EXISTS:
                std::cout << (tree.Has(value) ? "true" : "false") << std::endl;
                break;
            case NEXT:
                {
                    int result = tree.Next(value);
                    std::cout << (result == 0 ? "none" : std::to_string(result)) << std::endl;
                    break;
                }
            case PREV:
                {
                    int result = tree.Prev(value);
                    std::cout << (result == 0 ? "none" : std::to_string(result)) << std::endl;
                    break;
                }
            default:
                break;
        }
    }

    return 0;
}