#include <iostream>

int findPeak(int* arr, int n) {
    int i = 1;
    while (i < n && arr[i] > arr[i - 1]) {
        i *= 2;
    }
    
        
    int left = i / 2;
    int right = i < n ? i : n - 1;

    while (right >= left) {
        int mid = left + (right - left) / 2;
        
        if (mid == 0 || mid == n - 1) {
            return mid;
        }
        
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
            return mid;
        }
        
        if (arr[mid] > arr[mid - 1]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    return -1;
}


int main()
{
    int n;
    std::cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    int resuleft = findPeak(arr, n);
    std::cout << resuleft << std::endl;

    delete[] arr;
    return 0;
}
