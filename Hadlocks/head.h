#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1
#define GRID 10
#define STACK_INIT_SIZE GRID*GRID
#define STACKINCREMENT 10
#define MPL 50
#define INCIDENCE 1

#define TX 4
#define TY 5
#define SX 1
#define SY 1

typedef int Status;

typedef struct Vertex{
	int x, y;
	int pre_x, pre_y;
}Vertex;

typedef struct{
	Vertex *base;
	Vertex *top;
	int stacksize;
}Stack;

Status InitStack(Stack &S);
Status StackEmpty(Stack &S);
Status GetTop(Stack &S, Vertex &v);
Status Push(Stack &S, Vertex v);
Status Pop(Stack &S, Vertex &v);
Status CopyStack(Stack &S1, Stack &S2);
Status ClearStack(Stack &S);

bool is_blocked(int x, int y, int **obstacle);
bool p_or_n(Vertex u, Vertex v);
Status Hadlock();
int **retrace(Vertex u, int len, Stack visit);
void visualization(int **p, int len, Stack v, int visual[][GRID]);

int **auto_gen();