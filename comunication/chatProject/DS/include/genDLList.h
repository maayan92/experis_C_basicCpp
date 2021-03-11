#ifndef __GENDLLIST_H__
#define __GENDLLIST_H__

#include "ADTerror.h"
#include <stdio.h>  /*for size_t*/

typedef struct genList genList;


/*
    DESCRIPTION:    Creates GenDLList.

    RETURN:         Pointer to the new genList created, if failed returns NULL.
*/
genList* GenDLListCreate();


/*
    DESCRIPTION:    Frees list. User should set _lst = NULL afterwards.

    INPUT:          _lst - Pointer to genList created in GenDLListCreate(). Should not be NULL.
                    _elementDestroyFunc - Func to destroy one element. If NULL element will not be destroyed.
*/
void GenDLListDestroy(genList *_lst, void(*_elementDestroyFunc)(void*));


/*
    DESCRIPTION:    Adds the element to the head of the list.

    INPUT:          _lst - Pointer to genList created in GenDLListCreate(). Should not be NULL.
                    _data - The element we want to add to the list. Should not be NULL.

    RETURN:         Value of OK if the element was added.
                    ERROR_NOT_INITIALIZED if the list was not initialized.
                    ERROR_WRONG_INPUT if the input is flawed.
                    ERROR_ALLOCATION_FAILED if the allocation failed.
*/
ErrorCode GenDLListPushHead(genList *_lst, void *_data);


/*
    DESCRIPTION:    Adds the element to the tail of the list.

    INPUT:          _lst - Pointer to genList created in GenDLListCreate(). Should not be NULL.
                    _data - The element we want to add to the list. Should not be NULL.

    RETURN:         Value of OK if the element was added.
                    ERROR_NOT_INITIALIZED if the list was not initialized.
                    ERROR_WRONG_INPUT if the input is flawed.
                    ERROR_ALLOCATION_FAILED if the allocation failed.
*/
ErrorCode GenDLListPushTail(genList *_lst, void *_data);


/*
    DESCRIPTION:    Removes the element from the head of the list.

    INPUT:          _lst - Pointer to genList created in GenDLListCreate(). Should not be NULL.
                    _data - Pointer the the pointer that will receive the element removed from the list. Should not be NULL.

    RETURN:         Value of OK if the element was removed.
                    ERROR_NOT_INITIALIZED if the list was not initialized.
                    ERROR_WRONG_INPUT if the input is flawed.
                    ERROR_UNDERFLOW if the genList is empty.
*/
ErrorCode GenDLListPopHead(genList *_lst, void **_data);


/*
    DESCRIPTION:    Removes the element from the tail of the list.

    INPUT:          _lst - Pointer to genList created in GenDLListCreate(). Should not be NULL.
                    _data - Pointer the the pointer that will receive the element removed from the list. Should not be NULL.

    RETURN:         Value of OK if the element was removed.
                    ERROR_NOT_INITIALIZED if the list was not initialized.
                    ERROR_WRONG_INPUT if the input is flawed.
                    ERROR_UNDERFLOW if the genList is empty.
*/
ErrorCode GenDLListPopTail(genList *_lst, void **_data);


/*
    DESCRIPTION:    Counts the number of elements in the list. Complexity O(n).

    INPUT:          _lst - Pointer to genList created in GenDLListCreate(). Should not be NULL.

    RETURN:         The number of elements in the list.
*/
size_t GenDLListCountItems(const genList *_lst);


/*
    DESCRIPTION:    Checks if the GenDLList is empty.

    INPUT:          _lst - Pointer to genList created in GenDLListCreate(). Should not be NULL.

    RETURN:         Value of true if the genList is empty or NULL.
                    Value of false if the genList has elements.
*/
int GenDLListIsEmpty(const genList *_lst);


/*
    DESCRIPTION:    Prints the GenDLList.

    INPUT:          _lst - Pointer to genList created in GenDLListCreate(). Should not be NULL.

void GenDLListPrint(genList *_lst);
*/

#endif


