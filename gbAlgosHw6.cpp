// HW Lesson 6 Algorithms and Data Structures
// Author: Dmitry Selin

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
	int data;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
} Node;

unsigned int simpleHash(const char* str) {
	long result = 0;
	for (size_t i = 0; i < strlen(str); i++)
		result += str[i];
	return result;
}

void addElement(Node** root, int data) {
	if (*root == NULL) {
		(*root) = (Node*)malloc(sizeof(Node));
		(*root)->data = data;
		(*root)->parent = NULL;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return;
	}

	if (data < (*root)->data)
		addElement(&(*root)->left, data);
	else
		addElement(&(*root)->right, data);
}

void printTree(Node* root) {
	if (!root) {
		printf("N");
		return;
	}
	else
		printf("%d", root->data);

	printf("(");
	printTree(root->left);
	printf(", ");
	printTree(root->right);
	printf(")");
}

void traverseForward(Node* root) {
	if (!root)
		return;

	printf("%d ", root->data);
	traverseForward(root->left);
	traverseForward(root->right);
}

void traverseSymmetric(Node* root) {
	if (!root)
		return;

	traverseSymmetric(root->left);
	printf("%d ", root->data);
	traverseSymmetric(root->right);
}

void traverseBackward(Node* root) {
	if (!root)
		return;

	traverseBackward(root->left);
	traverseBackward(root->right);
	printf("%d ", root->data);
}

void deleteTree(Node* root) {
	if (root)
		return;

	deleteTree(root->left);
	deleteTree(root->right);
	free(root);
}

void findElement(Node* root, int value) {
	if (!root) {
		printf("not found");
		return;
	}
	
	printf("%d ", root->data);
	if (root->data == value) {
		printf("done");
		return;
	}

	if (value < root->data) {
		printf("left ");
		findElement(root->left, value);
	}
	else {
		printf("right ");
		findElement(root->right, value);
	}
}

int main() {
	const char* testStrings[] = {"", "a", "abc", "Hello", "World"};
	for (size_t i = 0; i < sizeof(testStrings) / sizeof(const char*); i++)
		printf("String: \"%s\", hash: %d\n", testStrings[i], simpleHash(testStrings[i]));
	
	printf("\nTree\n");
	Node* testRoot = NULL;
	addElement(&testRoot, 15);
	addElement(&testRoot, 10);
	addElement(&testRoot, 20);
	addElement(&testRoot, 3);
	addElement(&testRoot, 50);
	addElement(&testRoot, 100);
	addElement(&testRoot, 14);
	addElement(&testRoot, 25);
	printTree(testRoot);

	printf("\n\nTraverse forward\n");
	traverseForward(testRoot);

	printf("\n\nTraverse symmetric\n");
	traverseSymmetric(testRoot);

	printf("\n\nTraverse backward\n");
	traverseBackward(testRoot);

	printf("\n");
	int testElements[] = { 100, 14, 15, 3, 50, 4 };
	for (size_t i = 0; i < sizeof(testElements) / sizeof(int); i++) {
		printf("\nLooking for: %d\n", testElements[i]);
		findElement(testRoot, testElements[i]);
	}

	deleteTree(testRoot);
	return 0;
}