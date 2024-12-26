#include <iostream>
#include <unordered_set>
#include <string>


const int PRIME_STRING = 71, PRIME_INT = 31;

struct StringHasher {
    size_t prime;

    StringHasher(size_t prime = PRIME_STRING)
        : prime(prime)
    {
    }

    size_t operator()(const std::string &str) const {
        size_t hash = 0;
        for (char ch : str) {
            hash = hash * prime + ch;
        }
        return hash;
    }
};


struct IntHasher {
    size_t prime;

    IntHasher(size_t prime = PRIME_INT) 
        : prime(prime) 
    {
    }

    size_t operator()(int value) const {
        return value * prime;
    }
};


struct Node {
    std::string product_name;
    int color;
    int size;

    bool operator==(const Node& other) const {
        return product_name == other.product_name &&
               color == other.color &&
               size == other.size;
    }
};


namespace std {
    template <>
    struct hash<Node> {
        size_t operator()(const Node& node) const {
            StringHasher stringHasher(PRIME_STRING);
            IntHasher intHasher(PRIME_INT);
            return stringHasher(node.product_name) ^ (intHasher(node.color) << 1) ^ (intHasher(node.size) << 2);
        }
    };
}


int main() {
    std::unordered_set<Node> my_customized_set;

    char op;
    std::string product_name;
    int color, size;

    while (std::cin >> op >> product_name >> color >> size) {
        Node node = {product_name, color, size};
        switch (op) {
            case '?': {
                std::cout << (my_customized_set.find(node) != my_customized_set.end() ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '+': {
                std::cout << (my_customized_set.insert(node).second ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-': {
                std::cout << (my_customized_set.erase(node) ? "OK" : "FAIL") << std::endl;
                break;
            }
            default: {
                std::cout << "ERROR: unknown operation" << std::endl;
                break;
            }
        }
    }
    return 0;
}