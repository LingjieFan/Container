#ifndef _UNITTEST_HASHTABLE_H_
#define _UNITTEST_HASHTABLE_H_

#define UNITTEST_HASHTABLE &UnitTest_HashTable_Class

typedef struct _Class Class;
typedef struct _IUnitTest IUnitTest;
typedef struct _UnitTest_HashTable UnitTest_HashTable;

extern Class UnitTest_HashTable_Class;

extern UnitTest_HashTable* UnitTest_HashTable_New();

extern UnitTest_HashTable* UnitTest_HashTable_Del(UnitTest_HashTable* this);

extern IUnitTest* UnitTest_HashTable_GetIUnitTest(UnitTest_HashTable* this);

extern void UnitTest_HashTable_TestAll(UnitTest_HashTable* this);

#endif /*_UNITTEST_HASHTABLE_H_*/
