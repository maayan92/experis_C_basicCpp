#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define VEC_MAGIC_NUMBER 0xbeefbeee

#define IS_NOT_EXIST(_que) (NULL == _que || (*_que).m_MagicNumber != VEC_MAGIC_NUMBER)
#define SWAP(_a,_b) { void *temp = _a; _a = _b; _b = temp; }

struct Vector
{
	size_t m_MagicNumber;
	void** m_vectorArray;
	size_t m_initialSize;
	size_t m_arrSize;
	size_t m_numOfElements;
	size_t m_blockSize;
};

/*resize the vector*/
static void** ReSizeVector(void** _vectorArray, size_t _newSize);
/*search the index of _data in the vector*/
static size_t searchIndex(const Vector* _vec,  void* _data);

/* CREATE VECTOR */

Vector* VectorCreate(size_t _initialSize, size_t _blockSize)
{
	Vector *vector;
	void** vectorArray;

	if(0 == _initialSize && 0 == _blockSize)
	{
		return NULL;
	}

	vector = (Vector*)malloc(sizeof(Vector));

	if(NULL == vector)
	{
		return NULL;
	}
	
	vectorArray = (void**)calloc(_initialSize+1,sizeof(void*));

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
	vector->m_MagicNumber = VEC_MAGIC_NUMBER;

	return vector;
}

/* DESTROY VECTOR */

void VectorDestroy(Vector* _vec, void(*ptrDestroy)(void*))
{
	int i;
	
	if(!IS_NOT_EXIST(_vec))
	{
		if(NULL != ptrDestroy)
		{
			for(i = 1; i <= _vec->m_numOfElements;++i)
			{
				(*ptrDestroy)(_vec->m_vectorArray[i]);
			}		
		}
		
		free(_vec->m_vectorArray);
		_vec->m_MagicNumber = 0;

		free(_vec);
	}
}

/* INSERT ELEMENT */

ErrCode VectorAddTail(Vector* _vec, void* _data)
{
	void** vectorArray;

	if(IS_NOT_EXIST(_vec))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(NULL == _data)
	{
		return ERR_ILLEGAL_INPUT;
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

ErrCode VectorRemoveTail(Vector* _vec, void** _data)
{
	void** vectorArray;

	if(IS_NOT_EXIST(_vec) || 0 == VectorNumOfelements(_vec))
	{
		return ERR_NOT_INITIALIZE;	
	}
	
	if(NULL == _data)
	{
		return ERR_ILLEGAL_INPUT;
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

ErrCode VectorSet(Vector* _vec, size_t _indx, void* _data)
{
	if(IS_NOT_EXIST(_vec))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(NULL == _data)
	{
		return ERR_ILLEGAL_INPUT;
	}

	if(0 == _indx || _vec->m_numOfElements < _indx)
	{
		return ERR_ILLEGAL_INPUT;
	}

	_vec->m_vectorArray[_indx] = _data;

	return SUCCEEDED;
}

/* REMOVE ELEMENT BY INDX */

ErrCode VectorGet(Vector* _vec, size_t _indx, void** _data)
{
	if(IS_NOT_EXIST(_vec))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(0 == _indx || _vec->m_numOfElements < _indx || NULL == _data)
	{
		return ERR_ILLEGAL_INPUT;
	}

	*_data = _vec->m_vectorArray[_indx];

	return SUCCEEDED;
}

/* FIND ELEMENT POSITION */

size_t VectorFind(const Vector* _vec,  void* _data)
{
	if(IS_NOT_EXIST(_vec))
	{
		return 0;
	}

	return searchIndex(_vec,_data);
}

/* PRINT VECTOR */

ErrCode PrintArray(const Vector *_vec, void(*ptrPrint)(void*))
{
	int i;

	if(IS_NOT_EXIST(_vec))
	{
		return ERR_NOT_INITIALIZE;
	}
	
	if(NULL == ptrPrint)
	{
		return ERR_ILLEGAL_INPUT;
	}

	for(i = 1;i <= _vec->m_numOfElements;++i)
	{
		(*ptrPrint)(_vec->m_vectorArray[i]);
	}

	return SUCCEEDED;
}

size_t VectorNumOfelements(const Vector* _vec)
{
	if(IS_NOT_EXIST(_vec))
	{
		return 0;
	}
	
	return _vec->m_numOfElements;
}

void BubbleSort(Vector* _vec, int(*ptrIfToSwap)(void*,void*))
{
	register int i, j;
	int swapped = 1;

	for(i = 1;i < _vec->m_numOfElements && swapped;++i)
	{
		swapped = 0;

		for(j = 1;j <= _vec->m_numOfElements-i;++j)
		{
			if((*ptrIfToSwap)(_vec->m_vectorArray[j],_vec->m_vectorArray[j+1]))
			{
				SWAP(_vec->m_vectorArray[j],_vec->m_vectorArray[j+1]);
				swapped = 1;
			}
		}
	}
}

/* SUB FUNCTINS */

static void** ReSizeVector(void** _vectorArray, size_t _newSize)
{
	_vectorArray = (void**)realloc(_vectorArray,(_newSize+1)*sizeof(void*));

	return _vectorArray;
}

static size_t searchIndex(const Vector* _vec,  void* _data)
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



