#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Class.h"
#include "Basic.h"
#include "IObject.h"
#include "IUnitTest.h"
#include "IHash.h"
#include "HashTable.h"
#include "UnitTest_HashTable.h"

typedef struct _HashNode HashNode;

Class UnitTest_HashTable_Class = {CLASS};

struct _UnitTest_HashTable
{
    Class* class;
    IUnitTest* iUnitTest;
};

struct _HashTable
{
    Class* class;
    IHash* iHash;   
    IObject* iObjectKey;
    IObject* iObjectValue;
    HashNode** tab;
    int size;
    int tab_size;
};

struct _HashNode
{
    unsigned int hash_key;
    void* key;
    void* value;
    HashNode* next;
};

static void _UnitTest_HashTable_TestAll(void* implementor);

static void Test_HashTable_New()
{
    HashTable* hash_table;

    hash_table = HashTable_New(String, Double);
    assert(hash_table->class == HASHTABLE);
    assert(hash_table->size == 0);
    assert(hash_table->tab_size == 21);
    HashTable_Del(hash_table);
    printf("Test_HashTable_New Success.\n");
}

static void Test_HashTable_Add()
{
    HashTable* hash_table;
    double tmp;

    hash_table = HashTable_New(String, Double);
    tmp = 1;
    HashTable_Add(hash_table, "1", &tmp);
    tmp = 12;
    HashTable_Add(hash_table, "12", &tmp);
    tmp = 123;
    HashTable_Add(hash_table, "123", &tmp);
    HashTable_Del(hash_table);
    printf("Test_HashTable_Add Success.\n");
}

static void Test_HashTable_Get()
{
    HashTable* hash_table;
    double tmp;

    hash_table = HashTable_New(String, Double);
    tmp = 1;
    HashTable_Add(hash_table, "1", &tmp);
    tmp = 12;
    HashTable_Add(hash_table, "12", &tmp);
    tmp = 123;
    HashTable_Add(hash_table, "123", &tmp);
    tmp = *(double*)HashTable_Get(hash_table, "1");
    HashTable_Del(hash_table);
    printf("Test_HashTable_Get Success.\n");
}

UnitTest_HashTable* UnitTest_HashTable_New()
{
    UnitTest_HashTable* unit_test;

    unit_test = (UnitTest_HashTable*)malloc(sizeof(UnitTest_HashTable)+sizeof(IUnitTest));
    unit_test->class = UNITTEST_HASHTABLE;
    unit_test->iUnitTest = (IUnitTest*)(unit_test+1);
    unit_test->iUnitTest->implementor = unit_test;
    unit_test->iUnitTest->TestAll = _UnitTest_HashTable_TestAll;

    return unit_test;
}

UnitTest_HashTable* UnitTest_HashTable_Del(UnitTest_HashTable* this)
{
    free(this);

    return NULL;
}

IUnitTest* UnitTest_HashTable_GetIUnitTest(UnitTest_HashTable* this)
{
    return this->iUnitTest;
}

void UnitTest_HashTable_TestAll(UnitTest_HashTable* this)
{
    Test_HashTable_New();
    Test_HashTable_Add();
    Test_HashTable_Get();
}

static void _UnitTest_HashTable_TestAll(void* implementor)
{
    UnitTest_HashTable* unit_test;

    unit_test = (UnitTest_HashTable*)implementor;
    UnitTest_HashTable_TestAll(unit_test);
}
