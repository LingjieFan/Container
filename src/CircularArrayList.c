#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "IObject.h"
#include "IStack.h"
#include "IList.h"
#include "IQueue.h"
#include "Class.h"
#include "Object.h"
#include "ArrayList.h"
#include "CircularArrayList.h"

Class CircularArrayList_Class = {OBJECT};

struct _CircularArrayList
{
    Class* class;
    IObject* iObject;
    IObject* iObjectContained;
    IList* iList;
    IStack* iStack;
    IQueue* iQueue;
    int size;
    int max_size;
    void** items;
    int front;
    int rear;
};

void* _CircularArrayList_New(void* implementor);
void* _CircularArrayList_Del(void* implementor);
int _CircularArrayList_Copy(void* implementor, void* object);
int _CircularArrayList_Equal(void* implementor, void* object);
IList* _CircularArrayList_Clear(void* implementor);
void* _CircularArrayList_Get(void* implementor, int index);
int _CircularArrayList_Index(void* implementor, void* item);
IList* _CircularArrayList_Insert(void* implementor, int index, void* item);
IList* _CircularArrayList_Add(void* implementor, void* item);
IList* _CircularArrayList_Remove(void* implementor, int index);
int _CircularArrayList_Size(void* implementor);
IStack* _CircularArrayList_ClearStack(void* implementor);
void* _CircularArrayList_GetTop(void* implementor);
IStack* _CircularArrayList_Push(void* implementor, void* item);
IStack* _CircularArrayList_Pop(void* implementor);
IQueue* _CircularArrayList_ClearQueue(void* implementor);
void* _CircularArrayList_GetFront(void* implementor);
IQueue* _CircularArrayList_EnQueue(void* implementor, void* item);
IQueue* _CircularArrayList_DeQueue(void* implementor);

CircularArrayList* CircularArrayList_New(IObject* iObjectContained)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)malloc(sizeof(CircularArrayList)+\
        sizeof(IObject)+sizeof(IList)+sizeof(IStack)+sizeof(IQueue));
    circular_array_list->class = CIRCULARARRAYLIST;
    circular_array_list->iObject = (IObject*)(circular_array_list+1);
    circular_array_list->iObject->New = _CircularArrayList_New;
    circular_array_list->iObject->Del = _CircularArrayList_Del;
    circular_array_list->iObject->Copy = _CircularArrayList_Copy;
    circular_array_list->iObject->Equal = _CircularArrayList_Equal;
    circular_array_list->iObjectContained = iObjectContained;
    circular_array_list->iList = (IList*)(circular_array_list->iObject+1);
    circular_array_list->iList->Clear = _CircularArrayList_Clear;
    circular_array_list->iList->Get = _CircularArrayList_Get;
    circular_array_list->iList->Index = _CircularArrayList_Index;
    circular_array_list->iList->Insert = _CircularArrayList_Insert;
    circular_array_list->iList->Add = _CircularArrayList_Add;
    circular_array_list->iList->Remove = _CircularArrayList_Remove;
    circular_array_list->iList->Size = _CircularArrayList_Size;
    circular_array_list->iStack = (IStack*)(circular_array_list->iList+1);
    circular_array_list->iStack->Clear = _CircularArrayList_ClearStack;
    circular_array_list->iStack->Get = _CircularArrayList_GetTop;
    circular_array_list->iStack->Push = _CircularArrayList_Push;
    circular_array_list->iStack->Pop = _CircularArrayList_Pop;
    circular_array_list->iStack->Size = _CircularArrayList_Size;
    circular_array_list->iQueue = (IQueue*)(circular_array_list->iStack);
    circular_array_list->iQueue->implementor = circular_array_list;
    circular_array_list->iQueue->Clear = _CircularArrayList_ClearQueue;
    circular_array_list->iQueue->Get = _CircularArrayList_GetFront;
    circular_array_list->iQueue->EnQueue = _CircularArrayList_EnQueue;
    circular_array_list->iQueue->DeQueue = _CircularArrayList_DeQueue;
    circular_array_list->iQueue->Size = _CircularArrayList_Size;
    circular_array_list->size = 0;
    circular_array_list->max_size = 8;
    circular_array_list->items = (void**)calloc(8, sizeof(void*));
    circular_array_list->front = 0;
    circular_array_list->rear = 0;

    return circular_array_list;
}

CircularArrayList* CircularArrayList_Del(CircularArrayList* this)
{
    CircularArrayList_Clear(this);
    free(this->items);
    free(this);
    
    return NULL;
}

IObject* CircularArrayList_GetIObject(CircularArrayList* this)
{
    return this->iObject;
}

IList* CircularArrayList_GetIList(CircularArrayList* this)
{
    return this->iList;
}

IStack* CircularArrayList_GetIStack(CircularArrayList* this)
{
    return this->iStack;
}

CircularArrayList* CircularArrayList_Clear(CircularArrayList* this)
{
    register int i, circular_index;
    void* implementor_contained;

    implementor_contained = this->iObjectContained->implementor;
    for(i=0; i<this->size; i++)
    {
        circular_index = (this->front + i) % this->max_size;
        this->iObjectContained->implementor = *(this->items+circular_index);
        IObject_Del(this->iObjectContained);
    }
    this->iObjectContained->implementor = implementor_contained;
    this->size = 0;
    this->front = 0;
    this->rear = 0;
    
    return this;
}

void* CircularArrayList_Get(CircularArrayList* this, int index)
{
    if(index<this->size)
    {
        int circular_index;
        
        circular_index = (this->front + index) % this->max_size;
        
        return *(this->items+circular_index);
    }
    else
    {
        printf("Error: Index is out of range. size: %d, index: %d", this->size, index);
        
        return NULL;
    }
}

int CircularArrayList_Index(CircularArrayList* this, void* item)
{
    register int i, circular_index, equal;
    void* implementor_contained;
    
    implementor_contained = this->iObjectContained->implementor;
    for(i=0;i<this->size;i++)
    {
        circular_index = (this->front + i) % this->max_size;
        this->iObjectContained->implementor = *(this->items+circular_index);
        equal = IObject_Equal(this->iObjectContained, item);
        if(equal)
        {
            this->iObjectContained->implementor = implementor_contained;
            
            return i;
        }
    }
    this->iObjectContained->implementor = implementor_contained;
    
    return -1;
}

CircularArrayList* CircularArrayList_Insert(CircularArrayList* this, int index, void* item)
{
    register int i;
    void* implementor_contained;
    
    if((this->rear+2)%this->max_size == this->front)
    {
        this->max_size = this->max_size << 1;
        assert(this->max_size>0);
        this->items = realloc(this->items, sizeof(void*)*this->max_size);
        if(this->rear<this->front)
        {
            for(i=this->front;i<this->max_size;i++)
            {
                *(this->items+i+(this->max_size >> 1)) = *(this->items+i);
            }
            this->front += (this->max_size >> 1);
        }
    }
    
    if(this->front == 0)
    {
        ArrayList* array_list;
        
        array_list = (ArrayList*)this;
        ArrayList_Insert(array_list, index, item);
        this->rear += 1;
    }
    else if((this->front > 0)&&(index>(this->size>>1))&&(index<this->size))
    {
        register int circular_index, circular_next_index;
        
        for(i=this->size-1;i>=index;i--)
        {
            circular_index = (this->front+i) % this->max_size;
            circular_next_index = (this->front+i+1) % this->max_size;
            *(this->items+circular_next_index) = *(this->items+circular_index);
        }
        *(this->items+circular_index) = IObject_New(this->iObjectContained);
        implementor_contained = this->iObjectContained->implementor;
        this->iObjectContained->implementor = *(this->items+circular_index);
        IObject_Copy(this->iObjectContained, item);
        this->iObjectContained->implementor = implementor_contained;
        this->rear += 1;
    }
    else if((this->front > 0)&&(index<(this->size>>1))&&(0<index))
    {
        register int circular_index, circular_prior_index;
        
        for(i=0;i<=index;i++)
        {
            circular_index = (this->front+i) % this->max_size;
            circular_prior_index = (this->front+i-1) % this->max_size;
            *(this->items+circular_prior_index) = *(this->items+circular_index);
        } 
        *(this->items+circular_index) = IObject_New(this->iObjectContained);
        implementor_contained = this->iObjectContained->implementor;
        this->iObjectContained->implementor = *(this->items+circular_index);
        IObject_Copy(this->iObjectContained, item);
        this->iObjectContained->implementor = implementor_contained;
        this->front -= 1;        
    }
    else
    {
        printf("Error: index is out of range. size: %d, index: %d", this->size, index);
    }
    
    return this;
}

CircularArrayList* CircularArrayList_Add(CircularArrayList* this, void* item)
{
    register int i;
    void* implementor_contained;
    
    if((this->rear+2)%this->max_size == this->front)
    {
        this->max_size = this->max_size << 1;
        assert(this->max_size>0);
        this->items = realloc(this->items, sizeof(void*)*this->max_size);
        if(this->rear<this->front)
        {
            for(i=this->front;i<this->max_size;i++)
            {
                *(this->items+i+(this->max_size >> 1)) = *(this->items+i);
            }
            this->front += (this->max_size >> 1);
        }
    }

    *(this->items+this->rear) = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = *(this->items+this->rear);
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained; 
    this->rear += 1;
    
    return this;
}

CircularArrayList* CircularArrayList_Remove(CircularArrayList* this, int index)
{
    register int i, circular_index;
    void* implementor_contained;
    
    circular_index = (this->front + index) % this->max_size;
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = *(this->items + circular_index);
    IObject_Del(this->iObjectContained);
    this->iObjectContained->implementor = implementor_contained;
    if((index<(this->size>>1))&&(index>0))
    {
        register int circular_prior_index;
        
        for(i=index;i>0;i++)
        {
            circular_prior_index = (this->front+i-1) % this->max_size;
            circular_index = (this->front+i) % this->max_size;
            *(this->items+circular_index) = *(this->items+circular_prior_index);
        }
        this->front += 1;
    }
    else if(index>=(this->size>>1)&&(index<this->size))
    {
        register int circular_next_index;
        
        for(i=index;i<(this->size-1);i++)
        {
            circular_next_index = (this->front+i+1) % this->max_size;
            circular_index = (this->front+i) % this->max_size;
            *(this->items+circular_index) = *(this->items+circular_next_index);
        }
        this->rear -= 1;
    }
    else
    {
        printf("Error, Index is out of range, size: %d index: %d", this->size, index);
    }
    
    return this;
}

int CircularArrayList_Size(CircularArrayList* this)
{
    return this->size;
}

void* _CircularArrayList_New(void* implementor)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;

    return CircularArrayList_New(circular_array_list->iObjectContained);
}

void* _CircularArrayList_Del(void* implementor)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;

    return CircularArrayList_Del(circular_array_list);
}

int _CircularArrayList_Copy(void* implementor, void* object)
{
    register int i;
    int size1, size2;
    CircularArrayList* list1,* list2;
    void* implementor_contained,* item;

    list1 = (CircularArrayList*)implementor;
    list2 = (CircularArrayList*)object;
    size1 = list1->size;
    size2 = list2->size;
    if(list1->iObjectContained->New == list2->iObjectContained->New)
    {
        CircularArrayList_Clear(list1);
        for(i=0;i<size2;i++)
        {
            item = CircularArrayList_Get(list2, i);
            CircularArrayList_Add(list1, item);
        }
        
        return 1;
    }
    
    return 0;
}

int _CircularArrayList_Equal(void* implementor, void* object)
{
    register int i, equal;
    int size1, size2;
    CircularArrayList* list1,* list2;
    void* implementor_contained,* item;

    list1 = (CircularArrayList*)implementor;
    list2 = (CircularArrayList*)object;
    size1 = list1->size;
    size2 = list2->size;
    
    if((size1 == size2) || (list1->iObjectContained->New == list2->iObjectContained->New))
    {
        implementor_contained = list1->iObjectContained->implementor;
        for(i=0;i<size1;i++)
        {
            list1->iObjectContained->implementor = CircularArrayList_Get(list1, i);
            item = CircularArrayList_Get(list2, i);
            equal = IObject_Equal(list1->iObjectContained, item);
            if(!equal)
            {
                list1->iObjectContained->implementor = implementor_contained;
                
                return 0;
            }
        }
        list1->iObjectContained->implementor = implementor_contained;
        
        return 1;
    }
    else
    {
        return 0;
    }
}

IList* _CircularArrayList_Clear(void* implementor)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Clear(circular_array_list);

    return circular_array_list->iList;
}

void* _CircularArrayList_Get(void* implementor, int index)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;

    return CircularArrayList_Get(circular_array_list, index);
}

int _CircularArrayList_Index(void* implementor, void* item)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;

    return CircularArrayList_Index(circular_array_list, item);
}

IList* _CircularArrayList_Insert(void* implementor, int index, void* item)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Insert(circular_array_list, index, item);

    return circular_array_list->iList;
}

IList* _CircularArrayList_Add(void* implementor, void* item)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Add(circular_array_list, item);

    return circular_array_list->iList;
}

IList* _CircularArrayList_Remove(void* implementor, int index)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Remove(circular_array_list, index);

    return circular_array_list->iList;
}

int _CircularArrayList_Size(void* implementor)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;

    return CircularArrayList_Size(circular_array_list);
}

IStack* _CircularArrayList_ClearStack(void* implementor)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Clear(circular_array_list);

    return circular_array_list->iStack;
}

void* _CircularArrayList_GetTop(void* implementor)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;

    return CircularArrayList_Get(circular_array_list, circular_array_list->size-1);
}

IStack* _CircularArrayList_Push(void* implementor, void* item)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Add(circular_array_list, item);

    return circular_array_list->iStack;
}

IStack* _CircularArrayList_Pop(void* implementor)
{
    CircularArrayList* circular_array_list;

    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Remove(circular_array_list, circular_array_list->size-1);

    return circular_array_list->iStack;
}

IQueue* _CircularArrayList_ClearQueue(void* implementor)
{
    CircularArrayList* circular_array_list;
    
    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Clear(circular_array_list);
    
    return circular_array_list->iQueue;
}

void* _CircularArrayList_GetFront(void* implementor)
{
    CircularArrayList* circular_array_list;
    
    circular_array_list = (CircularArrayList*)implementor;
    
    return CircularArrayList_Get(circular_array_list, 0);
}

IQueue* _CircularArrayList_EnQueue(void* implementor, void* item)
{
    CircularArrayList* circular_array_list;
    
    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Insert(circular_array_list, circular_array_list->size-1, item);
    
    return circular_array_list->iQueue;
}

IQueue* _CircularArrayList_DeQueue(void* implementor)
{
    CircularArrayList* circular_array_list;
    
    circular_array_list = (CircularArrayList*)implementor;
    CircularArrayList_Remove(circular_array_list, 0);
    
    return circular_array_list->iQueue;
}
