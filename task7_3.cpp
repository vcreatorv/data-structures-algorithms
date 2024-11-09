#include <iostream>

void binaryMSDSort(unsigned long long* arr, int left, int right, int bit) {
    if (left >= right || bit < 0) {
        return;
    }


    int i = left, j = right;
    while (i <= j) {

        while (i <= j && !(arr[i] & (1ULL << bit))) {
            i++;
        }

        while (i <= j && (arr[j] & (1ULL << bit))) {
            j--;
        }

        if (i < j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    binaryMSDSort(arr, left, j, bit - 1);
    binaryMSDSort(arr, i, right, bit - 1);
}

int main() {
    int n;
    std::cin >> n;

    unsigned long long* arr = new unsigned long long[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    binaryMSDSort(arr, 0, n - 1, 63);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    delete[] arr;

    return 0;
}