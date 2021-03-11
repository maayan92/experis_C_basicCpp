#ifndef __GENDLLISTITER_H__
#define __GENDLLISTITER_H__

#include "genDLList.h"
#include "ADTerror.h"
#include <stdio.h>  /*for size_t*/

typedef void* genListIter;


/*
    DESCRIPTION:    Returns the genListIter in the begining (first element) of the genList.
    
    INPUT:          _lst - List to return it's begining. Should not be NULL.
    
    RETURN:         The genListIter in the begining of the genList. If empty returns the end of the list.
    
    ERRORS:         Returns NULL if the list is not initialized.
*/
genListIter GenListIterBegin(const genList *_lst);


/*
    DESCRIPTION:    Returns the genListIter in the end (tail) of the genList.
    
    INPUT:          _lst - List to return it's end. Should not be NULL.
    
    RETURN:         The genListIter in the end of the genList. If empty returns the begining of the list.
    
    ERRORS:         Returns NULL if the list is not initialized.
*/
genListIter GenListIterEnd(const genList *_lst);


/*
    DESCRIPTION:    Checks if the two nodes are equal.
    
    INPUT:          _a - Pointer to node to compare with _b.
                    _b - Pointer to node to compare with _a.
    
    RETURN:         Value of true if _a and _b are pointing to the same node or both NULL. If not, flase.
    
    ERRORS:         Value of false if _a and _b are NULL.
*/
int GenListIterEquals(const genListIter _a, const genListIter _b);


/*
    DESCRIPTION:    Returns the next element.
    
    INPUT:          _itr - Pointer to a genListIter node. Should not be NULL. Func Does not check if it is NULL.
    
    RETURN:         Pointer to the next element, if end of genListIter returns end.
*/
genListIter GenListIterNext(genListIter *_itr);


/*
    DESCRIPTION:    Returns the prev element.
    
    INPUT:          _itr - Pointer to a genListIter node. Should not be NULL. Func Does not check if it is NULL.
    
    RETURN:         Pointer to the prev element, if begining of genListIter returns begining.
*/
genListIter GenListIterPrev(genListIter *_itr);


/*
    DESCRIPTION:    Returns the data from the node _itr is pointing at.
    
    INPUT:          _itr - Pointer to a genListIter node. Should not be NULL. Func Does not check if it is NULL.
    
    RETURN:         The data from the node _itr is pointing at.
    
    ERRORS:         Returns NULL if _itr is NULL or if _itr is pointing to the end of the list.
*/
void* GenListIterGet(genListIter _itr);


/*
    DESCRIPTION:    Replaces the data from the node with _data.
    
    INPUT:          _itr - Pointer to a genListIter node. Should not be NULL or begining or end of the list.
                           Func Does not check if it is.
                    _data - the new data for the genListIter node.
    
    RETURN:         The original data from the node _itr is pointing at.
*/
void* GenListIterSet(genListIter _itr, void* _data);


/*
    DESCRIPTION:    Inserts a new node before the genListIter pointer.
    
    INPUT:          _itr - Pointer to a genListIter node. Should not be NULL or begining of the list. 
                           Func Does not check if it is NULL.
    
    RETURN:         genListIter to the new node added.
    
    ERRORS:         Returns NULL if _itr is pointing to the begining of the list.
*/
genListIter GenListIterInsertBefore(genListIter _itr, void* _data);


/*
    DESCRIPTION:    Removes the node at the genListIter pointer.
    
    INPUT:          _itr - Pointer to a genListIter node. Should not be NULL or begining or end of the list.
                           Func Does not check if it is NULL.
    
    RETURN:         The data from the removed node.
    
    ERRORS:         Returns NULL if _itr is pointing to the begining or end of the list.
*/
void* GenListIterRemove(genListIter _itr);


#endif
