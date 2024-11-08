#include <iostream>
#include <algorithm>

class Video {
public:
    int likes;
    int comments;
    int views;

    Video(int likes = 0, int comments = 0, int views = 0) 
        : likes(likes), comments(comments), views(views) {}

    friend std::ostream& operator<<(std::ostream& os, const Video& video) {
        os << "(Likes: " << video.likes << ", Comments: " << video.comments << ", Views: " << video.views << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Video& video) {
        is >> video.likes >> video.comments >> video.views;
        return is;
    }
};

struct VideoComparator {
    bool operator()(const Video& v1, const Video& v2) const {
        return v1.likes < v2.likes; 
    }
};

template <typename T>
struct ArrayIterator {
    const T* arr;
    int size;
    int curPos;

    ArrayIterator(const T* arr, int size) : arr(arr), size(size), curPos(0) {}

    const T& current() const {
        return arr[curPos];
    }

    void moveNext() {
        curPos++;
    }

    bool hasNext() const {
        return curPos < size;
    }
};

template <typename T, typename Comparator = std::less<T>>
class Heap {
private:
    ArrayIterator<T>** data;
    int capacity;
    int size;
    Comparator cmp;

    void resize() {
        int newCapacity = capacity * 2;
        ArrayIterator<T>** newData = new ArrayIterator<T>*[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (cmp(data[parent]->current(), data[index]->current())) {
                break;
            }
            std::swap(data[parent], data[index]);
            index = parent;
        }
    }

    void siftDown(int index) {
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < size && cmp(data[leftChild]->current(), data[smallest]->current())) {
                smallest = leftChild;
            }

            if (rightChild < size && cmp(data[rightChild]->current(), data[smallest]->current())) {
                smallest = rightChild;
            }

            if (smallest == index) {
                break;
            }

            std::swap(data[index], data[smallest]);
            index = smallest;
        }
    }

public:
    Heap() : capacity(2), size(0) {
        data = new ArrayIterator<T>*[capacity];
    }

    ~Heap() {
        for (int i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
    }

    void add(ArrayIterator<T>* iterator) {
        if (size >= capacity) {
            resize();
        }
        data[size] = iterator;
        siftUp(size);
        ++size;
    }

    ArrayIterator<T>* extract() {
        if (size == 0) {
            return nullptr;
        }
        ArrayIterator<T>* minNode = data[0];
        data[0] = data[--size];
        if (size > 0) {
            siftDown(0);
        }
        return minNode;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

template <typename T, typename Comparator = std::less<T>>
void sort(Heap<T, Comparator>& heap) {
    while (!heap.isEmpty()) {
        ArrayIterator<T>* minNode = heap.extract();
        std::cout << minNode->current() << " ";
        
        minNode->moveNext();
        if (minNode->hasNext()) {
            heap.add(minNode);
        } 
        else {
            delete minNode;
        }
    }
    std::cout << std::endl;
}

int main() {
    // Пример использования с Video
    // Heap<Video, VideoComparator> videoHeap;
    
    // Video arr1[] = {Video(6, 10, 100)};
    // Video arr2[] = {Video(50, 20, 200), Video(90, 30, 300)};
    // Video arr3[] = {Video(1, 5, 50), Video(10, 15, 150), Video(70, 25, 250)};

    // videoHeap.add(new ArrayIterator<Video>(arr1, 1));
    // videoHeap.add(new ArrayIterator<Video>(arr2, 2));
    // videoHeap.add(new ArrayIterator<Video>(arr3, 3));

    // sort(videoHeap);

    Heap<int> intHeap;
    
    int K;
    std::cin >> K; 

    for (int i = 0; i < K; i++) {
        int size;
        std::cin >> size;  

        int* arr = new int[size];
        for (int j = 0; j < size; j++) {
            std::cin >> arr[j]; 
        }

        intHeap.add(new ArrayIterator<int>(arr, size));
    }

    sort(intHeap);

    return 0;
}