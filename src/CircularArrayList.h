#ifndef _CIRCULARARRAYLIST_H_
#define _CIRCULARARRAYLIST_H_

#define CIRCULARARRAYLIST &CircularArrayList_Class

typedef struct _Class Class;
typedef struct _IObject IObject;
typedef struct _IList IList;
typedef struct _IStack IStack;
typedef struct _IQueue IQueue;
typedef struct _CircularArrayList CircularArrayList;

extern Class CircularArrayList_Class;

extern CircularArrayList* CircularArrayList_New(IObject* iObjectContained);

extern CircularArrayList* CircularArrayList_Del(CircularArrayList* this);

extern IObject* CircularArrayList_GetIObject(CircularArrayList* this);

extern IList* CircularArrayList_GetIList(CircularArrayList* this);

extern IStack* CircularArrayList_GetIStack(CircularArrayList* this);

extern IQueue* CircularArrayList_GetIQueue(CircularArrayList* this);

extern CircularArrayList* CircularArrayList_Clear(CircularArrayList* this);

extern void* CircularArrayList_Get(CircularArrayList* this, int index);

extern int CircularArrayList_Index(CircularArrayList* this, void* item);

extern CircularArrayList* CircularArrayList_Insert(CircularArrayList* this, int index, void* item);

extern CircularArrayList* CircularArrayList_Add(CircularArrayList* this, void* item);

extern CircularArrayList* CircularArrayList_Remove(CircularArrayList* this, int index);

extern int CircularArrayList_Size(CircularArrayList* this);

#endif /*_CIRCULARARRAYLIST_H_*/
