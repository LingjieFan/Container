#include <assert.h>
#include <stdlib.h>
#include "IObject.h"
#include "IList.h"
#include "IStack.h"
#include "IQueue.h"
#include "Class.h"
#include "Object.h"
#include "ArrayList.h"

Class ArrayList_Class = {OBJECT};

struct _ArrayList
{
    const Class* class;
    IObject* iObject;
    IObject* iObjectContained;
    IList* iList;
    IStack* iStack;
    IQueue* iQueue;
    void** items;
    int size;
    int max_size;
};

static void* _ArrayList_New(void* implementor);
static void* _ArrayList_Del(void* implementor);
static int _ArrayList_Copy(void* implementor, void* object);
static int _ArrayList_Equal(void* implementor, void* object);
static IList* _ArrayList_Clear(void* implementor);
static void* _ArrayList_Get(void* implementor, int index);
static int _ArrayList_Index(void* implementor, void* item);
static IList* _ArrayList_Insert(void* implementor, int index, void* item);
static IList* _ArrayList_Add(void* implementor, void* item);
static IList* _ArrayList_Remove(void* implementor, int index);
static int _ArrayList_Size(void* implementor);
static IStack* _ArrayList_ClearStack(void* implementor);
static void* _ArrayList_GetTop(void* implementor);
static IStack* _ArrayList_Push(void* implementor, void* item);
static IStack* _ArrayList_Pop(void* implementor);
static IQueue* _ArrayList_ClearQueue(void* implementor);
static void* _ArrayList_GetFront(void* implementor);
static IQueue* _ArrayList_EnQueue(void* implementor, void* item);
static IQueue* _ArrayList_DeQueue(void* implementor);

ArrayList* ArrayList_New(IObject* iObjectContained)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)malloc(sizeof(ArrayList)+sizeof(IObject)\
        +sizeof(IList)+sizeof(IStack)+sizeof(IQueue)); 
    array_list->class = ARRAYLIST;
    array_list->iObject = (IObject*)(array_list+1);
    array_list->iObject->implementor = array_list; 
    array_list->iObject->New = _ArrayList_New;
    array_list->iObject->Del = _ArrayList_Del;
    array_list->iObject->Copy = _ArrayList_Copy;
    array_list->iObject->Equal = _ArrayList_Equal;
    array_list->iObjectContained = iObjectContained;
    array_list->iList = (IList*)(array_list->iObject+1);
    array_list->iList->implementor = array_list;   
    array_list->iList->Clear = _ArrayList_Clear;
    array_list->iList->Get = _ArrayList_Get;
    array_list->iList->Index = _ArrayList_Index;
    array_list->iList->Insert = _ArrayList_Insert;
    array_list->iList->Add = _ArrayList_Add;
    array_list->iList->Remove = _ArrayList_Remove;
    array_list->iList->Size = _ArrayList_Size;
    array_list->iStack = (IStack*)(array_list->iList+1);
    array_list->iStack->implementor = array_list;
    array_list->iStack->Clear = _ArrayList_ClearStack;
    array_list->iStack->Get = _ArrayList_GetTop;
    array_list->iStack->Push = _ArrayList_Push;
    array_list->iStack->Pop = _ArrayList_Pop;
    array_list->iStack->Size = _ArrayList_Size;
    array_list->iQueue = (IQueue*)(array_list->iStack+1);
    array_list->iQueue->implementor = array_list;
    array_list->iQueue->Clear = _ArrayList_ClearQueue;
    array_list->iQueue->Get = _ArrayList_GetFront;
    array_list->iQueue->EnQueue = _ArrayList_EnQueue;
    array_list->iQueue->DeQueue = _ArrayList_DeQueue;
    array_list->iQueue->Size = _ArrayList_Size;
    array_list->size = 0;
    array_list->max_size = 8;
    array_list->items = (void**)calloc(8, sizeof(void*));

    return array_list;
}

ArrayList* ArrayList_Del(ArrayList* this)
{
    ArrayList_Clear(this);
    free(this->items);
    free(this);
    
    return NULL;
}

int ArrayList_Copy(ArrayList* this, void* object)
{
    register int i;
    int size1, size2;
    ArrayList* list1,* list2;
    void* implementor_contained,* item;
    
    list1 = this;
    list2 = (ArrayList*)object;
    size1 = list1->size;
    size2 = list2->size;
    if(list1->iObjectContained->New == list2->iObjectContained->New)
    {
        if(size2>size1) 
        {
            for(i=size1;i<size2;i++)
            {
                item = IObject_New(list1->iObjectContained);
                ArrayList_Add(list1, item);
            }
        }
        else
        {
            for(i=size1-1;i>size2;i--)
            {
                ArrayList_Remove(list1, i);
            }
        }
        implementor_contained = list1->iObjectContained->implementor;
        for(i=0;i<size2;i++)
        {
            list1->iObjectContained->implementor = *(list1->items+i);
            IObject_Copy(list1->iObjectContained, *(list2->items+i));
        }
        list1->iObjectContained->implementor = implementor_contained;
    
        return 1;
    }
    else
    {   
        return 0;
    }    
}

int ArrayList_Equal(ArrayList* this, void* object)
{
    register int i, equal;
    int size1, size2;
    ArrayList* list1,* list2;    
    void* implementor_contained;

    list1 = this;
    list2 = (ArrayList*)object;
    size1 = list1->size;
    size2 = list2->size;
    
    if((size1 == size2) || (list1->iObjectContained->New == list2->iObjectContained->New))
    {
        implementor_contained = list1->iObjectContained->implementor;
        for(i=0;i<size1;i++)
        {
            list1->iObjectContained->implementor = *(list1->items+i);
            equal = IObject_Equal(list1->iObjectContained, *(list2->items+i));
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

IObject* ArrayList_GetIObject(ArrayList* this)
{
    return this->iObject;
}

IList* ArrayList_GetIList(ArrayList* this)
{
    return this->iList;
}

IStack* ArrayList_GetIStack(ArrayList* this)
{
    return this->iStack;
}

IQueue* ArrayList_GetIQueue(ArrayList* this)
{
    return this->iQueue;
}

ArrayList* ArrayList_Clear(ArrayList* this)
{
    register int i;
    void* implementor_contained;

    for(i=0;i<this->size;i++)
    {
        implementor_contained = this->iObjectContained->implementor;
        this->iObjectContained->implementor = *(this->items+i);
        IObject_Del(this->iObjectContained);
        *(this->items+i) = NULL;
        this->iObjectContained->implementor = implementor_contained;
    }
    this->size = 0;

    return this;
}

void* ArrayList_Get(ArrayList* this, int index)
{
    return *(this->items+index);
}

int ArrayList_Index(ArrayList* this, void* item)
{
    register int i, equal;
    void* implementor_contained;
    
    implementor_contained = this->iObjectContained->implementor;
    for(i=0;i<this->size;i++)
    {
        this->iObjectContained->implementor = *(this->items+i);
        equal = IObject_Equal(this->iObjectContained, item);
        if(equal)
        {
            return i;
        }
    }
    
    return -1;
}

ArrayList* ArrayList_Insert(ArrayList* this, int index, void* item)
{
    register int i;
    void* implementor_contained;
    
    this->size += 1;
    if(this->size>this->max_size)
    {
        this->max_size = this->max_size << 1;
        assert(this->max_size>0);
        this->items = realloc(this->items,sizeof(void*)*this->max_size);
    }
    
    for(i=this->size-1;i>index;i--)
    {
        *(this->items+i) = *(this->items+i-1);
    }
    *(this->items+index) = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = *(this->items+index);
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;
    
    return this;
}

ArrayList* ArrayList_Add(ArrayList* this, void* item)
{
    register int i;
    void* implementor_contained;

    if((this->size+1)>this->max_size)
    {
        this->max_size = this->max_size << 1;
        assert(this->max_size>0);
        this->items = realloc(this->items,sizeof(void*)*(this->max_size));
    }
    *(this->items+this->size) = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = *(this->items+this->size);
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;
    this->size += 1; 
    
    return this;
}

ArrayList* ArrayList_Remove(ArrayList* this, int index)
{
    register int i;
    void* implementor_contained;

    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = *(this->items+index);
    IObject_Del(this->iObjectContained);
    this->iObjectContained->implementor = implementor_contained;
    this->size -= 1;

    for(i=index;i<this->size;i++)
    {
        *(this->items+i) = *(this->items+i+1);
    }

    return this;
}

int ArrayList_Size(ArrayList* this)
{
    return this->size;
}

static void* _ArrayList_New(void* implementor)
{
    ArrayList* array_list;

    array_list = (ArrayList*)implementor;
    
    return ArrayList_New(array_list->iObjectContained);
}

static void* _ArrayList_Del(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    return ArrayList_Del(array_list);
}

static int _ArrayList_Copy(void* implementor, void* object)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    return ArrayList_Copy(array_list, object);
}

static int _ArrayList_Equal(void* implementor, void* object)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    return ArrayList_Equal(array_list, object);
}

static IList* _ArrayList_Clear(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Clear(array_list);
    
    return array_list->iList;
}

static void* _ArrayList_Get(void* implementor, int index)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    return ArrayList_Get(array_list, index);
}

static int _ArrayList_Index(void* implementor, void* item)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    return ArrayList_Index(array_list, item);
}

static IList* _ArrayList_Insert(void* implementor, int index, void* item)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Insert(array_list, index, item);
    
    return array_list->iList;
}

static IList* _ArrayList_Add(void* implementor, void* item)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Add(array_list, item);
    
    return array_list->iList;
}

static IList* _ArrayList_Remove(void* implementor, int index)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Remove(array_list, index);
    
    return array_list->iList;
}

static int _ArrayList_Size(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    return ArrayList_Size(array_list);
}

static IStack* _ArrayList_ClearStack(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Clear(array_list);
    
    return array_list->iStack;
}

static void* _ArrayList_GetTop(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    return ArrayList_Get(array_list, array_list->size-1);
}

static IStack* _ArrayList_Push(void* implementor, void* item)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Add(array_list, item);
    
    return array_list->iStack;
}

static IStack* _ArrayList_Pop(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Remove(array_list, array_list->size-1);
    
    return array_list->iStack;
}

static IQueue* _ArrayList_ClearQueue(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Clear(array_list);
    
    return array_list->iQueue;
}

static void* _ArrayList_GetFront(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    return ArrayList_Get(array_list, 0);
}

static IQueue* _ArrayList_EnQueue(void* implementor, void* item)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    ArrayList_Insert(array_list, array_list->size-1, item);
    
    return array_list->iQueue;
}

static IQueue* _ArrayList_DeQueue(void* implementor)
{
    ArrayList* array_list;
    
    array_list = (ArrayList*)implementor;
    
    ArrayList_Remove(array_list, 0);
    
    return array_list->iQueue;
}
