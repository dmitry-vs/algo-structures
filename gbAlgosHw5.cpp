// HW Lesson 5 Algorithms and Data Structures
// Author: Dmitry Selin

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define T char

typedef struct Node {
	T data;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
	int size;
} Stack;

typedef struct {
	Node* head;
	Node* tail;
} Queue;

bool pushStack(Stack* st, T val) {
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
		return false;

	temp->data = val;
	temp->next = st->head;
	st->head = temp;
	st->size++;
	return true;
}

T popStack(Stack* st) {
	if (st->size == 0)
		return -1;
	
	T result = st->head->data;
	Node* temp = st->head;
	st->head = st->head->next;
	free(temp);
	st->size--;
	return result;
}

void decToBinStk(int dec) {
	Stack s;
	s.size = 0;
	s.head = NULL;
	int temp = dec;

	do {
		pushStack(&s, temp % 2 == 0 ? '0' : '1');
		temp = temp / 2;
	} while (temp > 0);

	while (s.size > 0)
		printf("%c", popStack(&s));
}

bool checkBraces(const char* str) {
	Stack circleBraces;
	circleBraces.size = 0;
	circleBraces.head = NULL;
	Stack squareBraces;
	squareBraces.size = 0;
	squareBraces.head = NULL;
	Stack curlyBraces;
	curlyBraces.size = 0;
	curlyBraces.head = NULL;

	T dummy = 0;
	T popOk = 1;
	for (size_t i = 0; i < strlen(str); i++) {
		popOk = 1;
		if (str[i] == '(')
			pushStack(&circleBraces, dummy);
		else if (str[i] == '[')
			pushStack(&squareBraces, dummy);
		else if (str[i] == '{')
			pushStack(&curlyBraces, dummy);
		else if (str[i] == ')')
			popOk = popStack(&circleBraces);
		else if (str[i] == ']')
			popOk = popStack(&squareBraces);
		else if (str[i] == '}')
			popOk = popStack(&curlyBraces);
		else
			continue;

		if (popOk == -1)
			return false;
	}

	if (circleBraces.size != 0 || squareBraces.size != 0 || curlyBraces.size != 0)
		return false;
	
	return true;
}

void printList(Node* head) {
	Node* current = head;

	while(true) {
		printf("%c ", current->data);
		if (current->next == NULL)
			break;
		current = current->next;
	}
}

void freeList(Node* head) {
	Node* current = head;

	while (true) {
		Node* temp = current;
		current = current->next;
		free(temp);
		if (current == NULL)
			break;
	}
}

Node* copyList(Node* head) {
	Node* resultHead = NULL;
	Node* resultLast = resultHead;
	Node* srcCurrent = head;

	while (srcCurrent) {
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->data = srcCurrent->data;
		temp->next = NULL;

		if (resultLast)
			resultLast->next = temp;
		resultLast = temp;
		if (!resultHead)
			resultHead = resultLast;

		srcCurrent = srcCurrent->next;
	}

	return resultHead;
}

bool pushQueue(Queue* q, T val) {
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
		return false;
	temp->data = val;
	temp->next = NULL;
	
	if (q->tail)
		q->tail->next = temp;
	
	q->tail = temp;
	if (!q->head)
		q->head = temp;

	return true;
}

T popQueue(Queue* q) {
	if (q->head == NULL)
		return -1;

	T result = q->head->data;
	Node* temp = q->head;
	if (q->tail == q->head) {
		q->head = NULL;
		q->tail = NULL;
	}
	else
		q->head = q->head->next;
	free(temp);

	return result;
}

int main() {
	printf("Dec to bin with stack\n");
	int testDec = 12;
	printf("Decimal: %d, binary: ", testDec);
	decToBinStk(testDec);

	Stack s1;
	s1.size = 0;
	s1.head = NULL;
	// loop below consumes all memory
	while (true) {
		if (pushStack(&s1, 'a') == false) {
			printf("\nOut of memory\n");
			break;
		}
	}
	
	printf("\n\nCheck braces\n");
	const char* testStrs[] = { "()", "([])()", "{}()", "([{}])", ")(", "())({)", "(", "])})", "([(])", "", "123*abc" };
	for (size_t i = 0; i < sizeof(testStrs) / sizeof(const char*); i++)
		printf("%8s: %d\n", testStrs[i], checkBraces(testStrs[i]));


	Node * testElement1 = (Node*)malloc(sizeof(Node));
	testElement1->data = 'a';
	Node* testElement2 = (Node*)malloc(sizeof(Node));
	testElement2->data = 'b';
	Node* testElement3 = (Node*)malloc(sizeof(Node));
	testElement3->data = 'c';
	testElement1->next = testElement2;
	testElement2->next = testElement3;
	testElement3->next = NULL;
	printf("\nOriginal list: ");
	printList(testElement1);
	Node* testCopyList = copyList(testElement1);
	printf("\nCopied list: ");
	printList(testCopyList);
	freeList(testElement1);
	freeList(testCopyList);

	Queue q;
	q.head = NULL;
	q.tail = NULL;
	pushQueue(&q, 'a');
	pushQueue(&q, 'b');
	pushQueue(&q, 'c');
	pushQueue(&q, 'd');

	printf("\n\nQueue:\n");
	while (true) {
		T test = popQueue(&q);
		if (test == -1)
			break;
		printf("%c ", test);
	}
	
	return 0;
}