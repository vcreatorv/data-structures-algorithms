#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
private:
    T* deque;
    int n;
    int head;
    int tail;

    void resize(int newSize) {
        T* newDeque = new T[newSize];
        int currentSize = size();
        for (int i = 0; i < currentSize; i++) {
            newDeque[i] = deque[(head + i) % n];
        }
        delete[] deque;
        deque = newDeque;
        head = 0;
        tail = currentSize;
        n = newSize;
    }

public:
    Deque(int initialSize = 2) : n(initialSize), head(0), tail(0) {
        deque = new T[n];
    }

    ~Deque() {
        delete[] deque;
    }

    int size() const {
        return (tail - head + n) % n;
    }

    void pushFront(const T& x) {
        if (size() == n - 1) {
            resize(n * 2);
        }
        head = (head - 1 + n) % n;
        deque[head] = x;
    }

    void pushBack(const T& x) {
        if (size() == n - 1) {
            resize(n * 2);
        }
        deque[tail] = x;
        tail = (tail + 1) % n;
    }

    T popFront() {
        if (size() == 0) {
            throw std::out_of_range("Deque is empty");
        }
        T value = deque[head];
        head = (head + 1) % n;
        if (size() > 0 && size() * 4 <= n) {
            resize(n / 2);
        }
        return value;
    }

    T popBack() {
        if (size() == 0) {
            throw std::out_of_range("Deque is empty");
        }
        tail = (tail - 1 + n) % n;
        T value = deque[tail];
        if (size() > 0 && size() * 4 <= n) {
            resize(n / 2);
        }
        return value;
    }
};

int main() {
    int n;
    std::cin >> n;

    Deque<int> deq;
    bool allCorrect = true;

    for (int i = 0; i < n; i++) {
        int command, value;
        std::cin >> command >> value;

        try {
            switch (command) {
                case 1:
                    deq.pushFront(value);
                    break;
                case 2:
                    if (deq.size() == 0) {
                        if (value != -1) {
                            allCorrect = false;
                        }
                    } 
                    else {
                        int popped = deq.popFront();
                        if (popped != value) {
                            allCorrect = false;
                        }
                    }
                    break;
                case 3:
                    deq.pushBack(value);
                    break;
                case 4:
                    if (deq.size() == 0) {
                        if (value != -1) {
                            allCorrect = false;
                        }
                    } 
                    else {
                        int popped = deq.popBack();
                        if (popped != value) {
                            allCorrect = false;
                        }
                    }
                    break;
            }
        } catch (const std::out_of_range&) {
            if (value != -1) {
                allCorrect = false;
            }
        }

        if (!allCorrect) {
            break;
        }
    }

    std::cout << (allCorrect ? "YES" : "NO") << std::endl;

    return 0;
}

