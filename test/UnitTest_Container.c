#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Class.h"
#include "IUnitTest.h"
#include "UnitTest_ArrayList.h"
#include "UnitTest_HashTable.h"
#include "UnitTest_Container.h"
#include "UnitTest_Buffer.h"

Class UnitTest_Container_Class = {CLASS};

struct _UnitTest_Container
{
    Class* class;
    IUnitTest* iUnitTest;
    UnitTest_ArrayList* unitTest_arrayList;
    UnitTest_HashTable* unitTest_hashtable;
    UnitTest_Buffer* unitTest_buffer;
};

void _UnitTest_Container_TestAll(void* implementor);

UnitTest_Container* UnitTest_Container_New()
{
    UnitTest_Container* unit_test;
    
    unit_test = (UnitTest_Container*)malloc(sizeof(UnitTest_Container)+sizeof(IUnitTest));
    unit_test->class = UNITTEST_CONTAINER;
    unit_test->iUnitTest = (IUnitTest*)(unit_test+1);
    unit_test->iUnitTest->implementor = unit_test;
    unit_test->iUnitTest->TestAll = _UnitTest_Container_TestAll;
    unit_test->unitTest_arrayList = UnitTest_ArrayList_New();
    unit_test->unitTest_hashtable = UnitTest_HashTable_New();
    unit_test->unitTest_buffer = UnitTest_Buffer_New();
    
    return unit_test;
}

UnitTest_Container* UnitTest_Container_Del(UnitTest_Container* this)
{
    UnitTest_ArrayList_Del(this->unitTest_arrayList);
    free(this);
    
    return NULL;
}

IUnitTest* UnitTest_Container_GetIUnitTest(UnitTest_Container* this)
{
    return this->iUnitTest;
}

void UnitTest_Container_TestAll(UnitTest_Container* this)
{
    UnitTest_ArrayList_TestAll(this->unitTest_arrayList);
    UnitTest_HashTable_TestAll(this->unitTest_hashtable);
    UnitTest_Buffer_TestAll(this->unitTest_buffer);
}

void _UnitTest_Container_TestAll(void* implementor)
{
    UnitTest_ArrayList* unit_test;
    
    unit_test = (UnitTest_ArrayList*)implementor;
    UnitTest_ArrayList_TestAll(unit_test);
}
