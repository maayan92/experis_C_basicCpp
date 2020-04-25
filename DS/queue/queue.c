#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "dynamicVector.h"

#define IS_NOT_EXIST(_que) (NULL == _que || (*_que).m_MagicNumber != MAGIC_NUMBER)

struct CyclicQueue
{
	size_t m_MagicNumber;
	size_t m_head;
	size_t m_tail;
	size_t m_initialSize;
	size_t m_numOfElements;
	Vector *m_vec;
};

static void fillQueue(CyclicQueue *_que)
{
	while(VectorNumOfelements(_que->m_vec) < _que->m_initialSize)
	{
		VectorAddTail(_que->m_vec,0);
	}
}

CyclicQueue * QueueCreate(size_t _initialSize)
{
	CyclicQueue *que;

	que = (CyclicQueue*)malloc(sizeof(CyclicQueue));

	if(NULL == que)
	{
		return NULL;
	}

	que->m_vec = VectorCreate(_initialSize,0);

	if(NULL == que->m_vec)
	{
		free(que);
		return NULL;
	}

	que->m_head = 1;
	que->m_tail = 1;
	que->m_initialSize = _initialSize;
	que->m_numOfElements = 0;
	que->m_MagicNumber = MAGIC_NUMBER;

	fillQueue(que);

	return que;
}

void QueueDestroy(CyclicQueue *_que)
{
	if(!IS_NOT_EXIST(_que))
	{
		_que->m_MagicNumber = NO_MAGIC_NUMBER;

		VectorDestroy(_que->m_vec);

		free(_que);
	}
}

ErrCode QueueEnQueue(CyclicQueue *_que, int _data)
{
	if(IS_NOT_EXIST(_que))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(_que->m_numOfElements == _que->m_initialSize)
	{
		return ERR_OVERFLOW;
	}

	VectorSet(_que->m_vec,_que->m_tail,_data);

	_que->m_numOfElements++;
	_que->m_tail = (_que->m_tail % _que->m_initialSize) + 1;

	return SUCCEEDED;
}

ErrCode QueueDeQueue(CyclicQueue *_que, int *_data)
{
	ErrCode err;

	if(IS_NOT_EXIST(_que))
	{
		return ERR_NOT_INITIALIZE;
	}

	if(0 == _que->m_numOfElements)
	{
		return ERR_UNDERFLOW;
	}

	err = VectorGet(_que->m_vec,_que->m_head,_data);

	if(SUCCEEDED != err)
	{
		return err;
	}

	_que->m_numOfElements--;
	_que->m_head = (_que->m_head % _que->m_initialSize) + 1;

	return SUCCEEDED;
}

int QueueIsEmpty(CyclicQueue *_que)
{
	return !QueueNumOfElements(_que);
}

size_t QueueNumOfElements(CyclicQueue *_que)
{

	if(IS_NOT_EXIST(_que))
	{
		return 0;
	}

	return _que->m_numOfElements;
}




