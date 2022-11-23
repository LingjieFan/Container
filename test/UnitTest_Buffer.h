#ifndef _UNITTEST_BUFFER_H_
#define _UNITTEST_BUFFER_H_

#define UNITTEST_BUFFER &UnitTest_Buffer_Class

typedef struct _Class Class;
typedef struct _IUnitTest IUnitTest;
typedef struct _UnitTest_Buffer UnitTest_Buffer;

extern Class UnitTest_Buffer_Class;

extern UnitTest_Buffer* UnitTest_Buffer_New();

extern UnitTest_Buffer* UnitTest_Bufffer_Del(UnitTest_Buffer* this);

extern IUnitTest* UnitTest_Buffer_GetIUnitTest(UnitTest_Buffer* this);

extern void UnitTest_Buffer_TestAll(UnitTest_Buffer* this);

#endif /*_UNITTEST_BUFFER_H_*/
