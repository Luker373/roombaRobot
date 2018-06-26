//-------------------------------
// Map.c
// Implementation file for Map ADT
// Designed for use in Roomba Robot
// Mucas Hartlage - 2018
// ------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "Map.h"

typedef struct NodeObj{
	int xCoor, yCoor;
	struct NodeObj* nextNode;
	struct NodeObj* prevNode;
} NodeObj;


// objects stored in following way:
// only obstacles are recorded in Map
// moving from left to right, xCoor increases until yCoor increments
// left to right, top to bottom
typedef struct MapObj{
	Node frontNode;
	Node backNode;
	Node cursorNode;
	int length;
	int cursorIndex;
} MapObj;

// CONSTRUCTORS AND DESTRUCTORS

Node newNode(int xC, int yC){
	Node N = malloc(sizeof(NodeObj));
	N->xCoor = xC;
	N->yCoor = yC;
	N->nextNode = NULL;
	N->prevNode = NULL;
	return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

Map newMap(void){
	Map M;
	M = malloc(sizeof(MapObj));
	M->frontNode = M->backNode = M->cursorNode = NULL;
	M->length = 0;
	M->cursorIndex = 0;
	return M;
}

// freeMap()
// Frees heap memory pointed to by *pM, sets *pM to NULL
void freeMap(Map* pM){
	if(pM != NULL && *pM != NULL){
		while((*pM)->length != 0)
			deleteFront(*pM)
		free(*pM);
		*pM = NULL;
	}
}

// ACCESS FUNCTIONS

// isEmpty(Map M)
// checks if M is empty or not
// 1 : Empty
// 0 : Non-empty
int isEmpty(Map M){
	if( M==NULL ){
      printf("Map Error: calling isEmpty() on NULL Map reference\n");
      exit(1);
    }
    return(M->length == 0);
}

// getSize(Map M)
// returns the length of a side of the smallest square required to hold all elements in M
int getSize(Map M){
	if( M==NULL ){
      printf("Map Error: calling getSize() on NULL Map reference\n");
      exit(1);
    }

    moveFront(M);
    int xMin, xMax, yMin, yMax;

    xMin = M->cursorNode->xCoor;
    yMin = M->cursorNode->yCoor;

    while(M->cursorIndex->nextNode != NULL){
        if(M->cursorNode->xCoor > xMax)
            xMax = M->cursorNode->xCoor;
        moveNext(M);
    }
    yMax = M->cursorNode->yCoor;
    
    if(yMax - yMin > xMax - xMin)
        return (yMax - yMin);
    else
        return (xMax - xMin);
}

int getNumObstacles(Map M){
	if( M==NULL ){
      printf("Map Error: calling getNumObstacles() on NULL Map reference\n");
      exit(1);
    }
    return(M->length);
}

int checkForObs(int xC, int yC, Map M){
    if( M==NULL ){
      printf("Map Error: calling checkForObs() on NULL Map reference\n");
      exit(1);
    }
    moveFront(M);
    while(M->cursorIndex > -1 && M->cursorNode->yCoor <= yC && M->cursorNode->xCoor != xC)
        moveNext(M);
    if(M->cursorNode->yCoor == yC && M->cursorNode->xCoor == xC)
        return 1;
    else
        return 0;
}

// Manipulation functions
void moveFront(Map M){
	if(M == NULL){
      printf("Map Error: calling moveFront() on NULL Map reference\n");
      exit(1);
    }
    M->cursorNode = M->frontNode;
    if(!isEmpty(M))
    	M->cursorIndex = 0;
    else
        M->cursorIndex = -1;
}

// movePrev()
// moves cursor element to element before current cursor element
void movePrev(Map M){
   if(M == NULL){
      printf("Map Error: calling movePrev() on NULL Map reference\n");
      exit(1);
   }
   if(M->cursorNode->prevNode == NULL){
      M->cursorNode = NULL;
      M->cursorIndex = -1;
      return;
   }
   if(M->length > 0){
      M->cursorNode = M->cursorNode->prevNode;
      M->cursorIndex--;
   }
}

// moveNext()
// moves cursor to element after current cursor element
void moveNext(Map M){
   if(M == NULL){
      printf("Map Error: calling moveNext() on NULL Map reference\n");
      exit(1);
   }
   if(M->cursorNode->nextNode == NULL){
      M->cursorNode = NULL;
      M->cursorIndex = -1;
      return;
   }
   if(M->length > 0){
      M->cursorNode = M->cursorNode->nextNode;
      M->cursorIndex++;
   }
}

// deleteFront()
// Deletes element at front of M
// Pre: !isEmpty(M)
void deleteFront(Map M){
   Node N = NULL;
   if( M==NULL ){
      printf("Map Error: calling deleteFront() on NULL Map reference\n");
      exit(1);
   }
   if( isEmpty(M) ){
      printf("Map Error: calling deleteFront() on an empty Map\n");
      exit(1);
   }
   N = M->frontNode;
   if( length(M)>1 ) { 
      M->frontNode = M->frontNode->nextNode; 
   }else{ 
      M->frontNode = M->backNode = NULL;
   }
   if(M->cursorIndex == 0){
      M->cursorNode = NULL;
      M->cursorIndex = -1;
   }else
      M->cursorIndex--;
   M->length--;
   freeNode(&N);
}

void addObstacle(int xC, int yC, Map M){
	if( M==NULL ){
      printf("Map Error: calling addObstacle() on NULL Map reference\n");
      exit(1);
    }
    moveFront(M);
    if(M->cursorIndex == -1){
        M->frontNode = M->backNode = newNode(xC, yC);
        return;
    }
    while(M->cursorNode->yCoor <= yC && M->cursorNode->xCoor <= xC)
        moveNext(M);
    Node N = newNode(xC, yC);

    N->prevNode = M->cursorNode->prevNode;
    N->nextNode = M->cursorNode;

    M->cursorNode->prevNode->nextNode = N;
    M->cursorNode->prevNode = N;

    M->length++;
    M->cursorIndex++;
}

// Other functions
void printMap(FILE* out, Map M);











