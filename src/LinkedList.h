#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define LINKEDLIST &LinkedList_Class

typedef struct _IObject IObject;
typedef struct _IList IList;
typedef struct _IStack IStack;
typedef struct _IQueue IQueue;
typedef struct _Class Class;
typedef struct _LinkedList LinkedList;
typedef void (*Func)(void* data, void* user_data);
typedef int (*CompareFunc)(void* a, void* b, void* user_data);

extern Class LinkedList_Class;

extern LinkedList* LinkedList_New(IObject* iObjectContained);

extern LinkedList* LinkedList_Del(LinkedList* this);

extern IObject* LinkedList_GetIObject(LinkedList* this);

extern IList* LinkedList_GetIList(LinkedList* this);

extern IStack* LinkedList_GetIStack(LinkedList* this);

extern IQueue* LinkedList_GetIQueue(LinkedList* this);

extern LinkedList* LinkedList_Clear(LinkedList* this);

extern void* LinkedList_Get(LinkedList* this, int index);

extern void* LinkedList_last(LinkedList* this);

extern int LinkedList_Index(LinkedList* this, void* item);

extern LinkedList* LinkedList_Insert(LinkedList* this, int index, void* item);

extern LinkedList* LinkedList_InsertSorted(LinkedList* this, void* item, CompareFunc compare_func, void* user_data);

extern LinkedList* LinkedList_Add(LinkedList* this, void* item);

extern LinkedList* LinkedList_AddFirst(LinkedList* this, void* item);

extern LinkedList* LinkedList_Remove(LinkedList* this, int index);

extern int LinkedList_Size(LinkedList* this);

extern LinkedList* LinkedList_Reverse(LinkedList* this);

extern LinkedList* LinkedList_ForEach(LinkedList* this, Func func, void* user_data);

extern LinkedList* LinkedList_Sort(LinkedList* this, CompareFunc compare_func, void* user_data);

#endif /*_LINKEDLIST_H_*/
