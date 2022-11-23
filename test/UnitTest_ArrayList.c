#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Class.h"
#include "Basic.h"
#include "IObject.h"
#include "Object.h"
#include "IUnitTest.h"
#include "ArrayList.h"
#include "MatrixDC.h"
#include "VectorDC.h"
#include "UnitTest_ArrayList.h"

Class UnitTest_ArrayList_Class = {CLASS};

struct _UnitTest_ArrayList
{
    Class* class;
    IUnitTest* iUnitTest;
};

struct _ArrayList
{
    const Class* class;
    IObject* iObject;
    IObject* iObjectContained;
    IList* iList;
    IStack* iStack;
    IQueue* iQueue;
    void** items;
    int size;
    int max_size;   
};

static void _UnitTest_ArrayList_TestAll(void* implementor);

void Test_ArrayList_New_Init_State()
{
    int size, result;
    ArrayList* array_list;
    
    array_list = ArrayList_New(Pointer);
    size = ArrayList_Size(array_list);
    assert(size == 0);
    result = InstanceOf(array_list, ARRAYLIST);
    assert(result == 1);
    result = InstanceOf(array_list, OBJECT);
    assert(result == 1);
    assert(array_list->size == 0);
    assert(array_list->iObjectContained == Pointer);
    array_list = ArrayList_Del(array_list);
    printf("Test_ArrayList_New_Init_State Success.\n");
}

void Test_ArrayList_IObject()
{
    int size, result;
    ArrayList* array_list,* new_list;
    IObject* iObject;
    void* object;
    
    array_list = ArrayList_New(Pointer);
    ArrayList_Add(array_list, &object);
    iObject = ArrayList_GetIObject(array_list);
    object = IObject_New(iObject);
    new_list = (ArrayList*)object;
    size = ArrayList_Size(new_list);
    assert(size == 0);
    result = InstanceOf(object, ARRAYLIST);
    assert(result == 1);
    result = IObject_Equal(iObject, array_list);
    assert(result == 1);
    result = IObject_Copy(iObject, array_list);
    assert(result = 1);
    object = IObject_Del(iObject);
    assert(object == NULL);
    printf("Test_ArrayList_IObject Success.\n");
}

void Test_ArrayList_Add()
{
    ArrayList* array_list;
    int* a1,* a2,* a3,* a4,* a5,* a6,* a7,* a8,* a9,* a10;
    
    array_list = ArrayList_New(Pointer);
    ArrayList_Add(array_list, &a1);
    ArrayList_Add(array_list, &a2);
    ArrayList_Add(array_list, &a3);
    ArrayList_Add(array_list, &a4);
    ArrayList_Add(array_list, &a5);
    ArrayList_Add(array_list, &a6);
    ArrayList_Add(array_list, &a7);
    ArrayList_Add(array_list, &a8);
    ArrayList_Add(array_list, &a9);
    ArrayList_Add(array_list, &a10);
    assert(*(int**)*(array_list->items) == a1);
    assert(*(int**)*(array_list->items+1) == a2);
    assert(*(int**)*(array_list->items+2) == a3);
    assert(*(int**)*(array_list->items+3) == a4);
    assert(*(int**)*(array_list->items+4) == a5);
    assert(*(int**)*(array_list->items+5) == a6);
    assert(*(int**)*(array_list->items+6) == a7);
    assert(*(int**)*(array_list->items+7) == a8);
    assert(*(int**)*(array_list->items+8) == a9);
    assert(*(int**)*(array_list->items+9) == a10);
    ArrayList_Del(array_list);
    printf("Test_ArrayList_Add Success.\n");
}

void Test_ArrayList_Insert()
{
    ArrayList* array_list;
    int* a0,* a1,* a2,* a3,* a4,* a5,* a6,* a7,* a8,* a9;
    
    array_list = ArrayList_New(Pointer);
    ArrayList_Insert(array_list, 0, &a9);
    ArrayList_Insert(array_list, 0, &a1);
    ArrayList_Insert(array_list, 1, &a2);
    ArrayList_Insert(array_list, 2, &a3);
    ArrayList_Insert(array_list, 0, &a0);
    ArrayList_Insert(array_list, 4, &a4);
    ArrayList_Insert(array_list, 5, &a5);
    ArrayList_Insert(array_list, 6, &a6);
    ArrayList_Insert(array_list, 7, &a7);
    ArrayList_Insert(array_list, 8, &a8);
    assert(*(int**)*(array_list->items) == a0);
    assert(*(int**)*(array_list->items+1) == a1);
    assert(*(int**)*(array_list->items+2) == a2);
    assert(*(int**)*(array_list->items+3) == a3);
    assert(*(int**)*(array_list->items+4) == a4);
    assert(*(int**)*(array_list->items+5) == a5);
    assert(*(int**)*(array_list->items+6) == a6);
    assert(*(int**)*(array_list->items+7) == a7);
    assert(*(int**)*(array_list->items+8) == a8);
    assert(*(int**)*(array_list->items+9) == a9);
    assert(array_list->size == 10);
    ArrayList_Del(array_list);    
    printf("Test_ArrayList_Insert Success.\n");
}

void Test_ArrayList_Remove()
{
    register int i;
    ArrayList* array_list;
    int* a0,* a1,* a2,* a3,* a4,* a5,* a6,* a7,* a8,* a9;
    
    array_list = ArrayList_New(Pointer);
    ArrayList_Insert(array_list, 0, &a9);
    ArrayList_Insert(array_list, 0, &a1);
    ArrayList_Insert(array_list, 1, &a2);
    ArrayList_Insert(array_list, 2, &a3);
    ArrayList_Insert(array_list, 0, &a0);
    ArrayList_Insert(array_list, 4, &a4);
    ArrayList_Insert(array_list, 5, &a5);
    ArrayList_Insert(array_list, 6, &a6);
    ArrayList_Insert(array_list, 7, &a7);
    ArrayList_Insert(array_list, 8, &a8);
    ArrayList_Remove(array_list, 0);
    assert(*(int**)*(array_list->items) == a1);
    ArrayList_Remove(array_list, 8);
    assert(*(int**)*(array_list->items+6) == a7);
    ArrayList_Remove(array_list, 4);
    assert(*(int**)*(array_list->items+4) == a6);
    ArrayList_Del(array_list);    
    printf("Test_ArrayList_Remove Success.\n");
}

void Test_ArrayList_Size()
{
    int size;
    ArrayList* array_list;
    int* a9,* a0;
    
    array_list = ArrayList_New(Pointer);
    size = ArrayList_Size(array_list);
    assert(size == 0);
    ArrayList_Insert(array_list, 0, &a9);
    size = ArrayList_Size(array_list);
    assert(size == 1);
    ArrayList_Add(array_list, &a0);
    size = ArrayList_Size(array_list);
    assert(size == 2);
    ArrayList_Remove(array_list, 0);
    size = ArrayList_Size(array_list);
    assert(size == 1);
    ArrayList_Clear(array_list);
    size = ArrayList_Size(array_list);
    assert(size == 0);
    ArrayList_Del(array_list);    
    printf("Test_ArrayList_Size Success.\n");
}

void Test_ArrayList_Get()
{
    int* result;
    ArrayList* array_list;
    int* a0,* a1;
    
    array_list = ArrayList_New(Pointer);
    ArrayList_Add(array_list, &a0);
    ArrayList_Add(array_list, &a1);
    result = *(int**)ArrayList_Get(array_list, 0);
    assert(result == a0);
    result = *(int**)ArrayList_Get(array_list, 1);
    assert(result == a1);
    ArrayList_Del(array_list);
    printf("Test_ArrayList_Get Success.\n");
}

void Test_ArrayList_MatrixDC_Server_Add()
{
    int size;
    ArrayList* array_list;
    MatrixDC* matrix_server;
    
    matrix_server = MatrixDC_New(2,2);
    array_list = ArrayList_New(MatrixDC_GetIObject(matrix_server));
    ArrayList_Add(array_list, matrix_server);
    size = ArrayList_Size(array_list);
    assert(size == 1);
    ArrayList_Del(array_list);
    MatrixDC_Del(matrix_server);
    printf("Test_ArrayList_MatrixDC_Server_Add Success.\n");
}

void Test_ArrayList_MatrixDC_Server_Clear_Add()
{
    int size;
    ArrayList* array_list;
    MatrixDC* matrix_server;
    
    matrix_server = MatrixDC_New(2,2);
    array_list = ArrayList_New(MatrixDC_GetIObject(matrix_server));
    ArrayList_Add(array_list, matrix_server);
    size = ArrayList_Size(array_list);
    ArrayList_Clear(array_list);
    ArrayList_Add(array_list, matrix_server);
    ArrayList_Del(array_list);
    MatrixDC_Del(matrix_server);
    printf("Test_ArrayList_MatrixDC_Server_Add Success.\n");
}

void Test_ArrayList_VectorDC_Add()
{
    int size;
    ArrayList* array_list;
    VectorDC* vector;

    vector = VectorDC_New(3);
    array_list = ArrayList_New(VectorDC_GetIObject(vector));
    ArrayList_Clear(array_list);
    ArrayList_Add(array_list, vector);
    size = ArrayList_Size(array_list);
    assert(size == 1);
    ArrayList_Del(array_list);
    VectorDC_Del(vector);
    printf("Test_ArrayList_VectorDC_Add Success.\n");
}

void Test_ArrayList_RemoveAndInsert()
{
    ArrayList* array_list;
    int* a1,* a2,* a3,* a4;
    int* result;
    int size;

    array_list = ArrayList_New(Pointer);
    ArrayList_Add(array_list, &a1);
    ArrayList_Add(array_list, &a2);
    ArrayList_Add(array_list, &a3);
    ArrayList_Remove(array_list, 0);
    size = ArrayList_Size(array_list);
    assert(size == 2);
    ArrayList_Insert(array_list, 1, &a4);
    size = ArrayList_Size(array_list);
    assert(size == 3);
    result = *(int**)ArrayList_Get(array_list, 0);
    assert(result == a2);
    result = *(int**)ArrayList_Get(array_list, 1);
    assert(result == a4);
    result = *(int**)ArrayList_Get(array_list, 2);
    assert(result == a3);
    printf("Test_ArrayList_RemoveAndInsert Success.\n");
}

UnitTest_ArrayList* UnitTest_ArrayList_New()
{
    UnitTest_ArrayList* unit_test;
    
    unit_test = (UnitTest_ArrayList*)malloc(sizeof(UnitTest_ArrayList)+sizeof(IUnitTest));
    unit_test->class = UNITTEST_ARRAYLIST;
    unit_test->iUnitTest = (IUnitTest*)(unit_test+1);
    unit_test->iUnitTest->implementor = unit_test;
    unit_test->iUnitTest->TestAll = _UnitTest_ArrayList_TestAll;
    
    return unit_test;
}

UnitTest_ArrayList* UnitTest_ArrayList_Del(UnitTest_ArrayList* this)
{
    free(this);
    
    return NULL;
}

IUnitTest* UnitTest_ArrayList_GetIUnitTest(UnitTest_ArrayList* this)
{
    return this->iUnitTest;
}

void UnitTest_ArrayList_TestAll(UnitTest_ArrayList* this)
{
    Test_ArrayList_New_Init_State();
    Test_ArrayList_IObject();
    Test_ArrayList_Add();
    Test_ArrayList_Get();
    Test_ArrayList_Insert();
    Test_ArrayList_Remove();
    Test_ArrayList_Size();
    Test_ArrayList_MatrixDC_Server_Add();
    Test_ArrayList_VectorDC_Add();
    Test_ArrayList_RemoveAndInsert();
}

static void _UnitTest_ArrayList_TestAll(void* implementor)
{
    UnitTest_ArrayList* unit_test;
    
    unit_test = (UnitTest_ArrayList*)implementor;
    UnitTest_ArrayList_TestAll(unit_test);
}

