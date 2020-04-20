#include <stdio.h>
#include <stdlib.h>
#include "dynamicVector.h"

struct Vector
{
	int *vectorArray;
	size_t initialSize;
	size_t numOfElements;
	size_t blockSize;
};

/* CREATE VECTOR */

Vector* VectorCreate(size_t _initialSize, size_t _blockSize)
{
	Vector *vector;
	int *vectorArray;

	if(0 == _initialSize || 0 == _blockSize)
	{
		return NULL;
	}

	vector = (Vector*)malloc(sizeof(Vector));

	if(NULL == vector)
	{
		return NULL;
	}
	
	vectorArray = (int*)calloc(_initialSize,sizeof(int));

	if(NULL == vectorArray)
	{
		free(vector);
		vector = NULL;

		return NULL;
	}

	vector->vectorArray = vectorArray;
	vector->initialSize = _initialSize;
	vector->numOfElements = 0;
	vector->blockSize = _blockSize;

	return vector;
}

/* DESTROY VECTOR */

void VectorDestroy(Vector* _vec)
{
	if(NULL != _vec)
	{
		free(_vec->vectorArray);

		free(_vec);
	}
}

/* INSERT ELEMENT */

static int * ReSizeVector(int *_vectorArray, size_t _newSize)
{
	_vectorArray = (int*)realloc(_vectorArray,_newSize*sizeof(int));

	return _vectorArray;
}

ErrCode VectorAddTail(Vector* _vec, int _data)
{
	int *vectorArray;

	if(NULL == _vec)
	{
		return ERR_NOT_EXIST;
	}

	++_vec->numOfElements;

	if(_vec->initialSize <= _vec->numOfElements)
	{
		vectorArray = ReSizeVector(_vec->vectorArray,_vec->initialSize += _vec->blockSize);

		if(NULL == vectorArray)
		{
			return ERR_OVERFLOW;
		}
		
		_vec->vectorArray = vectorArray;
	}

	_vec->vectorArray[_vec->numOfElements] = _data;

	return SUCCEEDED;
}

/* REMOVE ELEMENT */

ErrCode VectorRemoveTail(Vector* _vec, int* _data)
{
	int *vectorArray;

	if(NULL == _vec)
	{
		return ERR_NOT_EXIST;
	}

	if(0 > _vec->numOfElements)
	{
		return EMPTY_VECTOR_ARR;	
	}

	(*_data) = _vec->vectorArray[_vec->numOfElements--];

	if((_vec->initialSize - _vec->numOfElements) >= (_vec->blockSize*2))
	{
		vectorArray = ReSizeVector(_vec->vectorArray,_vec->initialSize -= _vec->blockSize);

		if(NULL == vectorArray)
		{
			return ERR_FAILED;
		}
		
		_vec->vectorArray = vectorArray;
	}

	return SUCCEEDED;
}

/* INSERT ELEMENT BY INDX */

ErrCode VectorSet(Vector* _vec, size_t _indx, int _data)
{
	if(NULL == _vec)
	{
		return ERR_NOT_EXIST;
	}

	if(1 > _indx || _vec->numOfElements < _indx)
	{
		return ERR_ILLEGAL_INPUT;
	}

	_vec->vectorArray[_indx] = _data;

	return SUCCEEDED;
}

/* REMOVE ELEMENT BY INDX */

ErrCode VectorGet(Vector* _vec, size_t _indx, int* _data)
{
	ErrCode err;
	int saveLast;

	if(NULL == _vec)
	{
		return ERR_NOT_EXIST;
	}

	err = VectorRemoveTail(_vec,&saveLast);

	if(SUCCEEDED != err)
	{
		return err;
	}

	(*_data) = _vec->vectorArray[_indx];
	VectorSet(_vec,_indx,saveLast);

	return SUCCEEDED;
}

/* FIND ELEMENT POSITION */

static size_t searchIndex(Vector* _vec,  int _data)
{
	size_t i;

	for(i = 1;i <= _vec->numOfElements;++i)
	{
		if(_data == _vec->vectorArray[i])
		{
			return i;
		}
	}

	return 0;
}

size_t VectorFind(Vector* _vec,  int _data)
{

	if(NULL == _vec)
	{
		return 0;
	}

	return searchIndex(_vec,_data);
}

/* PRINT VECTOR */

ErrCode PrintArray(Vector *_vec)
{
	int i;

	if(NULL == _vec)
	{
		return ERR_NOT_EXIST;
	}

	printf("number of elements: %ld\n",_vec->numOfElements);
	printf("vector array size: %ld\n",_vec->initialSize);
	printf("vector array block size: %ld\n",_vec->blockSize);

	printf("vector array values: \n");

	for(i = 1;i <= _vec->numOfElements;++i)
	{
		printf("%d ",_vec->vectorArray[i]);
	}
	
	printf("\n");

	return SUCCEEDED;
}


