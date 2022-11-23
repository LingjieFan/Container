#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

#define ARRAYLIST &ArrayList_Class

typedef struct _IObject IObject;
typedef struct _IList IList;
typedef struct _IStack IStack;
typedef struct _IQueue IQueue;
typedef struct _Class Class;
typedef struct _ArrayList ArrayList;

extern Class ArrayList_Class;

extern ArrayList* ArrayList_New(IObject* iObjectContained);

extern ArrayList* ArrayList_Del(ArrayList* this);

extern IObject* ArrayList_GetIObject(ArrayList* this);

extern IList* ArrayList_GetIList(ArrayList* this);

extern IStack* ArrayList_GetIStack(ArrayList* this);

extern IQueue* ArrayList_GetIQueue(ArrayList* this);

extern ArrayList* ArrayList_Clear(ArrayList* this);

extern void* ArrayList_Get(ArrayList* this, int index);

extern int ArrayList_Index(ArrayList* this, void* item);

extern ArrayList* ArrayList_Insert(ArrayList* this, int index, void* item);

extern ArrayList* ArrayList_Add(ArrayList* this, void* item);

extern ArrayList* ArrayList_Remove(ArrayList* this, int index);

extern int ArrayList_Size(ArrayList* this);

#endif /*_ARRAYLIST_H_*/
