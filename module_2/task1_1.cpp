#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;
const float C1 = 0.5, C2 = 0.5;
const float LOAD_FACTOR = 0.75;

enum class HashTableNodeType 
{
    NIL,
    KEY, 
    DEL 
};

template <typename T>
struct HashTableNode {
    T key;
    HashTableNodeType type;
    
    HashTableNode() 
    : type(HashTableNodeType::NIL) 
    {
    }

    HashTableNode(const T &key, HashTableNodeType type)
    : key(key), type(type)
    {
    }
};

class StringHasher
{
public:
    StringHasher(size_t prime = 71)
    : prime(prime)
    {
    }
    
    size_t operator()(const std::string &str)
    {
        size_t hash = 0;
        for (int i = 0; i < str.size(); i++)
        {
            hash = hash * prime + str[i];
        }
        return hash;
    }
    
private:
    size_t prime;
};

template <typename T, typename Hasher = std::hash<T>>
class HashTable
{
public:
    HashTable(size_t initial_size = DEFAULT_SIZE)
    : size(0), table(initial_size, HashTableNode<T>())
    {
    }

    ~HashTable()
    {
        table.clear();
        size = 0;
    };

    size_t quadraticProbe(size_t hash, size_t i) 
    {
        return (hash + static_cast<size_t>(C1 * i + C2 * i * i)) % table.size();
    }

    bool Add(const T &key)
    {
        if (static_cast<float>(size) / table.size() >= LOAD_FACTOR) 
        {
            grow();
        }

        size_t hash = hasher(key) % table.size();
        size_t index = quadraticProbe(hash, 0);
        int first_deleted = -1;

        for (int i = 0; i < table.size(); i++)
        {
            if (table[index].type == HashTableNodeType::DEL && first_deleted == -1)
            {
                first_deleted = index;
            }

            if (table[index].type == HashTableNodeType::NIL)
            {
                if (first_deleted != -1)
                {
                    index = first_deleted;
                }
                table[index] = HashTableNode(key, HashTableNodeType::KEY);
                size++;
                return true;
            }

            if (table[index].type == HashTableNodeType::KEY && table[index].key == key)
            {
                return false;
            }

            index = (index + i + 1) % table.size();
        }
        
        if (first_deleted != -1)
        {
            table[first_deleted] = HashTableNode(key, HashTableNodeType::KEY);
            size++;
            return true;
        }

        return false;
    };

    bool Has(const T &key)
    {
        size_t hash = hasher(key) % table.size();
        size_t index = quadraticProbe(hash, 0);

        for (int i = 0; i < table.size(); i++)
        {
            if (table[index].type == HashTableNodeType::NIL)
            {
                return false;
            }

            if (table[index].type == HashTableNodeType::KEY && table[index].key == key)
            {
                return true;
            }

            index = (index + i + 1) % table.size();
        }
        return false;
    };

    bool Delete(const T &key)
    {
        size_t hash = hasher(key) % table.size();
        size_t index = quadraticProbe(hash, 0);

        for (int i = 0; i < table.size(); i++)
        {
            if (table[index].type == HashTableNodeType::NIL)
            {
                return false;
            }

            if (table[index].type == HashTableNodeType::KEY && table[index].key == key)
            {
                table[index].type = HashTableNodeType::DEL;
                size--;
                return true;
            }

            index = (index + i + 1) % table.size();
        }
        return false; 
    };

private:
    void grow()
    {
        std::vector<HashTableNode<T>> oldTable = table;
        table.clear();
        table.resize(oldTable.size() * 2, HashTableNode<T>());
        size = 0;

        for (int i = 0; i < oldTable.size(); i++)
        {
            if(oldTable[i].type == HashTableNodeType::KEY)
            {
                Add(oldTable[i].key);
            }
        }
    }


    std::vector<HashTableNode<T>> table;
    size_t size;
    Hasher hasher;
};

int main()
{
    HashTable<std::string, StringHasher> table;
    
    char op;
    std::string key;

    while (std::cin >> op >> key)
    {
        switch (op)
        {
            case '?':
            {
                std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '+':
            {
                std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-':
            {
                std::cout << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            default:
            {
                std::cout << "ERROR: unknown type of operation" << std::endl;
                break;
            }     
        }
    }
    return 0;
}
