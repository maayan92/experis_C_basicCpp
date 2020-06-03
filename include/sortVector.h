#ifndef __SORT_VECTOR__
#define __SORT_VECTOR__

#include "vector.h"

typedef enum { false,true }Bool;

void BubbleSort(Vector* _vec, Bool(*ptrIfToSwap)(void*,void*));



#endif
