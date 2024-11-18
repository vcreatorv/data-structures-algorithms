#include <iostream>
#include <algorithm>

struct Interval {
    int start;
    int end;

    Interval() : start(0), end(0) {}

    Interval(int s, int e) : start(s), end(e) {}


    friend std::istream& operator>>(std::istream& is, Interval& i) {
        is >> i.start >> i.end;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Interval& i) {
        os << "(" <<  i.start << ", " << i.end << ")";
        return os;
    }
};

bool compareIntervals(const Interval& a, const Interval& b) {
    if (a.end == b.end) {
        return a.start < b.start;
    }
    return a.end < b.end;
}

template <typename T, typename Comparator = std::less<T>>
void merge(T *arr, int left, int mid, int right, Comparator cmp) {
    int size_left_half = mid - left + 1;
    int size_right_half = right - mid;

    T *L = new T[size_left_half];
    T *R = new T[size_right_half];

    for (int i = 0; i < size_left_half; i++) {
         L[i] = arr[left + i];
    }

    for (int j = 0; j < size_right_half; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < size_left_half && j < size_right_half) {
        if (cmp(L[i], R[j])) {
            arr[k++] = L[i++];
        } 
        else {
            arr[k++] = R[j++];
        }
    }

    while (i < size_left_half) {
        arr[k++] = L[i++];
    }

    while (j < size_right_half) {
        arr[k++] = R[j++];
    }
}



template <typename T, typename Comparator = std::less<T>>
void mergeSort(T *arr, int left, int right, Comparator cmp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, cmp);
        mergeSort(arr, mid + 1, right, cmp);
        merge(arr, left, mid, right, cmp);
    }
}



int minAdvertismentsToShow(Interval *arr, int size) {
    mergeSort(arr, 0, size - 1, compareIntervals);

    int count = 0;
    int last_ad_showed_at = -1;
    int first_ad_showed_at = -1;
    for (int i = 0; i < size; i++) {
        if (last_ad_showed_at < arr[i].start) {
            count += 2;
            first_ad_showed_at = arr[i].end - 1;
            last_ad_showed_at = arr[i].end;
        }

        else if (last_ad_showed_at == arr[i].start) {
            count++;
            first_ad_showed_at = last_ad_showed_at;
            last_ad_showed_at = arr[i].end;
        }

        else if (last_ad_showed_at > arr[i].start && first_ad_showed_at < arr[i].start) {
            count++;
            first_ad_showed_at = last_ad_showed_at;
            last_ad_showed_at = arr[i].end;
        }
    }

    return count;
}


int main() {
    int size;
    std::cin >> size;

    Interval *arr = new Interval[size];

    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    int result = minAdvertismentsToShow(arr, size);
    std::cout << result;

    // mergeSort(arr, 0, size - 1, compareIntervals);
    // for (int i = 0; i < size; i++) {
    //     std::cout << arr[i];
    // }

    delete[] arr;
    return 0;
}