#include "genDLList.h"
#include "genDLListIter.h"
#include <stdio.h>
#include <stdlib.h>  /*for allocation*/
#include <stdbool.h>

#define MAGIC_NUMBER 0xbeacdea
#define NO_MAGIC_NUMBER 0xdeadbeef

#define IS_LIST_NOT_EXIST(lst) (!lst || lst->m_magicNumber != MAGIC_NUMBER)
#define IS_LIST_EMPY(lst) (lst->m_head.m_next == &lst->m_tail)


typedef struct node
{
    void *m_data;
    struct node *m_prev;
    struct node *m_next;
}node;

struct genList
{
    size_t m_magicNumber;
    node m_head;
    node m_tail;
};


/*
    DESCRIPTION:    Creates a new node.

    INPUT:          _data - The value for element we are creating.

    RETURN:         Pointer to the new node created, if failed returns NULL.
*/
static node* GenDLListCreateNode(void *_data);

/*
    DESCRIPTION:    Adds _newNode as the element after _tempHead.

    INPUT:          _tempHead - Pointer to the node we want to be before the _newNode added. Should not be NULL.
                    _newNode - Pointer to the node we want to add after _tempHead. Should not be NULL.
*/
static void GenDLListAddNode(node *_tempHead, node *_newNode);

/*
    DESCRIPTION:    Removes _nodeToRemove from the list.

    INPUT:          _nodeToRemove - The element we want to remove.

    RETURN:         The m_data value of the element removed.
*/
static void* GenDLListRemoveNode(node *_nodeToRemove);



genList* GenDLListCreate()
{
    genList * newList;

    if((newList = (genList*)malloc(sizeof(genList))) == NULL)
    {
        return NULL;
    }

    newList->m_head.m_next = &newList->m_tail;
    newList->m_tail.m_prev = &newList->m_head;
    newList->m_head.m_prev = NULL;
    newList->m_tail.m_next = NULL;
    newList->m_head.m_data = NULL;
    newList->m_tail.m_data = NULL;
    newList->m_magicNumber = MAGIC_NUMBER;

    return newList;
}

void GenDLListDestroy(genList *_lst, void(*_elementDestroyFunc)(void*))
{
    void* data;
    
    if(IS_LIST_NOT_EXIST(_lst))
    {
        return;
    }

    _lst->m_magicNumber = NO_MAGIC_NUMBER;

    if(_elementDestroyFunc)
    {
        while(!IS_LIST_EMPY(_lst))
        {
            data = GenDLListRemoveNode(_lst->m_head.m_next);
            _elementDestroyFunc(data);
        }
    }
    else
    {
        while(!IS_LIST_EMPY(_lst))
        {
            GenDLListRemoveNode(_lst->m_head.m_next);
        }
    }

    free(_lst);

    return;
}

ErrorCode GenDLListPushHead(genList *_lst, void *_data)
{
    node *newNode;

    if(IS_LIST_NOT_EXIST(_lst))
    {
        return ERROR_NOT_INITIALIZED;
    }
    if(!_data)
    {
        return ERROR_WRONG_INPUT;
    }
    if(!(newNode = GenDLListCreateNode(_data)))
    {
        return ERROR_ALLOCATION_FAILED;
    }

    GenDLListAddNode(&_lst->m_head, newNode);

    return OK;
}

ErrorCode GenDLListPushTail(genList *_lst, void *_data)
{
    node *newNode;

    if(IS_LIST_NOT_EXIST(_lst))
    {
        return ERROR_NOT_INITIALIZED;
    }
    if(!_data)
    {
        return ERROR_WRONG_INPUT;
    }
    if(!(newNode = GenDLListCreateNode(_data)))
    {
        return ERROR_ALLOCATION_FAILED;
    }

    GenDLListAddNode(_lst->m_tail.m_prev, newNode);

    return OK;
}

ErrorCode GenDLListPopHead(genList *_lst, void **_data)
{
    if(IS_LIST_NOT_EXIST(_lst))
    {
        return ERROR_NOT_INITIALIZED;
    }
    if(!_data)
    {
        return ERROR_WRONG_INPUT;
    }
    if(IS_LIST_EMPY(_lst))
    {
        return ERROR_UNDERFLOW;
    }

    *_data = GenDLListRemoveNode(_lst->m_head.m_next);

    return OK;
}

ErrorCode GenDLListPopTail(genList *_lst, void **_data)
{
    if(IS_LIST_NOT_EXIST(_lst))
    {
        return ERROR_NOT_INITIALIZED;
    }
    if(!_data)
    {
        return ERROR_WRONG_INPUT;
    }
    if(IS_LIST_EMPY(_lst))
    {
        return ERROR_UNDERFLOW;
    }

    *_data = GenDLListRemoveNode(_lst->m_tail.m_prev);

    return OK;
}

size_t GenDLListCountItems(const genList *_lst)
{
    size_t counter = 0;
    node *temp;

    if(IS_LIST_NOT_EXIST(_lst) || IS_LIST_EMPY(_lst))
    {
        return counter;
    }

    temp = _lst->m_head.m_next;

    while(temp != &_lst->m_tail)
    {
        ++counter;
        temp = temp->m_next;
    }

    return counter;
}

int GenDLListIsEmpty(const genList *_lst)
{
    if(IS_LIST_NOT_EXIST(_lst) || IS_LIST_EMPY(_lst))
    {
        return true;
    }

    return false;
}
/*
void GenDLListPrint(genList *_lst)
{
    node *temp;

    if(IS_LIST_NOT_EXIST(_lst) || IS_LIST_EMPY(_lst))
    {
        return;
    }

    temp = _lst->m_head.m_next;

    while(temp != &_lst->m_tail)
    {
        printf("%d -> ", temp->m_data);
        temp = temp->m_next;
    }
    printf("\n");

    return;
}
*/

genListIter GenListIterBegin(const genList *_lst)
{
    if(IS_LIST_NOT_EXIST(_lst))
    {
        return NULL;
    }
    return _lst->m_head.m_next;
}

genListIter GenListIterEnd(const genList *_lst)
{
    if(IS_LIST_NOT_EXIST(_lst))
    {
        return NULL;
    }
    return _lst->m_tail.m_prev->m_next;
}

int GenListIterEquals(const genListIter _a, const genListIter _b)
{
    return _a == _b;
}

genListIter GenListIterNext(genListIter *_itr)
{
    if(!((node*)_itr)->m_next)
    {
        return _itr;
    }
    return (genListIter)((node*)_itr)->m_next;
}

genListIter GenListIterPrev(genListIter *_itr)
{
    if(!((node*)_itr)->m_prev)
    {
        return _itr;
    }
    return (genListIter)((node*)_itr)->m_prev;
}

void* GenListIterGet(genListIter _itr)
{
    return ((node*)_itr)->m_data;
}

void* GenListIterSet(genListIter _itr, void* _data)
{
    void *temp;
    
    temp = ((node*)_itr)->m_data;
    ((node*)_itr)->m_data = _data;
    return temp;
}

genListIter GenListIterInsertBefore(genListIter _itr, void* _data)
{
    node *newNode;
    
    if(!((node*)_itr)->m_prev)
    {
        return NULL;
    }
    if(!(newNode = GenDLListCreateNode(_data)))
    {
        return NULL;
    }
    GenDLListAddNode(GenListIterPrev(_itr), newNode);
    return (genListIter)newNode;
}

void* GenListIterRemove(genListIter _itr)
{
    if(!((node*)_itr)->m_prev || !((node*)_itr)->m_next)
    {
        return NULL;
    }
    return GenDLListRemoveNode((node*)_itr);
}



static node* GenDLListCreateNode(void *_data)
{
    node *newNode;

    if((newNode = (node*)malloc(sizeof(node))) == NULL)
    {
        return NULL;
    }

    newNode->m_data = _data;
    newNode->m_prev = NULL;
    newNode->m_next = NULL;

    return newNode;
}

static void* GenDLListRemoveNode(node *_nodeToRemove)
{
    void *data;

    data = _nodeToRemove->m_data;

    _nodeToRemove->m_prev->m_next = _nodeToRemove->m_next;
    _nodeToRemove->m_next->m_prev = _nodeToRemove->m_prev;

    free(_nodeToRemove);

    return data;
}

static void GenDLListAddNode(node *_tempHead, node *_newNode)
{
    _newNode->m_prev = _tempHead;
    _newNode->m_next = _tempHead->m_next;
    _tempHead->m_next = _newNode;
    _newNode->m_next->m_prev = _newNode;
    return;
}






