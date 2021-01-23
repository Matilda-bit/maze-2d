#include <stdio.h>
#include <stdlib.h>

#define COL 5
#define ROW 7

#define EMPTY -1
#define MAX COL*ROW*2


// the function pathSearch(...) using recursion to find the path to an exit point E
// storing by steps the coordinate x and y into the queue
// and print them out if the exit point was found

struct queue{
    int* items;
    int front;
    int count;
    int maxSize;
};

char maze[ROW][COL] = {
        {'*','*','*','E','*'},
        {'*',' ',' ',' ','*'},
        {'*',' ','*','*','*'},
        {'*',' ',' ',' ','E'},
        {'*',' ','*','*','*'},
        {'*',' ','*','*','*'},
        {'*','*','*','*','*'}
};

int sol[ROW][COL];
int startX = 1, startY = 5;

void init(struct queue* qPtr);
int enqueue(struct queue* qPtr, int val);
int dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
void printSolution();
void printMaze();
int pathSearch(int x, int y, struct queue* qPtr);


int main(){
    int i,j;
    struct queue* MyQueuePtr = (struct queue*)malloc(sizeof(struct queue));
    init(MyQueuePtr);
    //put zeros to solution matrix
    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            sol[i][j] = 0;
        }
    }
    printMaze();

    if (pathSearch(startX,startY,MyQueuePtr)){
        printSolution();
    }
    else
        printf("Тo way out!\n");
    return 0;
}


void init(struct queue* qPtr){
    qPtr->items = (int*)malloc(sizeof(int)*MAX);
    qPtr->front = 0;
    qPtr->count = 0;
    qPtr->maxSize = MAX;
}


int enqueue(struct queue* q, int val){
    int i;
    if(q->count != q->maxSize){
        q->items[(q->front+q->count)%q->maxSize] = val;
        (q->count)++;
        return 1;
    }
    else{
        q->items = realloc(q->items, (q->maxSize)*sizeof(int)*2);
        for(i=0; i<=q->front-1; i++){
            q->items[i + q->maxSize] = q->items[i];
        }
        q->items[i+q->maxSize] = val;
        (q->maxSize) *= 2;
        (q->count)++;

        return 1;
    }
}

int dequeue(struct queue* qPtr) {
    int val;
    if (qPtr->count == 0)
        return EMPTY;
    val = qPtr->items[qPtr->front];
    qPtr->front = (qPtr->front + 1)% qPtr->maxSize;

    (qPtr->count)--;

    return val;
}

int empty(struct queue* qPtr){
    return qPtr->count == 0;
}

void printSolution(){
    int i,j;
    printf("\n\n\n");
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            printf("%d\t",sol[i][j]);
        }
        printf("\n\n");
    }
}


void printMaze(){
    int i,j;
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            if(i==startY && j==startX){
                printf("@\t");
            }
            else{
                printf("%c\t",maze[i][j]);
            }
        }
        printf("\n\n");
    }
    printf("\n\n");
}


int pathSearch(int x, int y, struct queue* qPtr){

    if(maze[y][x]=='E'){
        sol[y][x] = 1;
        enqueue(qPtr, y);
        enqueue(qPtr, x);
        //print solution
        while (!empty(qPtr)){
            int num1 = dequeue(qPtr);
            int num2 = dequeue(qPtr);
            printf("%d, %d;\t", num1, num2);
        }
        printf("\n");
        //printf("%d , %d;\t", x,y);

        return 1;
    }

    if(x>=0 && y>=0 && x<COL && y<ROW && sol[y][x] == 0 && maze[y][x] == ' '){
        sol[y][x] = 1;
        enqueue(qPtr, y);
        enqueue(qPtr, x);

        //right
        if(pathSearch(x + 1, y,qPtr)){
            //printf("%d , %d;\t", x,y);
            return 1;
        }

        //down
        if(pathSearch(x, y+1,qPtr)){
            //printf("%d , %d;\t", x,y);
            return 1;
        }

        //left
        if(pathSearch(x-1, y,qPtr)){
            //printf("%d , %d;\t", x,y);
            return 1;
        }

        //up
        if(pathSearch(x, y-1,qPtr)){
            //printf("%d , %d;\t", x,y);
            return 1;
        }

        //backtracking
        sol[y][x] = 0;
        return 0;
    }
    return 0;
}
