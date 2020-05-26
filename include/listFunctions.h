#ifndef __LIST_FUNCTIONS_H__
#define __LIST_FUNCTIONS_H__


#include "GDLList_Itr.h"

/*All function use half open range [_begin.._end) */
 
/* POINTERS TO FUNCTIONS */
 
/*
	Description: Predicate function returns a none zero value if predicate holds for element.
	Input: _element - element to test, _context - context to be used.
	Return value: return none zero if predicate holds.
*/
typedef int (*PredicateFunction)(void * _element, void* _context);

/*
	Description: Action function to operate on an element.
	Input: _element - element to test, _context - context to be used.
	Return value: return zero if action fails.
*/
typedef int (*ListActionFunction)(void* _element, void* _context);

/*
	Description: Action function to check if a < b 
	Input: _a - element to test, _b - element to test against
	Return value: return none zero if _a < _b.
*/
typedef int (*LessFunction)(void* _a, void* _b);

 /*
	Description: Action function to check if a == b.
	Input: _a - element to test, _b - element to test against
	Return value: return none zero if _a == _b.
*/
typedef int (*EqualsFunction)(void* _a, void* _b);

/* FUNCTIONS */

/*
	Description: Finds the first element in a range for which the predicate returns a non zero value.
	Input: _begin - start search from here, _end - end search here -> not included, 
		_predicate - predicate function, _context : context to be passed to the predicate.
	Return value: return an iterator pointing to the first node with data found or to _end if not.
*/
ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context);

/*
	Description: count elements in a sub list for which the predicate returns a non zero value.
	Input: _begin - start search from here, _end - end search here -> not included, 
		_predicate - predicate function, _context - context to be passed to the predicate.
	Return value: return count of all elements e where _predicate(e, _context) != 0.
*/
size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context);

/*
	Description:  execute an action for all elements in a half open range, iteration will stop if Action function returns 0 for an element.
	Input: _begin - start search from here, _end - end search here -> not included, 
		_Action - user provided action function, _context - context to be passed to the predicate.
	Return value: return ListItr to the element where the iteration stoped. this might be end iterator.
*/
ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context);

/*
	Description: Sorts a sublist in place using the bubble sort algorithm, Complexity O(n^2).
	Input: _begin - Iterator to sublist start, _end - Iterator to sublist end, _less - less compare function.
	Return value: nothing returns.
*/
void ListItrSort(ListItr _begin, ListItr _end, LessFunction _less);

/*
	Description: remove all elements from the half open range and insert them before _dest. O(n)
	Input: _begin - Iterator to sublist start, _end - Iterator to sublist end, _dset - the destination list. 
	warning: The function assumes that : _begin and _end are in the correct order and on the same list, is not between _begin and _end,
						all three iterators can belong to same list.
	Return value: return iterator _dest.
*/
ListItr ListItrSplice(ListItr _dest, ListItr _begin, ListItr _end);

/*
	Description: Merges two given sublists into destination. O(n)
	Input: _firstBegin - Iterator to first sublist start, _firstEnd - Iterator to first sublist end,
		_secondBegin - Iterator to second sublist start, _secondEnd - Iterator to second sublist end,
		_destBegin - Iterator to destination list start, _less - less compare function.
	warning: sublists should be sorted, this will removes all merged items from source ranges.
	Return value: return iterator _destBegin.
*/
ListItr ListItrMerge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd, LessFunction _less);

/*
	Description: Removes a sublist [_begin.._end)  from a list and creates a new list with all removed items. O(n)
	Input: _begin - Iterator to sublist start, _end - Iterator to sublist end.
	Return value: return pointer to the new list.
*/
List* ListItrCut(ListItr _begin, ListItr _end);

/*
	Description: Removes all duplicate elements from a sorted sublist [_begin.._end) and rertun a new list with all removed items. O(?)
	Input: _begin - Iterator to sublist start, _end - Iterator to sublist end, _equals - equals compare function.
	Return value: rertun a new list with all removed items.
*/
List* ListItrUnique(ListItr _begin, ListItr _end, EqualsFunction _equals);







#endif
