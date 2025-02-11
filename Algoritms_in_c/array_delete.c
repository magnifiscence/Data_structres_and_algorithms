#include <stdio.h>

void deleteElement(int arr[], int *size, int position) {
    if (position < 0 || position >= *size) {
        printf("invalid position\n");
        return;
    }
    for (int i = position; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
}

void traverseArray(int arr[], int size) {
    printf("Array elements are:\n");
    for (int i = 0; i < size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size;
    printf("enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];
    printf("enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d, ", &arr[i]);
    }

    int position;
    printf("enter the position of the element to delete: ");
    scanf("%d", &position);

    deleteElement(arr, &size, position);
    traverseArray(arr, size);

    return 0;
}