// HW Lesson 3 Algorithms and Data Structures
// Author: Dmitry Selin

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void fillArray(int* buf, int len) {
	for (size_t i = 0; i < len; i++)
		buf[i] = rand() % 100;
}

void printArray(int* arr, int len) {
	for (size_t i = 0; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void swap(int* a, int* b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int bubbleSort(int* arr, int len) {
	int comparisons = 0;
	for (size_t i = 0; i < len; i++)
		for (size_t j = 0; j < len - 1; j++)
		{
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
			comparisons++;
		}
	return comparisons;
}

int bubbleSortOptimized(int* arr, int len) {
	int comparisons = 0;
	bool changes = false;
	int rightBorderLen = 0;

	for (size_t i = 0; i < len; i++)
	{
		for (size_t j = 0; j < len - 1; j++)
		{
			if (j == (len - rightBorderLen))
				break;
			
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				changes = true;
			}
			comparisons++;
		}
		
		if (!changes)
			break;
		changes = false;
		rightBorderLen++;
	}
	return comparisons;
}

int shakerSort(int* arr, int len) {
	int leftShift = 0;
	int rightShift = 0;
	int comparisons = 0;
	bool changes = false;

	while (len > (leftShift + rightShift + 1)) {
		// go forward
		for (size_t i = leftShift; i < len - 1 - rightShift; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(&arr[i], &arr[i + 1]);
				changes = true;
			}
			comparisons++;
		}
		rightShift++;
		if (!changes)
			break;
		changes = false;

		// go backward
		for (size_t i = len - 1 - rightShift; i > leftShift; i--) {
			if (arr[i] < arr[i - 1]) {
				changes = true;
				swap(&arr[i], &arr[i - 1]);
			}
			comparisons++;
		}
		leftShift++;
		if (!changes)
			break;
		changes = false;
	}
	
	return comparisons;
}

int linearSearchRec(int* arr, int len, int v, int step = 0) {
	if (len == 0)
		return -1;
	if (arr[0] == v)
		return step;

	return linearSearchRec(arr + 1, len - 1, v, ++step);
}

int main() {
	const int testArrLen = 25;
	int testArr[testArrLen];
	fillArray(testArr, testArrLen);
	int tempArr[testArrLen];
	
	printf("Classic bubble sort\n");
	memcpy(tempArr, testArr, testArrLen * sizeof(int));
	printArray(tempArr, testArrLen);
	int bubbleComparisons = bubbleSort(tempArr, testArrLen);
	printArray(tempArr, testArrLen);
	printf("Comparisons: %d\n", bubbleComparisons);

	printf("\nOptimized bubble sort\n");
	memcpy(tempArr, testArr, testArrLen * sizeof(int));
	printArray(tempArr, testArrLen);
	int bubbleComparisonsOpt = bubbleSortOptimized(tempArr, testArrLen);
	printArray(tempArr, testArrLen);
	printf("Comparisons: %d\n", bubbleComparisonsOpt);

	printf("\nShaker sort\n");
	memcpy(tempArr, testArr, testArrLen * sizeof(int));
	printArray(tempArr, testArrLen);
	int shakerComparisons = shakerSort(tempArr, testArrLen);
	printArray(tempArr, testArrLen);
	printf("Comparisons: %d\n", shakerComparisons);

	printf("\nRecursive linear search\n");
	printArray(testArr, testArrLen);
	int testNum = 53;
	int index = linearSearchRec(testArr, testArrLen, testNum);
	printf("Index of %d is %d\n", testNum, index);
}