#include <stdio.h>

int linearSearch(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i; // Return the index of the found element
        }
    }
    return -1; // element not found
}

int main() {
    int arr[] = {2, 4, 0, 1, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 1;
    int result = linearSearch(arr, size, key);
    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }
    return 0;
}