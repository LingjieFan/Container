#ifndef _DOUBLELINKEDLIST_H_
#define _DOUBLELINKEDLIST_H_

#define DOUBLELINKEDLIST &DoubleLinkedList_Class

typedef struct _IObject IObject;
typedef struct _IList IList;
typedef struct _IQueue IQueue;
typedef struct _Class Class;
typedef struct _DoubleLinkedList DoubleLinkedList;
typedef void (*Func)(void* user, void* user_data);
typedef int (*CompareFunc)(void* a, void* b, void* user_data);

extern Class DoubleLinkedList_Class;

extern DoubleLinkedList* DoubleLinkedList_New(IObject* iObjectContained);

extern DoubleLinkedList* DoubleLinkedList_Del(DoubleLinkedList* this);

extern IObject* DoubleLinkedList_GetIObject(DoubleLinkedList* this);

extern IList* DoubleLinkedList_GetIList(DoubleLinkedList* this);

extern IQueue* DoubleLinkedList_GetIQueue(DoubleLinkedList* this);

extern DoubleLinkedList* DoubleLinkedList_Clear(DoubleLinkedList* this);

extern void* DoubleLinkedList_Get(DoubleLinkedList* this, int index);

extern void* DoubleLinkedList_Last(DoubleLinkedList* this);

extern int DoubleLinkedList_Index(DoubleLinkedList* this, void* item);

extern DoubleLinkedList* DoubleLinkedList_Insert(DoubleLinkedList* this, int index, void* item);

extern DoubleLinkedList* DoubleLinkedList_InsertSorted(DoubleLinkedList* this, void* item, CompareFunc compare_func, void* user_data);

extern DoubleLinkedList* DoubleLinkedList_Add(DoubleLinkedList* this, void* item);

extern DoubleLinkedList* DoubleLinkedList_AddFirst(DoubleLinkedList* this, void* item);

extern DoubleLinkedList* DoubleLinkedList_Remove(DoubleLinkedList* this, int index);

extern int DoubleLinkedList_Size(DoubleLinkedList* this);

extern DoubleLinkedList* DoubleLinkedList_Reverse(DoubleLinkedList* this);

extern DoubleLinkedList* DoubleLinkedList_ForEach(DoubleLinkedList* this, Func func, void* user_data);

extern DoubleLinkedList* DoubleLinkedList_Sort(DoubleLinkedList* this, CompareFunc compare_func, void* user_data);

#endif /*_DOUBLELINKEDLIST_H_*/
