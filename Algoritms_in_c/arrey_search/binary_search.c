#include <stdio.h>

int binarySearch(int arr[], int size, int key) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return mid; // Return the index of the found element
        }
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;//element not found
}

int main() {
    int arr[] = {0, 1, 2, 4, 9}; //arrey most be sorted in binary search
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 4;
    int result = binarySearch(arr, size, key);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }
    return 0;
}