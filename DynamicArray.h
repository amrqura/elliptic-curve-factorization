/*
 * DynamicArray.h
 *
 *  Created on: May 7, 2014
 *      Author: amrqura
 */

#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_
#include <stdio.h>
#include <stdlib.h>
#include "CommonUtils.h"
typedef struct {
  int *array;
  size_t used;
  size_t size;
  int usedSize;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
  a->usedSize++;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}


int getLocation(Array *a,int lenght , int item)
{

	for(i=0;i<lenght;i++)
		if(a->array[i]==item)
			return i;
	return -1;
}
#endif /* DYNAMICARRAY_H_ */
