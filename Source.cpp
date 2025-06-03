#include <iostream>
using namespace std;

void printArray(int* arr, int size) {
    for (int* p = arr; p < arr + size; p++) cout << *p << " ";
    cout << endl;
}

void deleteByIndex(int*& arr, int& size, int index) {
    if (index < 0 || index >= size) return;
    int* newArr = new int[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            *(newArr + j) = *(arr + i);
            j++;
        }
    }
    delete[] arr;
    arr = newArr;
    size--;
}

int* extractNegatives(int* arr, int size, int& newSize) {
    newSize = 0;
    for (int* p = arr; p < arr + size; p++) {
        if (*p < 0) newSize++;
    }
    int* negArr = new int[newSize];
    for (int i = 0, j = 0; i < size; i++) {
        if (*(arr + i) < 0) {
            *(negArr + j) = *(arr + i);
            j++;
        }
    }
    return negArr;
}

void appendBlock(int*& arr, int& size, int* block, int blockSize) {
    int* newArr = new int[size + blockSize];
    for (int i = 0; i < size; i++) newArr[i] = arr[i];
    for (int i = 0; i < blockSize; i++) newArr[size + i] = block[i];
    delete[] arr;
    arr = newArr;
    size += blockSize;
}

void insertBlock(int*& arr, int& size, int* block, int blockSize, int index) {
    if (index < 0 || index > size) return;
    int* newArr = new int[size + blockSize];
    for (int i = 0; i < index; i++) newArr[i] = arr[i];
    for (int i = 0; i < blockSize; i++) newArr[index + i] = block[i];
    for (int i = index; i < size; i++) newArr[i + blockSize] = arr[i];
    delete[] arr;
    arr = newArr;
    size += blockSize;
}

void deleteBlock(int*& arr, int& size, int index, int blockSize) {
    if (index < 0 || index + blockSize > size) return;
    int* newArr = new int[size - blockSize];
    for (int i = 0; i < index; i++) newArr[i] = arr[i];
    for (int i = index + blockSize; i < size; i++) newArr[i - blockSize] = arr[i];
    delete[] arr;
    arr = newArr;
    size -= blockSize;
}

int main() {
    setlocale(LC_ALL, "ukr,ru");
    int size = 8;
    int* arr = new int[size] {3, -4, 7, -1, 9, 2, -6, 5};
    printArray(arr, size);

    int delIdx;
    cin >> delIdx;
    deleteByIndex(arr, size, delIdx);
    printArray(arr, size);

    int negSize;
    int* negatives = extractNegatives(arr, size, negSize);
    printArray(negatives, negSize);
    delete[] negatives;

    int block1[] = { 100, 200, 300 };
    appendBlock(arr, size, block1, 3);
    printArray(arr, size);

    int block2[] = { 777, 888 };
    insertBlock(arr, size, block2, 2, 2);
    printArray(arr, size);

    deleteBlock(arr, size, 3, 2);
    printArray(arr, size);

    delete[] arr;
    return 0;
}
