// HW Lesson 4 Algorithms and Data Structures
// Author: Dmitry Selin

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OBSTACLES_X {1, 2, 3}
#define OBSTACLES_Y {1, 3, 1}

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

int binarySearch(int* arr, int len, int v) {
	int left = 0;
	int right = len - 1;
	int mid = (left + right) / 2;

	while (mid != left && mid != right && arr[mid] != v) {
		if (arr[mid] < v)
			left = mid;
		else
			right = mid;
		mid = (left + right) / 2;
	}

	if (arr[mid] == v)
		return mid;
	if (arr[mid + 1] == v)
		return mid + 1;
	return -1;
}

int binarySearchRec(int* arr, int len, int v, int offset = 0) {
	int mid = len / 2;

	if (arr[mid] == v)
		return mid + offset;
	if (len == 1)
		return -1;
	if (arr[mid + 1] == v)
		return mid + offset + 1;
	if (arr[mid] > v)
		return binarySearchRec(arr, mid, v, offset);
	else
		return binarySearchRec(arr + mid + 1, mid, v, offset + mid + 1);
}

int routes(int x, int y) {
	if (x == 0 || y == 0)
		return 1;

	return routes(x - 1, y) + routes(x, y - 1);
}

bool checkObstacles(int x, int y) {
	int obstaclesX[] = OBSTACLES_X;
	int obstaclesY[] = OBSTACLES_Y;

	for (size_t i = 0; i < sizeof(obstaclesX) / sizeof(int); i++)
		if (x == obstaclesX[i] && y == obstaclesY[i])
			return true;

	return false;
}

int routesObstacles(int x, int y) {
	if (x == 0 || y == 0)
		return 1;
	if (checkObstacles(x, y))
		return 0;

	return routesObstacles(x - 1, y) + routesObstacles(x, y - 1);
}


int main() {
	const int testArrLen = 10;
	int testArr[testArrLen];
	fillArray(testArr, testArrLen);
	int tempArr[testArrLen];
	
	printf("Original array:\n");
	printArray(testArr, testArrLen);
	printf("Sorted array:\n");
	memcpy(tempArr, testArr, testArrLen * sizeof(int));
	bubbleSort(tempArr, testArrLen);
	printArray(tempArr, testArrLen);
	
	printf("\nBinary search:\n");
	for (size_t i = 0; i < testArrLen; i++)
		printf("Index of %d: %d\n", tempArr[i], binarySearch(tempArr, testArrLen, tempArr[i]));
	printf("Index of %d: %d\n", 100, binarySearch(tempArr, testArrLen, 100));

	printf("\nBinary search recursive:\n");
	for (size_t i = 0; i < testArrLen; i++)
		printf("Index of %d: %d\n", tempArr[i], binarySearchRec(tempArr, testArrLen, tempArr[i]));
	printf("Index of %d: %d\n", 100, binarySearchRec(tempArr, testArrLen, 100));

	printf("\nRoutes:\n");
	int fieldSize = 5;
	for (size_t i = 0; i < fieldSize; i++) {
		for (size_t j = 0; j < fieldSize; j++)
			printf("%5d ", routes(i, j));
		printf("\n");
	}

	printf("\nRoutes with obstacles:\n");
	for (size_t i = 0; i < fieldSize; i++) {
		for (size_t j = 0; j < fieldSize; j++)
			printf("%5d ", routesObstacles(i, j));
		printf("\n");
	}

	return 0;
}