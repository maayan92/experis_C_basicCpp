#include "genHashMap.h"
#include <stdio.h>
#include <stdlib.h>  /* for free() */


typedef enum result
{
    SUCCESS,
    FAIL
}result;

static void TestPrintResult(result (*_funcToTest)(void), char *_funcName)
{
    result r = _funcToTest();
    printf("%-45s%s\n", _funcName, r==SUCCESS? "SUCCESS": "FAIL");
}

size_t HashOrgenizeBy(void *_num)
{
    if(*(int*)_num < 0)
    {
        *(int*)_num *= -1;
    }
    
    return *(int*)_num * 2;
}

int HashCompare(void *_a, void *_b)
{
    return *(int*)_a == *(int*)_b;
}

int PrintElement(const void* _key, void* _value, void* _context)
{
    printf("key: %d, value: %d\n", *(int*)_key, *(int*)_value);
    return 1;
}


result TestGenHashMapCreate_N()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    
    if(!mp)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenHashMapCreate_sizeZero_funcN_funcN()
{
    genHashMap *mp = GenHashMapCreate(0, HashOrgenizeBy, HashCompare);
    
    if(mp)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenHashMapCreate_sizeN_funcNULL_funcN()
{
    genHashMap *mp = GenHashMapCreate(10, NULL, HashCompare);
    
    if(mp)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenHashMapCreate_sizeN_funcN_funcNULL()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, NULL);
    
    if(mp)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenHashMapDestroy_N()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    int a=0, b=1, c=2, d=3, e=4;
    
    GenHashMapInsert(mp, &a, &a);
    GenHashMapInsert(mp, &b, &a);
    GenHashMapInsert(mp, &c, &a);
    GenHashMapInsert(mp, &d, &a);
    GenHashMapInsert(mp, &e, &b);
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapDestroy_hashEmpty()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapDestroy_double()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    GenHashMapDestroy(&mp, NULL, NULL);
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapDestroy_hashNULL()
{
    GenHashMapDestroy(NULL, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapInsert_N()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    
    if(GenHashMapInsert(mp, &k, &v) != MAP_SUCCESS)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapInsert_five()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    int a=0, b=1, c=2, d=3, e=4;
    
    if(GenHashMapInsert(mp, &a, &a) != MAP_SUCCESS)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    if(GenHashMapInsert(mp, &b, &a) != MAP_SUCCESS)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    if(GenHashMapInsert(mp, &c, &a) != MAP_SUCCESS)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    if(GenHashMapInsert(mp, &d, &a) != MAP_SUCCESS)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    if(GenHashMapInsert(mp, &e, &a) != MAP_SUCCESS)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapInsert_Dup()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapInsert(mp, &k, &v) != MAP_KEY_DUPLICATE_ERROR)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapInsert_keyNULL()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int v=4;
    
    if(GenHashMapInsert(mp, NULL, &v) != MAP_KEY_NULL_ERROR)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapInsert_valueNULL()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9;
    
    if(GenHashMapInsert(mp, &k, NULL) != MAP_SUCCESS)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapInsert_hashNULL()
{
    int k=9, v=4;
    
    if(GenHashMapInsert(NULL, &k, &v) != MAP_UNINITIALIZED_ERROR)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenHashMapRemove_N()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    int *pk, *pv;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapRemove(mp, &k, (void**)&pk, (void**)&pv) != MAP_SUCCESS || *pk != k || *pv != v)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapRemove_notInHash()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    int *pk, *pv;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapRemove(mp, &v, (void**)&pk, (void**)&pv) != MAP_KEY_NOT_FOUND_ERROR)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapRemove_hashEmpty()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9;
    int *pk, *pv;
    
    if(GenHashMapRemove(mp, &k, (void**)&pk, (void**)&pv) != MAP_KEY_NOT_FOUND_ERROR)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapRemove_fromFive()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    int a=0, b=1, c=2, d=3, e=4;
    int *pk, *pv;
    
    GenHashMapInsert(mp, &a, &a);
    GenHashMapInsert(mp, &b, &a);
    GenHashMapInsert(mp, &c, &a);
    GenHashMapInsert(mp, &d, &a);
    GenHashMapInsert(mp, &e, &b);
    if(GenHashMapRemove(mp, &e, (void**)&pk, (void**)&pv) != MAP_SUCCESS || *pk != e || *pv != b)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapRemove_hashNULL()
{
    int k=9;
    int *pk, *pv;
    
    if(GenHashMapRemove(NULL, &k, (void**)&pk, (void**)&pv) != MAP_UNINITIALIZED_ERROR)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenHashMapRemove_searchKeyNULL()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    int *pk, *pv;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapRemove(mp, NULL, (void**)&pk, (void**)&pv) != MAP_KEY_NULL_ERROR)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapRemove_pKeyNULL()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    int *pv;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapRemove(mp, &k, NULL, (void**)&pv) != MAP_SUCCESS || *pv != v)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapRemove_pValueNULL()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    int *pk;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapRemove(mp, &k, (void**)&pk, NULL) != MAP_SUCCESS || *pk != k)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapFind_N()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    int *pv;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapFind(mp, &k, (void**)&pv) != MAP_SUCCESS || *pv != v)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapFind_notInHash()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    int *pv;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapFind(mp, &v, (void**)&pv) != MAP_KEY_NOT_FOUND_ERROR)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapFind_hashEmpty()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9;
    int *pv;
    
    if(GenHashMapFind(mp, &k, (void**)&pv) != MAP_KEY_NOT_FOUND_ERROR)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapFind_fromFive()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    int a=0, b=1, c=2, d=3, e=4;
    int *pv;
    
    GenHashMapInsert(mp, &a, &a);
    GenHashMapInsert(mp, &b, &a);
    GenHashMapInsert(mp, &c, &a);
    GenHashMapInsert(mp, &d, &a);
    GenHashMapInsert(mp, &e, &b);
    if(GenHashMapFind(mp, &e, (void**)&pv) != MAP_SUCCESS || *pv != b)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapFind_hashNULL()
{
    int k=9;
    int *pv;
    
    if(GenHashMapFind(NULL, &k, (void**)&pv) != MAP_UNINITIALIZED_ERROR)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenHashMapFind_searchKeyNULL()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    int *pv;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapFind(mp, NULL, (void**)&pv) != MAP_KEY_NULL_ERROR)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapFind_pValueNULL()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    int k=9, v=4;
    
    GenHashMapInsert(mp, &k, &v);
    if(GenHashMapFind(mp, &k, NULL) != MAP_SUCCESS)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapNumOfElements_N()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    int a=0, b=1, c=2, d=3, e=4;
    
    GenHashMapInsert(mp, &a, &a);
    GenHashMapInsert(mp, &b, &a);
    GenHashMapInsert(mp, &c, &a);
    GenHashMapInsert(mp, &d, &a);
    GenHashMapInsert(mp, &e, &b);
    if(GenHashMapNumOfElements(mp) != 5)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapNumOfElements_afterRemove()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    int a=0, b=1, c=2, d=3, e=4;
    int *pk, *pv;
    
    GenHashMapInsert(mp, &a, &a);
    GenHashMapInsert(mp, &b, &a);
    GenHashMapInsert(mp, &c, &a);
    GenHashMapInsert(mp, &d, &a);
    GenHashMapInsert(mp, &e, &b);
    GenHashMapRemove(mp, &e, (void**)&pk, (void**)&pv);
    if(GenHashMapNumOfElements(mp) != 4)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapNumOfElements_hashEmpty()
{
    genHashMap *mp = GenHashMapCreate(10, HashOrgenizeBy, HashCompare);
    
    if(GenHashMapNumOfElements(mp) != 0)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}
result TestGenHashMapNumOfElements_hashNULL()
{
    if(GenHashMapNumOfElements(NULL) != 0)
    {
        return FAIL;
    }
    return SUCCESS;
}

result TestGenHashMapGetStatistics_N()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    mapStats stats;
    int a=0, b=2, c=5, d=3, e=6, f=12;
    
    GenHashMapInsert(mp, &a, &a);
    GenHashMapInsert(mp, &b, &a);
    GenHashMapInsert(mp, &c, &a);
    GenHashMapInsert(mp, &d, &a);
    GenHashMapInsert(mp, &e, &a);
    GenHashMapInsert(mp, &f, &a);
    stats = GenHashMapGetStatistics(mp);
    
    if(stats.m_numberOfLists != 2 || stats.m_numberOfElements != 6 || stats.m_maxListLength != 4 || stats.m_averageListLength != 3)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapForEach_N()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    int a=0, b=2, c=5, d=3, e=6, f=12;
    
    GenHashMapInsert(mp, &a, &a);
    GenHashMapInsert(mp, &b, &b);
    GenHashMapInsert(mp, &c, &c);
    GenHashMapInsert(mp, &d, &d);
    GenHashMapInsert(mp, &e, &e);
    GenHashMapInsert(mp, &f, &f);
    
    if(GenHashMapForEach(mp, PrintElement, NULL) != 6)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapForEach_hashEmpty()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    if(GenHashMapForEach(mp, PrintElement, NULL) != 0)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapForEach_funcNULL()
{
    genHashMap *mp = GenHashMapCreate(3, HashOrgenizeBy, HashCompare);
    if(GenHashMapForEach(mp, NULL, NULL) != 0)
    {
        GenHashMapDestroy(&mp, NULL, NULL);
        return FAIL;
    }
    GenHashMapDestroy(&mp, NULL, NULL);
    return SUCCESS;
}

result TestGenHashMapForEach_hashNULL()
{
    if(GenHashMapForEach(NULL, PrintElement, NULL) != 0)
    {
        return FAIL;
    }
    return SUCCESS;
}



int main()
{
    TestPrintResult(TestGenHashMapCreate_N, "TestGenHashMapCreate_N");
    TestPrintResult(TestGenHashMapCreate_sizeZero_funcN_funcN, "TestGenHashMapCreate_sizeZero_funcN_funcN");
    TestPrintResult(TestGenHashMapCreate_sizeN_funcNULL_funcN, "TestGenHashMapCreate_sizeN_funcNULL_funcN");
    TestPrintResult(TestGenHashMapCreate_sizeN_funcN_funcNULL, "TestGenHashMapCreate_sizeN_funcN_funcNULL");
    TestPrintResult(TestGenHashMapDestroy_N, "TestGenHashMapDestroy_N");
    TestPrintResult(TestGenHashMapDestroy_hashEmpty, "TestGenHashMapDestroy_hashEmpty");
    TestPrintResult(TestGenHashMapDestroy_double, "TestGenHashMapDestroy_double");
    TestPrintResult(TestGenHashMapDestroy_hashNULL, "TestGenHashMapDestroy_hashNULL");
    TestPrintResult(TestGenHashMapInsert_N, "TestGenHashMapInsert_N");
    TestPrintResult(TestGenHashMapInsert_five, "TestGenHashMapInsert_five");
    TestPrintResult(TestGenHashMapInsert_Dup, "TestGenHashMapInsert_Dup");
    TestPrintResult(TestGenHashMapInsert_keyNULL, "TestGenHashMapInsert_keyNULL");
    TestPrintResult(TestGenHashMapInsert_valueNULL, "TestGenHashMapInsert_valueNULL");
    TestPrintResult(TestGenHashMapInsert_hashNULL, "TestGenHashMapInsert_hashNULL");
    TestPrintResult(TestGenHashMapRemove_N, "TestGenHashMapRemove_N");
    TestPrintResult(TestGenHashMapRemove_notInHash, "TestGenHashMapRemove_notInHash");
    TestPrintResult(TestGenHashMapRemove_hashEmpty, "TestGenHashMapRemove_hashEmpty");
    TestPrintResult(TestGenHashMapRemove_fromFive, "TestGenHashMapRemove_fromFive");
    TestPrintResult(TestGenHashMapRemove_hashNULL, "TestGenHashMapRemove_hashNULL");
    TestPrintResult(TestGenHashMapRemove_searchKeyNULL, "TestGenHashMapRemove_searchKeyNULL");
    TestPrintResult(TestGenHashMapRemove_pKeyNULL, "TestGenHashMapRemove_pKeyNULL");
    TestPrintResult(TestGenHashMapRemove_pValueNULL, "TestGenHashMapRemove_pValueNULL");
    TestPrintResult(TestGenHashMapFind_N, "TestGenHashMapFind_N");
    TestPrintResult(TestGenHashMapFind_notInHash, "TestGenHashMapFind_notInHash");
    TestPrintResult(TestGenHashMapFind_hashEmpty, "TestGenHashMapFind_hashEmpty");
    TestPrintResult(TestGenHashMapFind_fromFive, "TestGenHashMapFind_fromFive");
    TestPrintResult(TestGenHashMapFind_hashNULL, "TestGenHashMapFind_hashNULL");
    TestPrintResult(TestGenHashMapFind_searchKeyNULL, "TestGenHashMapFind_searchKeyNULL");
    TestPrintResult(TestGenHashMapFind_pValueNULL, "TestGenHashMapFind_pValueNULL");
    TestPrintResult(TestGenHashMapNumOfElements_N, "TestGenHashMapNumOfElements_N");
    TestPrintResult(TestGenHashMapNumOfElements_afterRemove, "TestGenHashMapNumOfElements_afterRemove");
    TestPrintResult(TestGenHashMapNumOfElements_hashEmpty, "TestGenHashMapNumOfElements_hashEmpty");
    TestPrintResult(TestGenHashMapNumOfElements_hashNULL, "TestGenHashMapNumOfElements_hashNULL");
    TestPrintResult(TestGenHashMapGetStatistics_N, "TestGenHashMapGetStatistics_N");
    TestPrintResult(TestGenHashMapForEach_N, "TestGenHashMapForEach_N");
    TestPrintResult(TestGenHashMapForEach_hashEmpty, "TestGenHashMapForEach_hashEmpty");
    TestPrintResult(TestGenHashMapForEach_funcNULL, "TestGenHashMapForEach_funcNULL");
    TestPrintResult(TestGenHashMapForEach_hashNULL, "TestGenHashMapForEach_hashNULL");
    
    return 0;
}
