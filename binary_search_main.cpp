#include <iostream>
using namespace std;

/**
 * Находит первое вхождение элемента в отсортированном массиве (левый бинарный поиск)
 * @param array Отсортированный массив
 * @param arraySize Размер массива
 * @param targetValue Искомое значение
 * @return Позиция элемента (1-based) или -1 если не найдено
 */
int findFirstOccurrence(int* array, int arraySize, int targetValue) {
    int left = -1;
    int right = arraySize;

    while (left < right - 1) {
        int mid = (left + right) / 2;
        if (array[mid] < targetValue) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (right < arraySize && array[right] == targetValue) {
        return right + 1;
    }
    return -1;
}

/**
 * Находит последнее вхождение элемента в отсортированном массиве (правый бинарный поиск)
 * @param array Отсортированный массив
 * @param arraySize Размер массива
 * @param targetValue Искомое значение
 * @return Позиция элемента (1-based) или -1 если не найдено
 */
int findLastOccurrence(int* array, int arraySize, int targetValue) {
    int left = -1;
    int right = arraySize;

    while (left < right - 1) {
        int mid = (left + right) / 2;
        if (array[mid] <= targetValue) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (left >= 0 && array[left] == targetValue) {
        return left + 1;
    }
    return -1;
}

int main() {
    int arraySize;
    cin >> arraySize;

    int* sortedArray = new int[arraySize];
    for (int i = 0; i < arraySize; i++) {
        cin >> sortedArray[i];
    }

    int queriesCount;
    cin >> queriesCount;

    for (int i = 0; i < queriesCount; i++) {
        int targetValue;
        cin >> targetValue;

        int firstPos = findFirstOccurrence(sortedArray, arraySize, targetValue);
        int lastPos = findLastOccurrence(sortedArray, arraySize, targetValue);

        cout << firstPos << " " << lastPos << "\n";
    }

    delete[] sortedArray;
    return 0;
}