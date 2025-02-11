#include <stdio.h>

//it is based on partitioning an array into smaller sub arrays. A pivot element is chosen and the array is partitioned
//such that the elements less than the pivot are on the left while those greater than the pivot are on the right
//This process is recursively applied to the sub arrays.

//function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// function to find the partion position
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; //pivot
    int i = (low - 1); // index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // if current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);

}

// function to perform quick sort on an array
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        //pi is a partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, hight);

        //seperately sort elements before partioning and after partitioning
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//function to execute quick sort algorthm
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    int i;

    printf("Original array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubbleSort(arr, n);

    printf("Sorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}