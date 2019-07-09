// ДЗ к уроку 2 по курсу Алгоритмы и Структуры данных
// Автор: Дмитрий Селин

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEC_TO_BIN_BUFFER_SIZE 1000
#define CALC_TREE_MAX_NODES 1000

void decToBinRec(int dec, char * dest) {
	size_t offset = strlen((char*)dest);
	dest[offset] = dec % 2 == 0 ? '0' : '1';
	dec = dec >> 1;
	dest[offset + 1] = 0;
	if (dec == 0)
	{
		char* reversed = _strrev(dest);
		strcpy_s(dest, strlen(reversed) + 1, reversed);
		return;
	}
	decToBinRec(dec, dest);
}

int pow(int base, int degree) {
	int result = 1;
	while (degree >= 1) {
		result *= base;
		degree--;
	}
	return result;
}

int powRec(int base, int degree) {
	int result = 1;
	if (degree >= 1)
		result = base * powRec(base, degree - 1);
	else
		return result;
}

int powRecSpeed(int base, int degree) {
	int result = 1;
	
	if (degree == 0)
		return result;
	if (degree % 2 == 0)
		result = powRecSpeed(base * base, degree / 2);
	else
		result = base * powRecSpeed(base, degree - 1);

	return result;
}

int countWays(int start, int end) {
	int ways = 0;
	int nodesBuf[CALC_TREE_MAX_NODES];
	nodesBuf[0] = end; // 20 in our case
	int nodesCount = 1;
	int tempBuf[CALC_TREE_MAX_NODES];

	while (nodesCount) {
		memcpy(&tempBuf, &nodesBuf, nodesCount * sizeof(int));
		int newNodesCount = 0;

		for (size_t i = 0; i < nodesCount; i++) {
			int node = tempBuf[i];
			
			if (node % 2 == 0) {
				int divNode = node / 2;
				if (divNode > start) {
					nodesBuf[newNodesCount] = divNode;
					newNodesCount++;
				}
				else if (divNode == start)
					ways++;
			}

			int addNode = node - 1;
			if (addNode > start) {
				nodesBuf[newNodesCount] = addNode;
				newNodesCount++;
			}
			else
				ways++;
		}

		nodesCount = newNodesCount;
	}
	
	return ways;
}

void countWaysRec(int start, int * nodesBuf, int * nodesCount, int * ways) {
	if (*nodesCount == 0)
		return;
	
	int tempBuf[CALC_TREE_MAX_NODES];
	memcpy(tempBuf, nodesBuf, sizeof(int) * (*nodesCount));

	int newNodesCount = 0;
	for (size_t i = 0; i < *nodesCount; i++) {
		int node = tempBuf[i];

		if (node % 2 == 0) {
			int divNode = node / 2;
			if (divNode > start) {
				nodesBuf[newNodesCount] = divNode;
				newNodesCount++;
			}
			else if (divNode == start)
				(*ways)++;
		}

		int addNode = node - 1;
		if (addNode > start) {
			nodesBuf[newNodesCount] = addNode;
			newNodesCount++;
		}
		else
			(*ways)++;
	}

	*nodesCount = newNodesCount;
	countWaysRec(start, nodesBuf, nodesCount, ways);
}


int main() {
	printf("Decimal to binary\n");
	char dest[DEC_TO_BIN_BUFFER_SIZE];
	dest[0] = 0;
	int testDec = 18;
	decToBinRec(testDec, dest);
	printf("%d: %s\n\n", testDec, dest);

	printf("Power without recursion\n");
	int testBase = 3, testDegree = 5;
	printf("%d in degree %d: %d\n\n", testBase, testDegree, pow(testBase, testDegree));
	printf("Power with recursion\n");
	printf("%d in degree %d: %d\n\n", testBase, testDegree, powRec(testBase, testDegree));
	printf("Power with recursion and speed\n");
	printf("%d in degree %d: %d\n\n", testBase, testDegree, powRecSpeed(testBase, testDegree));

	printf("Calculator +1 *2 without recursion\n");
	int testTarget = 20;
	int testStart = 3;
	printf("Ways from %d to %d: %d\n\n", testStart, testTarget, countWays(testStart, testTarget));
	printf("Calculator +1 *2 with recursion\n");
	int testBuf[CALC_TREE_MAX_NODES];
	testBuf[0] = testTarget;
	int testNodesCount = 1;
	int testWays = 0;
	countWaysRec(testStart, testBuf, &testNodesCount, &testWays);
	printf("Ways from %d to %d: %d\n", testStart, testTarget, testWays);

	return 0;
}