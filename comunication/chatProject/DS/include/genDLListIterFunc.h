#ifndef __GENLISTITERFUNC_H__
#define __GENLISTITERFUNC_H__

#include "genDLListIter.h"


/*
    DESCRIPTION:    Predicate func returns value of true if predicate holds for element.
    
    INPUT:          _element - element to test.
                    _context - context to be used in func.
    
    RETURN:         Value of true if predicate holds.
*/
typedef int(*predicateFunc)(void *_element, void *_context);


/*
    DESCRIPTION:    Action func to operate on an element.
    
    INPUT:          _element - element to test.
                    _context - context to be used in func.
    
    RETURN:         Value of zero if actoin fails.
*/
typedef int(*listActionFunc)(void *_element, void *_context);


/*
    DESCRIPTION:    Action func to check if _a < _b.
    
    INPUT:          _a - element to test.
                    _b - element to test.
    
    RETURN:         Value of true if _a < _b.
*/
typedef int(*lessFunc)(void *_a, void *_b);


/*
    DESCRIPTION:    Action func to check if _a == _b.
    
    INPUT:          _a - element to test.
                    _b - element to test.
    
    RETURN:         Value of true if _a == _b.
*/
typedef int(*cmprFunc)(void *_a, void *_b);





/*
    DESCRIPTION:    Findes the first element in a range where _predicateFunc if true.
    
    INPUT:          _begin - Start search from here.
                    _end - End search here, not included.
                    _predicateFunc - Predicate func.
                    _context - Context to be used in func.
    
    RETURN:         Pointer to the first element found, if not found returns end.
*/
genListIter GenListIterFindFirst(genListIter _begin, genListIter _end, predicateFunc _predicateFunc, void *_context);


/*
    DESCRIPTION:    Exicute an action for all elements in range.
    
    INPUT:          _begin - Start search from here.
                    _end - End search here, not included.
                    _listActionFunc - Action func.
                    _context - Context to be used in func.
    
    RETURN:         genListIter to the element where the iteration stoped.
*/
genListIter GenListIterForEach(genListIter _begin, genListIter _end, listActionFunc _listActionFunc, void *_context);


/*
    DESCRIPTION:    Count elements in a range where _predicateFunc is true.
    
    INPUT:          _begin - Start search from here.
                    _end - End search here, not included.
                    _predicateFunc - Predicate func.
                    _context - Context to be used in func.
    
    RETURN:         Num of elements where _predicateFunc is true.
*/
size_t GenListIterCountIf(genListIter _begin, genListIter _end, predicateFunc _predicateFunc, void *_context);


/*
    DESCRIPTION:    Shake sorts the sublist. O(n^2)
    
    INPUT:          _begin - Start search from here.
                    _end - End search here, not included.
                    _lessFunc - Less compare func.
*/
void GenListIterSort(genListIter _begin, genListIter _end, lessFunc _lessFunc);


/*
    DESCRIPTION:    .
    
    INPUT:          _dest - 
                    _begin - Start search from here.
                    _end - End search here, not included.
    
    RETURN:         .
*/
genListIter GenListIterSplice(genListIter _dest, genListIter _begin, genListIter _end);



#endif




