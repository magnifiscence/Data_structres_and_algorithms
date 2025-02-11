#include <stdio.h>
 
void insertElement(int arr[], int *size, int element, int position) {
    if (position < 0 || position > *size) {
        printf("Invalid position!\n");
        return;
    }
    for (int i = *size; i > position; i--) {
        arr[i] = arr[i-1];
    }
    arr[position] = element;
    (*size)++;
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

    int arr[size + 1]; // extra space for insertion
    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int element, position;
    printf("enter the element to insert: ");
    scanf("%d", &element);
    printf("enter the position to insert the element: ");
    scanf("%d", &position);

    insertElement(arr, &size, element, position);
    traverseArray(arr, size);

    return 0;
}