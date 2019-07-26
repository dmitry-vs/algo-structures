// HW Lesson 7 Algorithms and Data Structures
// Author: Dmitry Selin

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
	int size;
} Stack;

bool pushStack(Stack* st, int val) {
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
		return false;

	temp->data = val;
	temp->next = st->head;
	st->head = temp;
	st->size++;
	return true;
}

int popStack(Stack* st) {
	if (st->size == 0)
		return -1;

	int result = st->head->data;
	Node* temp = st->head;
	st->head = st->head->next;
	free(temp);
	st->size--;
	return result;
}

bool stackEmpty(Stack* st) {
	return st->size == 0;
}

typedef struct {
	Node* head;
	Node* tail;
} Queue;

bool pushQueue(Queue* q, int val) {
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

int popQueue(Queue* q) {
	if (q->head == NULL)
		return -1;

	int result = q->head->data;
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

bool queueEmpty(Queue* q) {
	return q->head == NULL;
}

const int GRAPH_VERTEX_COUNT = 6;

const int GRAPH[GRAPH_VERTEX_COUNT][GRAPH_VERTEX_COUNT] = {
	{0, 1, 0, 0, 1, 0},
	{1, 0, 1, 1, 0, 0},
	{0, 1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1, 0}
};

void printGraph() {
	for (int i = 0; i < GRAPH_VERTEX_COUNT; i++) {
		for (int j = 0; j < GRAPH_VERTEX_COUNT; j++)
			printf("%d ", GRAPH[i][j]);
		printf("\n");
	}
}

int visitedVertexesCount = 0;
int visitedVertexesList[GRAPH_VERTEX_COUNT];

void setVertexVisited(int index) {
	visitedVertexesList[visitedVertexesCount] = index;
	visitedVertexesCount++;
}

bool isVertexVisited(int index) {
	for (size_t i = 0; i < visitedVertexesCount; i++)
		if (visitedVertexesList[i] == index)
			return true;
	return false;
}

Stack* getChildren(int index) {
	if (index < 0 || index >= GRAPH_VERTEX_COUNT)
		return NULL;

	Stack* result = (Stack*)malloc(sizeof(Stack));
	result->size = 0;
	result->head = NULL;

	for (int i = 0; i < GRAPH_VERTEX_COUNT; i++)
		if (GRAPH[index][i] != 0)
			pushStack(result, i);

	return result;
}

Queue * vertexQueue;

bool widthTraverse(int startIndex) {
	if (startIndex < 0 || startIndex >= GRAPH_VERTEX_COUNT)
		return false;
	
	pushQueue(vertexQueue, startIndex);
	setVertexVisited(startIndex);
	
	while (!queueEmpty(vertexQueue)) {
		int current = popQueue(vertexQueue);
		printf("%d ", current);

		Stack* children = getChildren(current);
		while (children->size != 0) {
			int childIndex = popStack(children);
			if (isVertexVisited(childIndex) == true)
				continue;
			
			pushQueue(vertexQueue, childIndex);
			setVertexVisited(childIndex);
		}
		free(children);
	}

	return true;
}

bool depthTraverse(int startIndex, int prevIndex = -1) {
	if (startIndex < 0 || startIndex >= GRAPH_VERTEX_COUNT)
		return false;

	printf("%d ", startIndex);
	if (!isVertexVisited(startIndex))
		setVertexVisited(startIndex);
	
	Stack* children = getChildren(startIndex);
	while (children->size) {
		int nextIndex = popStack(children);
		if(nextIndex != prevIndex)
			depthTraverse(nextIndex, startIndex);
	}
	free(children);

	if(visitedVertexesCount != GRAPH_VERTEX_COUNT)
		printf("%d ", prevIndex);

	return true;
}

// Lee algorithm
const int w = 7;
const int h = 7;
const int OBSTACLE = -1;
const int UNVISITED = -2;
int grid[h][w];
int len;
int pointX[h * w];
int pointY[h * w];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void initGrid() {
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			grid[i][j] = UNVISITED;
}

void printGrid() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			printf("%2d ", grid[i][j]);
		printf("\n");
	}
	printf("\n");
}

void initPath(int sx, int sy) {
	for (size_t i = 0; i < sizeof(pointX) / sizeof(int); i++)
		pointX[i] = -1;
	for (size_t i = 0; i < sizeof(pointY) / sizeof(int); i++)
		pointY[i] = -1;
	pointX[0] = sx;
	pointY[0] = sy;
}

void printPath() {
	int index = 0;
	
	for (int i = 0; i < sizeof(pointX) / sizeof(int); i++)
	{
		if (pointX[i] < 0)
			break;
		printf("(%d, %d) ", pointX[i], pointY[i]);
	}
	printf("\n");
}

int lee(int sx, int sy, int ex, int ey) {
	int x, y, vector, dist, stop;
	if (sx == ex && sy == ey)
		return 0;
	if (grid[sy][sx] == OBSTACLE || grid[ey][ex] == OBSTACLE)
		return 0;

	dist = 0;
	grid[sy][sx] = dist;
	do
	{
		stop = 1;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				if (grid[y][x] == dist) {
					for (vector = 0; vector < 4; vector++) {
						int nextX = x + dx[vector];
						int nextY = y + dy[vector];
						if (nextX >= 0 && nextX < w &&
							nextY >= 0 && nextY < w &&
							grid[nextY][nextX] == UNVISITED) {
							stop = 0;
							grid[nextY][nextX] = dist + 1;
						}
					}
				}
			}
		}
		dist++;
	} while (!stop && grid[ey][ex] == UNVISITED);

	if (grid[ey][ex] == UNVISITED)
		return 0;

	len = grid[ey][ex];
	x = ex;
	y = ey;
	while (dist > 0) {
		pointX[dist] = x;
		pointY[dist] = y;
		dist--;

		for (vector = 0; vector < 4; vector++) {
			int nextX = x + dx[vector];
			int nextY = y + dy[vector];
			if (nextX >= 0 && nextX < w &&
				nextY >= 0 && nextY < h &&
				grid[nextY][nextX] == dist) {
				x = nextX;
				y = nextY;
			}
		}
	}

	return 1;
}

int main() {
	printf("Graph:\n");
	printGraph();
	printf("\nWidth traverse:\n");
	vertexQueue = (Queue*)malloc(sizeof(Queue));
	vertexQueue->head = NULL;
	vertexQueue->tail = NULL;
	int testStartIndex = 4;
	widthTraverse(testStartIndex);
	free(vertexQueue);
	visitedVertexesCount = 0;

	printf("\n\nDepth traverse:\n");
	depthTraverse(testStartIndex);
	printf("\n");

	printf("\nLee algorithm:\n");
	int testSx = 1, testSy = 2, testEx = 5, testEy = 4;
	initGrid();
	grid[2][3] = OBSTACLE;
	grid[3][3] = OBSTACLE;
	grid[4][3] = OBSTACLE;
	initPath(testSx, testSy);
	lee(testSx, testSy, testEx, testEy);
	printGrid();
	printf("Path:\n");
	printPath();
}