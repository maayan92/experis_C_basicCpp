#include <stdio.h>
#include <stdlib.h>

#include "listFunctions.h"

static void* node = NULL;
ListItr ilegalItr = &node;

typedef void (*ptrNextPrev)(ListItr *, ListItr *);

/*get the wanted ListItr*/
static ListItr getListItr(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context, Bool _bool);
/*swap data between two iterators*/
static void Swap(ListItr _first, ListItr _second);
/*promotes one step back*/
static void getPrev(ListItr *_first, ListItr *_second);
/*promotes one step ahead*/
static void getNext(ListItr *_first, ListItr *_second);
/*push data back by function _less*/
static size_t PushBackByDirection(ListItr *_first, ListItr *_second, ListItr _end, LessFunction _less, ptrNextPrev _getNextPrev);
/*remove _begin and insert before _dest*/
static ListItr InsertBeforeDest(ListItr _dest, ListItr _begin);



ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{	
	return getListItr(_begin,_end,_predicate,_context,false);
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	int count = 0;
	
	if(NULL == _predicate)
	{
		return count;
	}
	
	while(!ListItrEquals(_begin,_end))
	{
		if(_predicate(ListItrGet(_begin),_context))
		{
			++count;
		}
		
		_begin = ListItrNext(_begin);
	}
	
	return count;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	return getListItr(_begin,_end,_action,_context,true);
}

void ListItrSort(ListItr _begin, ListItr _end, LessFunction _less)
{
	int swapped = 1;
	ListItr firstItr = _begin, secondItr;
	
	if(NULL == _less)
	{
		return;
	}
	
	while(!ListItrEquals(_begin,_end) && swapped)
	{
		firstItr = _begin;
		secondItr = ListItrNext(firstItr);
		
		swapped = PushBackByDirection(&firstItr,&secondItr,_end,_less,getNext);
		
		getPrev(&firstItr,&secondItr);
		
		swapped = PushBackByDirection(&firstItr,&secondItr,_begin,_less,getPrev);
		
		_end = ListItrPrev(_end);
	}
}

ListItr ListItrSplice(ListItr _dest, ListItr _begin, ListItr _end)
{
	while(!ListItrEquals(_begin,_end))
	{
		_begin = InsertBeforeDest(_dest,_begin);
	}

	return _dest;
}

ListItr ListItrMerge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
	if(NULL == _less)
	{
		return _destBegin;
	}

	while(!ListItrEquals(_firstBegin,_firstEnd) && !ListItrEquals(_secondBegin,_secondEnd))
	{
		if(_less(ListItrGet(_firstBegin),ListItrGet(_secondBegin)))
		{
			_firstBegin = InsertBeforeDest(_destBegin,_firstBegin);
		}
		else
		{
			_secondBegin = InsertBeforeDest(_destBegin,_secondBegin);
		}
	}
	
	if(!ListItrEquals(_firstBegin,_firstEnd))
	{
		return ListItrSplice(_destBegin,_firstBegin,_firstEnd);
	}
	
	return ListItrSplice(_destBegin,_secondBegin,_secondEnd);
}

List* ListItrCut(ListItr _begin, ListItr _end)
{
	List *newList = DLListCreate();

	if(NULL == newList)
	{
		return NULL;
	}

	ListItrSplice(ListItrEnd(newList),_begin,_end);

	return newList;
}

List* ListItrUnique(ListItr _begin, ListItr _end, EqualsFunction _equals)
{
	ListItr next = ListItrNext(_begin);
	List *newList;
	
	if(NULL == _equals)
	{
		return NULL;
	}
	
	newList = DLListCreate();
	if(NULL == newList)
	{
		return NULL;
	}
	
	while(!ListItrEquals(_begin,_end) && !ListItrEquals(_begin,ListItrPrev(_end)))
	{
		next = ListItrNext(_begin);
		_begin = (_equals(ListItrGet(_begin),ListItrGet(next))) ? InsertBeforeDest(ListItrEnd(newList),_begin) : next;
	}
	
	return newList;
}

/* SUB FUNCTIONS */

static ListItr getListItr(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context, Bool _bool)
{
	if(NULL == _predicate)
	{
		return _end;/*TODO*/
	}
	
	while(!ListItrEquals(_begin,_end) && _bool == _predicate(ListItrGet(_begin),_context))
	{
		_begin = ListItrNext(_begin);
	}
	
	return _begin;
}

static void Swap(ListItr _first, ListItr _second)
{
	void *firstData, *secondData;
	
	firstData = ListItrGet(_first);
	secondData = ListItrSet(_second,firstData);
	ListItrSet(_first,secondData);
}

static void getPrev(ListItr *_first, ListItr *_second)
{
	*_second = *_first;
	*_first = ListItrPrev(*_first);
}

static void getNext(ListItr *_first, ListItr *_second)
{
	*_first = *_second;
	*_second = ListItrNext(*_second);
}

static size_t PushBackByDirection(ListItr *_first, ListItr *_second, ListItr _end, LessFunction _less, ptrNextPrev _getNextPrev)
{
	size_t swapped = 0;

	while(!ListItrEquals(*_second,_end))
	{
		if(_less(ListItrGet(*_second),ListItrGet(*_first)))
		{
			Swap(*_first,*_second);
			swapped = 1;
		}
		
		_getNextPrev(_first,_second);
	}
	
	return swapped;
}


static ListItr InsertBeforeDest(ListItr _dest, ListItr _begin)
{
	ListItr temp = ListItrNext(_begin);

	ListItrInsertBefore(_dest,ListItrRemove(_begin));
	
	return temp;
}










