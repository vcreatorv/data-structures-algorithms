#include <iostream>
#include <stdexcept>


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
        root = deleteInternal(root, data);
    }
    
    T getKthStatistic(int k)
    {
        Node* result = getKthStatisticInternal(root, k);
        if (result)
            return result->data;
        throw std::out_of_range("Index out of range for k-th statistic");
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
    
    Node* getKthStatisticInternal(Node *node, int k)
    {
        if (!node)
            return nullptr;
        
        int leftSize = getSize(node->left);
       
        if (k == leftSize + 1)
            return node;
        
        if (k <= leftSize)
            return getKthStatisticInternal(node->left, k);
        else
            return getKthStatisticInternal(node->right, k - leftSize - 1);
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
    
};

int main(int argc, const char * argv[]) 
{
    int N;
    std::cin >> N;
    
    AvlTree<int> tree;
    
    for (int i = 0; i < N; i++) 
    {
        int num, k;
        std::cin >> num >> k;
        
        if (num > 0) 
            tree.Add(num);
        else if (num < 0)
            tree.Delete(-num);
        
        std::cout << tree.getKthStatistic(k + 1) << std::endl;
    }
    
    return 0;
}