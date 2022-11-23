#ifndef _ILIST_H_
#define _ILIST_H_

typedef struct _IList IList;

struct _IList
{
    void* implementor;
    IList* (*Clear)(void* implementor);
    void* (*Get)(void* implementor, int index);
    int (*Index)(void* implementor, void* item);
    IList* (*Insert)(void* implementor, int index, void* item);
    IList* (*Add)(void* implementor, void* item);
    IList* (*Remove)(void* implementor, int index);
    int (*Size)(void* implementor);
};

extern IList* IList_Clear(IList* this);

extern void* IList_Get(IList* this, int index);

extern int IList_Index(IList* this, void* item);

extern IList* IList_Insert(IList* this, int index, void* item);

extern IList* IList_Add(IList* this, void* item);

extern IList* IList_Remove(IList* this, int index);

extern int IList_Size(IList* this);

#endif /*_ILIST_H_*/
