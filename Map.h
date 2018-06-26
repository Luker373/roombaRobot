//-------------------------------
// Map.h
// Header file for Map ADT
// Designed for use in Roomba Robot
// Lucas Hartlage - 2018
// ------------------------------

#ifndef _MAP_H_INCLUDE_
#define _MAP_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

// structs
typedef struct NodeObj* Node;
typedef struct MapObj* Map;

// constructors/destructors
Map newMap(void);
void freeMap(Map* pM);
Node newNode(int xC, int yC);
void freeNode(Node* pN);

// Access functions
int isEmpty(Map M);
int getSize(Map M);
int getNumObstacles(Map M);
int checkForObs(int xC, int yC, Map M);

// Manipulation functions
void moveFront(Map M);
void moveBack(Map M);
void deleteFront(Map M);
void addObstacle(int xC, int yC, Map M);

// Other functions
void printMap(FILE* out, Map M);

#endif