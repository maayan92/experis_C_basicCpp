#include "genDLListIterFunc.h"
#include <stdio.h>
#include <stdbool.h>



static int IfNeededThenSwap(genListIter _a, genListIter _b, lessFunc _lessFunc);
static int ShakeSortLastPlace(genListIter _begin, genListIter _end, lessFunc _lessFunc);
static int ShakeSortFirstPlace(genListIter _begin, genListIter _end, lessFunc _lessFunc);



static genListIter GenListIterIteration(genListIter _begin, genListIter _end, predicateFunc _predicateFunc, void *_context, int _stopCritiria)
{
    if(!_predicateFunc)
    {
        return _begin; /* TODO illigal iterator */
    }
    while(!GenListIterEquals(_begin, _end))
    {
        if(_predicateFunc(GenListIterGet(_begin), _context) == _stopCritiria)
        {
            break;
        }
        _begin = GenListIterNext(_begin);
    }
    return _begin;
}

genListIter GenListIterFindFirst(genListIter _begin, genListIter _end, predicateFunc _predicateFunc, void *_context)
{
    return GenListIterIteration(_begin, _end, _predicateFunc, _context, true);
}

genListIter GenListIterForEach(genListIter _begin, genListIter _end, listActionFunc _listActionFunc, void *_context)
{
    return GenListIterIteration(_begin, _end, _listActionFunc, _context, false);
}

size_t GenListIterCountIf(genListIter _begin, genListIter _end, predicateFunc _predicateFunc, void *_context)
{
    size_t counter = 0;
    
    if(!_predicateFunc)
    {
        return 0;
    }
    while(!GenListIterEquals(_begin, _end))
    {
        if(_predicateFunc(GenListIterGet(_begin), _context))
        {
            ++counter;
        }
        _begin = GenListIterNext(_begin);
    }
    return counter;
}

void GenListIterSort(genListIter _begin, genListIter _end, lessFunc _lessFunc)
{
    int swaped = true;
    
    if(!_lessFunc)
    {
        return;
    }
    
    while(!GenListIterEquals(_begin, _end))
    {
        swaped = ShakeSortLastPlace(_begin, _end, _lessFunc);
        _end = GenListIterPrev(_end);
        if(!swaped)
        {
            return;
        }
        swaped = ShakeSortFirstPlace(_begin, _end, _lessFunc);
        _begin = GenListIterNext(_begin);
    }
}

static int IfNeededThenSwap(genListIter _a, genListIter _b, lessFunc _lessFunc)
{
    void *dataA, *dataB;
    
    dataA = GenListIterGet(_a);
    dataB = GenListIterGet(_b);
    
    if(_lessFunc(dataA, dataB))
    {
        GenListIterSet(_a, dataB);
        GenListIterSet(_b, dataA);
        return true;
    }
    return false;
}

static int ShakeSortLastPlace(genListIter _begin, genListIter _end, lessFunc _lessFunc)
{
    int swaped = false;

    while(!GenListIterEquals(GenListIterNext(_begin), _end))
    {
        if(IfNeededThenSwap(_begin, GenListIterNext(_begin), _lessFunc))
        {
            swaped = true;
        }
        _begin = GenListIterNext(_begin);
    }
    return swaped;
}

static int ShakeSortFirstPlace(genListIter _begin, genListIter _end, lessFunc _lessFunc)
{
    int swaped = false;
    
    _end = GenListIterPrev(_end);
    while(!GenListIterEquals(_begin, _end))
    {
        if(IfNeededThenSwap(GenListIterPrev(_end), _end, _lessFunc))
        {
            swaped = true;
        }
        _end = GenListIterPrev(_end);
    }
    return swaped;
}


