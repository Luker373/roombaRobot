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
Map newMap(int );
void freeMap(Map* pM);

// Access functions
int isEmpty(Map m);
int getSize(Map m);
int getNumObstacles(Map m);

// Manipulation functions


// Other functions
void printMap(FILE* out, Map m);

#endif