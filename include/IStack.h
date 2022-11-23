#ifndef _ISTACK_H_
#define _ISTACK_H_

typedef struct _IStack IStack;

struct _IStack
{
    void* implementor;
    IStack* (*Clear)(void* implementor);
    void* (*Get)(void* implementor);
    IStack* (*Push)(void* implementor, void* item);
    IStack* (*Pop)(void* implementor);
    int (*Size)(void* implementor);
};

extern IStack* IStack_Clear(IStack* this);

extern void* IStack_Get(IStack* this);

extern IStack* IStack_Push(IStack* this, void* item);

extern IStack* IStack_Pop(IStack* this);

extern int IStack_Size(IStack* this);

#endif /*_ISTACK_H_*/
