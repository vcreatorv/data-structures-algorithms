#include <iostream>
#include <vector>
#include <sstream>
#include <string>

template <typename T>
class BTree
{
public:
    struct Node
    {
        Node(bool leaf)
        : leaf(leaf)
        {
        }
        
        ~Node()
        {
            for (Node* child: children)
            {
                delete child;
            }
        }
        
        bool leaf;
        std::vector<T> keys;
        std::vector<Node*> children;
    };
    
    BTree(size_t min_degree)
    : t(min_degree), root(nullptr)
    {
    }
    
    ~BTree()
    {
        if (root)
            delete root;
    }
    
    void Insert(const T &key)
    {
        if (!root)
            root = new Node(true);
        
        if (isNodeFull(root))
        {
            Node *newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            splitChild(root, 0);
        }
        
        insertNonFull(root, key);
    }
    
    void debugPrint()
    {
        debugPrintInternal(root, 0);
    }

    void printTreeByLevels()
    {
        if (!root) return;

        std::vector<Node*> currentLevel;
        currentLevel.push_back(root);

        while (!currentLevel.empty())
        {
            std::vector<Node*> nextLevel;
            for (Node* node : currentLevel)
            {
                for (const T& key : node->keys)
                {
                    std::cout << key << " ";
                }
                if (!node->leaf)
                {
                    nextLevel.insert(nextLevel.end(), node->children.begin(), node->children.end());
                }
            }
            std::cout << std::endl;
            currentLevel = nextLevel;
        }
    }
    
private:
    
    void debugPrintInternal(Node *node, int indent)
    {
        std::cout << std::string(indent, ' ');
        std::cout << "keys: [";
        for (auto it = node->keys.begin(); it != node->keys.end(); it++)
        {
            std::cout << (*it);
            if (it + 1 != node->keys.end())
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        
        for (auto child: node->children)
        {
            debugPrintInternal(child, indent + 4);
        }
    }
    
    bool isNodeFull(Node *node)
    {
        return node->keys.size() == 2*t - 1;
    }
    
    void splitChild(Node *node, size_t index)
    {
        Node *fullChild = node->children[index];
        Node *newChild = new Node(fullChild->leaf);

        for (size_t i = 0; i < t - 1; ++i)
        {
            newChild->keys.push_back(fullChild->keys[t + i]);
        }
        if (!fullChild->leaf)
        {
            for (size_t i = 0; i < t; ++i)
            {
                newChild->children.push_back(fullChild->children[t + i]);
            }
            fullChild->children.resize(t);
        }

        node->children.insert(node->children.begin() + index + 1, newChild);

        node->keys.insert(node->keys.begin() + index, fullChild->keys[t - 1]);

        fullChild->keys.resize(t - 1);

        fullChild->keys.shrink_to_fit();
        if (!fullChild->leaf)
        {
            fullChild->children.shrink_to_fit();
        }
    }

    void insertNonFull(Node *node, const T &key)
    {
        int pos = node->keys.size() - 1;
        
        if (node->leaf)
        {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos])
            {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        }
        else
        {
            while (pos >= 0 && key < node->keys[pos])
            {
                pos--;
            }
            
            if (isNodeFull(node->children[pos + 1]))
            {
                splitChild(node, pos + 1);
                if (key > node->keys[pos + 1])
                    pos++;
            }
            insertNonFull(node->children[pos + 1], key);
        }
    }
    
    size_t t;
    Node *root;
    
    friend void test1();
};

void test1()
{
    BTree<char> tree(3);
    
    tree.root = new BTree<char>::Node(false);
    tree.root->keys = {'G', 'M', 'P', 'X'};
    
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'A', 'C', 'D', 'E'};
        tree.root->children.push_back(child);
    }
    
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'J', 'K'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'N', 'O'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'R', 'S', 'T', 'U', 'V'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'Y', 'Z'};
        tree.root->children.push_back(child);
    }
    
    std::cout << "Initial tree:" << std::endl;
    tree.debugPrint();
    std::cout << std::endl;
    
    std::string insertKeys = "BQLF";
    for (auto c: insertKeys)
    {
        tree.Insert(c);
        std::cout << "After inserting " << c << ":" << std::endl;
        tree.debugPrint();
        std::cout << std::endl;
    }
}


int main(int argc, const char * argv[]) {
    int t;
    std::cin >> t;

    BTree<int> tree(t);

    std::string line;
    std::getline(std::cin, line);
    std::getline(std::cin, line);

    std::istringstream iss(line);
    int element;
    while (iss >> element) {
        tree.Insert(element);
    }
    tree.printTreeByLevels();

    return 0;
}