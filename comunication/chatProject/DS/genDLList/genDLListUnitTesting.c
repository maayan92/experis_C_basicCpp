#include "genDLList.h"
#include "genDLListIter.h"
#include <stdio.h>
#include <stdlib.h>  /* for allocation */
#include <stdbool.h>

typedef enum result
{
    SUCCESS,
    FAIL
}result;


typedef struct testing
{
    int m_a;
}testing;


static testing* CreateTestingElement(int _a)
{
    testing *t;
    if(!(t = (testing*)malloc(sizeof(testing))))
    {
        return NULL;
    }
    t->m_a = _a;
    return t;
}

static void DestroyTestingElement(void *_t)
{
    if(_t)
    {
        free(_t);
    }
}

static void PrintTestingElement(void *_t)
{
    if(_t)
    {
        printf("%d\t", ((testing*)_t)->m_a);
    }
}


static void TestPrintResult(result (*_funcToTest)(void), char *_funcName)
{
    result r = _funcToTest();
    printf("%-50s%s\n", _funcName, r==SUCCESS? "SUCCESS": "FAIL");
}


result TestGenDLListCreate_N()
{
    genList *lst = NULL;

    lst = GenDLListCreate();

    if(lst)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListDestroy_N()
{
    genList *lst = NULL;

    lst = GenDLListCreate();

    GenDLListDestroy(lst, NULL);

    return SUCCESS;
}

result TestGenDLListDestroy_Double()
{
    genList *lst = NULL;

    lst = GenDLListCreate();

    GenDLListDestroy(lst, NULL);
    GenDLListDestroy(lst, NULL);

    return SUCCESS;
}

result TestGenDLListDestroy_NULL()
{
    GenDLListDestroy(NULL, NULL);

    return SUCCESS;
}

result TestGenDLListDestroy_Copy()
{
    genList *lst = NULL, *copy = NULL;

    lst = GenDLListCreate();
    copy = lst;

    GenDLListDestroy(lst, NULL);
    GenDLListDestroy(copy, NULL);

    return SUCCESS;
}

result TestGenDLListPushHead_N()
{
    genList *lst = NULL;
    testing *t;
    ErrorCode e;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    
    e = GenDLListPushHead(lst, t);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e == OK)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListPushHead_Ten()
{
    genList *lst = NULL;
    testing *t;
    ErrorCode e;
    int i;

    lst = GenDLListCreate();

    for(i=0; i<10; ++i)
    {
        t = CreateTestingElement(i);
        e = GenDLListPushHead(lst, t);
        if(e != OK)
        {
            return FAIL;
        }
    }

    GenDLListDestroy(lst, DestroyTestingElement);

    return SUCCESS;
}

result TestGenDLListPushHead_lstNULL()
{
    ErrorCode e;
    int a = 4;

    e = GenDLListPushHead(NULL, &a);

    if(e != OK)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListPushHead_dataNULL()
{
    genList *lst = NULL;
    ErrorCode e;

    lst = GenDLListCreate();
    e = GenDLListPushHead(lst, NULL);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e != OK)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListPushTail_N()
{
    genList *lst = NULL;
    testing *t;
    ErrorCode e;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    
    e = GenDLListPushTail(lst, t);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e == OK)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListPushTail_Ten()
{
    genList *lst = NULL;
    testing *t;
    ErrorCode e;
    int i;

    lst = GenDLListCreate();

    for(i=0; i<10; ++i)
    {
        t = CreateTestingElement(i);
        e = GenDLListPushTail(lst, t);
        if(e != OK)
        {
            return FAIL;
        }
    }

    GenDLListDestroy(lst, DestroyTestingElement);

    return SUCCESS;
}

result TestGenDLListPushTail_lstNULL()
{
    ErrorCode e;
    int a = 4;

    e = GenDLListPushTail(NULL, &a);

    if(e != OK)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListPushTail_dataNULL()
{
    genList *lst = NULL;
    ErrorCode e;

    lst = GenDLListCreate();
    e = GenDLListPushTail(lst, NULL);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e != OK)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListPopHead_N()
{
    genList *lst = NULL;
    ErrorCode e;
    testing *t, *out;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    
    e = GenDLListPushHead(lst, t);
    e = GenDLListPopHead(lst, (void**)&out);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e == OK && t == out)
    {
        DestroyTestingElement(out);
        return SUCCESS;
    }
    DestroyTestingElement(out);
    return FAIL;
}

result TestGenDLListPopHead_Ten()
{
    genList *lst = NULL;
    ErrorCode e;
    int i;
    testing *t, *out;

    lst = GenDLListCreate();

    for(i=0; i<10; ++i)
    {
        t = CreateTestingElement(i);
        GenDLListPushHead(lst, t);
    }
    for(i=0; i<10; ++i)
    {
        e = GenDLListPopHead(lst, (void**)&out);
        if(e != OK || out->m_a != 9-i)
        {
            DestroyTestingElement(out);
            return FAIL;
        }
        DestroyTestingElement(out);
    }

    GenDLListDestroy(lst, DestroyTestingElement);

    return SUCCESS;
}

result TestGenDLListPopHead_lstNULL()
{
    ErrorCode e;
    testing *t;

    e = GenDLListPopHead(NULL, (void**)&t);

    if(e != OK)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListPopHead_dataNULL()
{
    genList *lst = NULL;
    ErrorCode e;
    testing *t;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    
    e = GenDLListPushHead(lst, t);
    e = GenDLListPopHead(lst, NULL);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e != OK)
    {
        return SUCCESS;
    }
    return FAIL;
}

result TestGenDLListPopHead_lstEmpty()
{
    genList *lst = NULL;
    ErrorCode e;
    testing *t;

    lst = GenDLListCreate();
    
    e = GenDLListPopHead(lst, (void**)&t);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e != OK)
    {
        return SUCCESS;
    }
    return FAIL;
}

result TestGenDLListPopTail_N()
{
    genList *lst = NULL;
    ErrorCode e;
    testing *t, *out;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    
    e = GenDLListPushTail(lst, t);
    e = GenDLListPopTail(lst, (void**)&out);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e == OK && t == out)
    {
        DestroyTestingElement(out);
        return SUCCESS;
    }
    DestroyTestingElement(out);
    return FAIL;
}

result TestGenDLListPopTail_Ten()
{
    genList *lst = NULL;
    ErrorCode e;
    int i;
    testing *t, *out;

    lst = GenDLListCreate();

    for(i=0; i<10; ++i)
    {
        t = CreateTestingElement(i);
        GenDLListPushTail(lst, t);
    }
    for(i=0; i<10; ++i)
    {
        e = GenDLListPopTail(lst, (void**)&out);
        if(e != OK || out->m_a != 9-i)
        {
            DestroyTestingElement(out);
            return FAIL;
        }
        DestroyTestingElement(out);
    }

    GenDLListDestroy(lst, DestroyTestingElement);

    return SUCCESS;
}

result TestGenDLListPopTail_lstNULL()
{
    ErrorCode e;
    testing *t;

    e = GenDLListPopTail(NULL, (void**)&t);

    if(e != OK)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListPopTail_dataNULL()
{
    genList *lst = NULL;
    ErrorCode e;
    testing *t;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    
    e = GenDLListPushTail(lst, t);
    e = GenDLListPopTail(lst, NULL);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e != OK)
    {
        return SUCCESS;
    }
    return FAIL;
}

result TestGenDLListPopTail_lstEmpty()
{
    genList *lst = NULL;
    ErrorCode e;
    testing *t;

    lst = GenDLListCreate();
    
    e = GenDLListPopTail(lst, (void**)&t);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(e != OK)
    {
        return SUCCESS;
    }
    return FAIL;
}

result TestGenDLListCountItems_N()
{
    genList *lst = NULL;
    testing *t;
    int num = 0;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    
    num = GenDLListCountItems(lst);
    
    GenDLListDestroy(lst, DestroyTestingElement);

    if(num == 1)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListCountItems_Ten()
{
    genList *lst = NULL;
    testing *t;
    int i, num;

    lst = GenDLListCreate();

    for(i=1; i<=10; ++i)
    {
        t = CreateTestingElement(i);
        GenDLListPushHead(lst, t);
        num = GenDLListCountItems(lst);
        if(num != i)
        {
            return FAIL;
        }
    }

    GenDLListDestroy(lst, DestroyTestingElement);

    return SUCCESS;
}

result TestGenDLListCountItems_listNULL()
{
    size_t num;

    num = GenDLListCountItems(NULL);

    if(num == 0)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListCountItems_listEmpty()
{
    genList *lst = NULL;
    size_t num;

    lst = GenDLListCreate();
    num = GenDLListCountItems(lst);
    GenDLListDestroy(lst, NULL);

    if(num == 0)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListIsEmpty_listN()
{
    genList *lst = NULL;
    int flag;
    testing *t;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    flag = GenDLListIsEmpty(lst);
    GenDLListDestroy(lst, DestroyTestingElement);

    if(flag == false)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListIsEmpty_listNULL()
{
    int flag;

    flag = GenDLListIsEmpty(NULL);

    if(flag == true)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenDLListIsEmpty_listEmpty()
{
    genList *lst = NULL;
    int flag;

    lst = GenDLListCreate();
    flag = GenDLListIsEmpty(lst);
    GenDLListDestroy(lst, NULL);

    if(flag == true)
    {
        return SUCCESS;
    }

    return FAIL;
}

result TestGenListIterBegin_N()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    
    itr = GenListIterBegin(lst);
    
    if(!itr)
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result TestGenListIterBegin_NULL()
{
    genListIter itr;
    
    itr = GenListIterBegin(NULL);
    
    if(itr)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenListIterEnd_N()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    
    itr = GenListIterEnd(lst);
    
    if(!itr)
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result TestGenListIterEnd_NULL()
{
    genListIter itr;
    
    itr = GenListIterEnd(NULL);
    
    if(itr)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenListIterEquals_equals()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr1, itr2;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    
    itr1 = GenListIterBegin(lst);
    itr2 = GenListIterBegin(lst);
    
    if(!GenListIterEquals(itr1, itr2))
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result TestGenListIterEquals_notEquals()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr1, itr2;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    
    itr1 = GenListIterBegin(lst);
    itr2 = GenListIterEnd(lst);
    
    if(GenListIterEquals(itr1, itr2))
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result TestGenListIterEquals_aNULL_bN()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    
    itr = GenListIterBegin(lst);
    
    if(GenListIterEquals(NULL, itr))
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result TestGenListIterEquals_aN_bNULL()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    
    itr = GenListIterBegin(lst);
    
    if(GenListIterEquals(itr, NULL))
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result TestGenListIterEquals_aNULL_bNULL()
{
    if(GenListIterEquals(NULL, NULL))
    {
        return SUCCESS;
    }
    return FAIL;
}

result GenListIterNext_N()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr1, itr2;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    itr1 = GenListIterBegin(lst);
    itr2 = GenListIterEnd(lst);
    
    itr1 = GenListIterNext(itr1);
    
    if(!GenListIterEquals(itr1, itr2))
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result GenListIterPrev_N()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr1, itr2;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    itr1 = GenListIterBegin(lst);
    itr2 = GenListIterEnd(lst);
    
    itr2 = GenListIterPrev(itr2);
    
    if(!GenListIterEquals(itr1, itr2))
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result TestGenListIterGet_N()
{
    genList *lst = NULL;
    testing *t;
    genListIter itr;
    void *item;

    lst = GenDLListCreate();
    t = CreateTestingElement(4);
    GenDLListPushHead(lst, t);
    
    itr = GenListIterBegin(lst);
    item = GenListIterGet(itr);
    
    if(!item || ((testing*)item)->m_a != t->m_a)
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}

result TestGenListIterGet_listEmpty()
{
    genList *lst = NULL;
    genListIter itr;
    void *item;

    lst = GenDLListCreate();
    
    itr = GenListIterBegin(lst);
    item = GenListIterGet(itr);
    
    if(item)
    {
        GenDLListDestroy(lst, DestroyTestingElement);
        return FAIL;
    }
    GenDLListDestroy(lst, DestroyTestingElement);
    return SUCCESS;
}



int main()
{
    TestPrintResult(TestGenDLListCreate_N, "TestGenDLListCreate_N");
    TestPrintResult(TestGenDLListDestroy_N, "TestGenDLListDestroy_N");
    TestPrintResult(TestGenDLListDestroy_Double, "TestGenDLListDestroy_Double");
    TestPrintResult(TestGenDLListDestroy_NULL, "TestGenDLListDestroy_NULL");
    TestPrintResult(TestGenDLListDestroy_Copy, "TestGenDLListDestroy_Copy");
    TestPrintResult(TestGenDLListPushHead_N, "TestGenDLListPushHead_N");
    TestPrintResult(TestGenDLListPushHead_Ten, "TestGenDLListPushHead_Ten");
    TestPrintResult(TestGenDLListPushHead_lstNULL, "TestGenDLListPushHead_lstNULL");
    TestPrintResult(TestGenDLListPushHead_dataNULL, "TestGenDLListPushHead_dataNULL");
    TestPrintResult(TestGenDLListPushTail_N, "TestGenDLListPushTail_N");
    TestPrintResult(TestGenDLListPushTail_Ten, "TestGenDLListPushTail_Ten");
    TestPrintResult(TestGenDLListPushTail_lstNULL, "TestGenDLListPushTail_lstNULL");
    TestPrintResult(TestGenDLListPushTail_dataNULL, "TestGenDLListPushTail_dataNULL");
    TestPrintResult(TestGenDLListPopHead_N, "TestGenDLListPopHead_N");
    TestPrintResult(TestGenDLListPopHead_Ten, "TestGenDLListPopHead_Ten");
    TestPrintResult(TestGenDLListPopHead_lstNULL, "TestGenDLListPopHead_lstNULL");
    TestPrintResult(TestGenDLListPopHead_dataNULL, "TestGenDLListPopHead_dataNULL");
    TestPrintResult(TestGenDLListPopHead_lstEmpty, "TestGenDLListPopHead_lstEmpty");
    TestPrintResult(TestGenDLListPopTail_N, "TestGenDLListPopTail_N");
    TestPrintResult(TestGenDLListPopTail_Ten, "TestGenDLListPopTail_Ten");
    TestPrintResult(TestGenDLListPopTail_lstNULL, "TestGenDLListPopTail_lstNULL");
    TestPrintResult(TestGenDLListPopTail_dataNULL, "TestGenDLListPopTail_dataNULL");
    TestPrintResult(TestGenDLListPopTail_lstEmpty, "TestGenDLListPopTail_lstEmpty");
    TestPrintResult(TestGenDLListCountItems_N, "TestGenDLListCountItems_N");
    TestPrintResult(TestGenDLListCountItems_Ten, "TestGenDLListCountItems_Ten");
    TestPrintResult(TestGenDLListCountItems_listNULL, "TestGenDLListCountItems_listNULL");
    TestPrintResult(TestGenDLListCountItems_listEmpty, "TestGenDLListCountItems_listEmpty");
    TestPrintResult(TestGenDLListIsEmpty_listN, "TestGenDLListIsEmpty_listN");
    TestPrintResult(TestGenDLListIsEmpty_listNULL, "TestGenDLListIsEmpty_listNULL");
    TestPrintResult(TestGenDLListIsEmpty_listEmpty, "TestGenDLListIsEmpty_listEmpty");
    TestPrintResult(TestGenListIterBegin_N, "TestGenListIterBegin_N");
    TestPrintResult(TestGenListIterBegin_NULL, "TestGenListIterBegin_NULL");
    TestPrintResult(TestGenListIterEnd_N, "TestGenListIterEnd_N");
    TestPrintResult(TestGenListIterEnd_NULL, "TestGenListIterEnd_NULL");
    TestPrintResult(TestGenListIterEquals_equals, "TestGenListIterEquals_equals");
    TestPrintResult(TestGenListIterEquals_notEquals, "TestGenListIterEquals_notEquals");
    TestPrintResult(TestGenListIterEquals_aNULL_bN, "TestGenListIterEquals_aNULL_bN");
    TestPrintResult(TestGenListIterEquals_aN_bNULL, "TestGenListIterEquals_aN_bNULL");
    TestPrintResult(TestGenListIterEquals_aNULL_bNULL, "TestGenListIterEquals_aNULL_bNULL");
    TestPrintResult(GenListIterNext_N, "GenListIterNext_N");
    TestPrintResult(GenListIterPrev_N, "GenListIterPrev_N");
    TestPrintResult(TestGenListIterGet_N, "TestGenListIterGet_N");
    TestPrintResult(TestGenListIterGet_listEmpty, "TestGenListIterGet_listEmpty");

    return 0;
}
