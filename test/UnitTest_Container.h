#ifndef _UNITTEST_CONTAINER_H_
#define _UNITTEST_CONTAINER_H_

#define UNITTEST_CONTAINER &UnitTest_Container_Class

typedef struct _Class Class;
typedef struct _IUnitTest IUnitTest;
typedef struct _UnitTest_Container UnitTest_Container;

extern Class UnitTest_Container_Class;

extern UnitTest_Container* UnitTest_Container_New();

extern UnitTest_Container* UnitTest_Container_Del(UnitTest_Container* this);

extern IUnitTest* UnitTest_Container_GetIUnitTest(UnitTest_Container* this);

extern void UnitTest_Container_TestAll(UnitTest_Container* this);

#endif /*_UNITTEST_CONTAINER_H_*/