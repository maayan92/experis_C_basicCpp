#include <stdio.h>
#include <stdlib.h>
#include "dynamicVector.h"

struct Vector
{
	size_t m_MagicNumber;
	int *m_vectorArray;
	size_t m_initialSize;
	size_t m_arrSize;
	size_t m_numOfElements;
	size_t m_blockSize;
};

/* CREATE VECTOR */

Vector* VectorCreate(size_t _initialSize, size_t _blockSize)
{
	Vector *vector;
	int *vectorArray;

	if(0 == _initialSize && 0 == _blockSize)
	{
		return NULL;
	}

	vector = (Vector*)malloc(sizeof(Vector));

	if(NULL == vector)
	{
		return NULL;
	}
	
	vectorArray = (int*)calloc(_initialSize+1,sizeof(int));

	if(NULL == vectorArray)
	{
		free(vector);
		vector = NULL;

		return NULL;
	}

	vector->m_vectorArray = vectorArray;
	vector->m_initialSize = _initialSize+1;
	vector->m_arrSize = _initialSize+1;
	vector->m_numOfElements = 0;
	vector->m_blockSize = _blockSize;
	vector->m_MagicNumber = MAGIC_NUMBER;

	return vector;
}

/* DESTROY VECTOR */

void VectorDestroy(Vector* _vec)
{
	if(NULL != _vec && _vec->m_MagicNumber == MAGIC_NUMBER)
	{
		_vec->m_MagicNumber = NO_MAGIC_NUMBER;

		free(_vec->m_vectorArray);

		free(_vec);
	}
}

/* INSERT ELEMENT */

static int * ReSizeVector(int *_vectorArray, size_t _newSize)
{
	_vectorArray = (int*)realloc(_vectorArray,(_newSize+1)*sizeof(int));

	return _vectorArray;
}

ErrCode VectorAddTail(Vector* _vec, int _data)
{
	int *vectorArray;

	if(NULL == _vec || _vec->m_MagicNumber != MAGIC_NUMBER)
	{
		return ERR_NOT_INITIALIZE;
	}

	++_vec->m_numOfElements;

	if(_vec->m_arrSize == _vec->m_numOfElements)
	{
		vectorArray = ReSizeVector(_vec->m_vectorArray,_vec->m_arrSize += _vec->m_blockSize);

		if(NULL == vectorArray)
		{
			return ERR_OVERFLOW;
		}
		
		_vec->m_vectorArray = vectorArray;
	}

	_vec->m_vectorArray[_vec->m_numOfElements] = _data;

	return SUCCEEDED;
}

/* REMOVE ELEMENT */

ErrCode VectorRemoveTail(Vector* _vec, int* _data)
{
	int *vectorArray;

	if(0 == VectorNumOfelements(_vec))
	{
		return ERR_NOT_INITIALIZE;	
	}

	*_data = _vec->m_vectorArray[_vec->m_numOfElements--];

	if((_vec->m_arrSize - _vec->m_numOfElements) >= (_vec->m_blockSize*2) && (_vec->m_arrSize - _vec->m_blockSize) >= _vec->m_initialSize)
	{
		vectorArray = ReSizeVector(_vec->m_vectorArray,_vec->m_arrSize -= _vec->m_blockSize);

		if(NULL == vectorArray)
		{
			return ERR_FAILED;
		}
		
		_vec->m_vectorArray = vectorArray;
	}

	return SUCCEEDED;
}

/* INSERT ELEMENT BY INDX */

ErrCode VectorSet(Vector* _vec, size_t _indx, int _data)
{
	if(NULL == _vec || _vec->m_MagicNumber != MAGIC_NUMBER)
	{
		return ERR_NOT_INITIALIZE;
	}

	if(0 == _indx || _vec->m_numOfElements < _indx)
	{
		return ERR_ILLEGAL_INPUT;
	}

	_vec->m_vectorArray[_indx] = _data;

	return SUCCEEDED;
}

/* REMOVE ELEMENT BY INDX */

ErrCode VectorGet(Vector* _vec, size_t _indx, int* _data)
{

	if(NULL == _vec || _vec->m_MagicNumber != MAGIC_NUMBER)
	{
		return ERR_NOT_INITIALIZE;
	}

	if(0 == _indx || _vec->m_numOfElements < _indx)
	{
		return ERR_ILLEGAL_INPUT;
	}

	*_data = _vec->m_vectorArray[_indx];

	return SUCCEEDED;
}

/* FIND ELEMENT POSITION */

static size_t searchIndex(Vector* _vec,  int _data)
{
	size_t i;

	for(i = 1;i <= _vec->m_numOfElements;++i)
	{
		if(_data == _vec->m_vectorArray[i])
		{
			return i;
		}
	}

	return 0;
}

size_t VectorFind(Vector* _vec,  int _data)
{
	
	if(NULL == _vec || _vec->m_MagicNumber != MAGIC_NUMBER)
	{
		return 0;
	}

	return searchIndex(_vec,_data);
}

/* PRINT VECTOR */

ErrCode PrintArray(Vector *_vec)
{
	int i;

	if(NULL == _vec || _vec->m_MagicNumber != MAGIC_NUMBER)
	{
		return ERR_NOT_INITIALIZE;
	}

	printf("number of elements: %ld\n",_vec->m_numOfElements);
	printf("initial size: %ld\n",_vec->m_initialSize);
	printf("size: %ld\n",_vec->m_arrSize);
	printf("block size: %ld\n",_vec->m_blockSize);

	printf("values: \n");

	for(i = 1;i <= _vec->m_numOfElements;++i)
	{
		printf("%d ",_vec->m_vectorArray[i]);
	}
	
	printf("\n");

	return SUCCEEDED;
}

size_t VectorNumOfelements(Vector* _vec)
{
	if(NULL == _vec || _vec->m_MagicNumber != MAGIC_NUMBER)
	{
		return 0;
	}
	
	return _vec->m_numOfElements;
}



