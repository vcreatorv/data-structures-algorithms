#include <iostream>

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T, typename Comparator = std::less<T>>
int partition(T* arr, int left, int right, Comparator cmp) {
    int pivot_index = left + rand() % (right - left + 1);
    T pivot_value = arr[pivot_index];
    
    swap(arr[pivot_index], arr[right]);

    int i = right - 1;
    int j = right - 1;

    while (j >= left) {
        if (cmp(arr[j], pivot_value)) {
            j--;
        }
        else {
            swap(arr[i], arr[j]);
            i--;
            j--;
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

template <typename T, typename Comparator = std::less<T>>
T findKthStatistic(T* arr, int n, int k, Comparator cmp = Comparator()) {
    int left = 0;
    int right = n - 1;

    while (true) {
        int pivot_index = partition(arr, left, right, cmp);

        if (k == pivot_index) {
            return arr[k];
        } 
        else if (k < pivot_index) {
            right = pivot_index - 1;
        } 
        else {
            left = pivot_index + 1;
        }
    } 
}

int main() {
    int n;
    std::cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int percentil_10 = findKthStatistic(arr, n, n / 10);

    int mediana = findKthStatistic(arr, n, n / 2);

    int percentil_90 = findKthStatistic(arr, n, 9 * n / 10);

    std::cout << percentil_10 << std::endl;
    std::cout << mediana << std::endl;
    std::cout << percentil_90 << std::endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
}
