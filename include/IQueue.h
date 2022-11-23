#ifndef _IQUEUE_H_
#define _IQUEUE_H_

typedef struct _IQueue IQueue;

struct _IQueue
{
    void* implementor;
    IQueue* (*Clear)(void* implementor);
    void* (*Get)(void* implementor);
    IQueue* (*EnQueue)(void* implementor, void* item);
    IQueue* (*DeQueue)(void* implementor);
    int (*Size)(void* implementor);
};

extern IQueue* IQueue_Clear(IQueue* this);

extern void* IQueue_Get(IQueue* this);

extern IQueue* IQueue_EnQueue(IQueue* this, void* item);

extern IQueue* IQueue_DeQueue(IQueue* this);

extern int IQueue_Size(IQueue* this);

#endif /*_IQUEUE_H_*/
