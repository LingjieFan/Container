#ifndef _UNITTEST_ARRAYLIST_H_
#define _UNITTEST_ARRAYLIST_H_

#define UNITTEST_ARRAYLIST &UnitTest_ArrayList_Class

typedef struct _Class Class;
typedef struct _IUnitTest IUnitTest;
typedef struct _UnitTest_ArrayList UnitTest_ArrayList;

extern Class UnitTest_ArrayList_Class;

extern UnitTest_ArrayList* UnitTest_ArrayList_New();

extern UnitTest_ArrayList* UnitTest_ArrayList_Del(UnitTest_ArrayList* this);

extern IUnitTest* UnitTest_ArrayList_GetIUnitTest(UnitTest_ArrayList* this);

extern void UnitTest_ArrayList_TestAll(UnitTest_ArrayList* this);

#endif /*_UNITTEST_ARRAYLIST_H_*/