#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#define HASHTABLE &HashTable_Class

typedef struct _IObject IObject;
typedef struct _IHash IHash;
typedef struct _Class Class;
typedef struct _HashTable HashTable;

extern Class HashTable_Class;

extern HashTable* HashTable_New(IObject* iObjectKey, IObject* iObjectValue);

extern HashTable* HashTable_Del(HashTable* this);

extern HashTable* HashTable_SetIHash(HashTable* this, IHash* iHash);

extern HashTable* HashTable_Clear(HashTable* this);

extern void* HashTable_Get(HashTable* this, void* key);

extern HashTable* HashTable_Add(HashTable* this, void* key, void* value);

extern HashTable* HashTable_Remove(HashTable* this, void* key);

#endif /*_HASHTABLE_H_*/
