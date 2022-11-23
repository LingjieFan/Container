#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "IObject.h"
#include "IList.h"
#include "IStack.h"
#include "IQueue.h"
#include "Class.h"
#include "Object.h"
#include "LinkedList.h"
#include "DoubleLinkedList.h"

typedef struct _LinkedNode LinkedNode;

Class DoubleLinkedList_Class = {OBJECT};

struct _DoubleLinkedList
{
    Class* class;
    IObject* iObject;
    IObject* iObjectContained;
    IList* iList;
    IStack* iStack;
    IQueue* iQueue;
    LinkedNode* next;
    LinkedNode* prior;
};

struct _LinkedNode
{
    LinkedNode* next;
    void* item;
    LinkedNode* prior;
};

extern int LinkedList_Equal(void* implementor, void* object);
static void* _DoubleLinkedList_New(void* implementor);
static void* _DoubleLinkedList_Del(void* implementor);
static int _DoubleLinkedList_Copy(void* implementor, void* object);
static int _DoubleLinkedList_Equal(void* implementor, void* object);
static IList* _DoubleLinkedList_Clear(void* implementor);
static void* _DoubleLinkedList_Get(void* implementor, int index);
static int _DoubleLinkedList_Index(void* implementor, void* item);
static IList* _DoubleLinkedList_Insert(void* implementor, int index, void* item);
static IList* _DoubleLinkedList_Add(void* implementor, void* item);
static IList* _DoubleLinkedList_Remove(void* implementor, int index);
static int _DoubleLinkedList_Size(void* implementor);
static IStack* _DoubleLinkedList_ClearStack(void* implementor);
static void* _DoubleLinkedList_GetTop(void* implementor);
static IStack* _DoubleLinkedList_Push(void* implementor, void* item);
static IStack* _DoubleLinkedList_Pop(void* implementor);
static IQueue* _DoubleLinkedList_ClearQueue(void* implementor);
static void* _DoubleLinkedList_GetFront(void* implementor);
static IQueue* _DoubleLinkedList_EnQueue(void* implementor, void* item);
static IQueue* _DoubleLinkedList_DeQueue(void* implementor);

DoubleLinkedList* DoubleLinkedList_New(IObject* iObjectContained)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList)+
        sizeof(IObject)+sizeof(IList)+sizeof(IStack)+sizeof(IQueue));
    double_linked_list->class = DOUBLELINKEDLIST;
    double_linked_list->iObject = (IObject*)(double_linked_list+1);
    double_linked_list->iObject->implementor = double_linked_list;
    double_linked_list->iObject->New = _DoubleLinkedList_New;
    double_linked_list->iObject->Del = _DoubleLinkedList_Del;
    double_linked_list->iObject->Copy = _DoubleLinkedList_Copy;
    double_linked_list->iObject->Equal = _DoubleLinkedList_Equal;
    double_linked_list->iObjectContained = iObjectContained;
    double_linked_list->iList = (IList*)(double_linked_list->iObject+1);
    double_linked_list->iList->Clear = _DoubleLinkedList_Clear;
    double_linked_list->iList->Get = _DoubleLinkedList_Get;
    double_linked_list->iList->Index = _DoubleLinkedList_Index;
    double_linked_list->iList->Insert = _DoubleLinkedList_Insert;
    double_linked_list->iList->Add = _DoubleLinkedList_Add;
    double_linked_list->iList->Remove = _DoubleLinkedList_Remove;
    double_linked_list->iList->Size = _DoubleLinkedList_Size;
    double_linked_list->iStack = (IStack*)(double_linked_list->iList+1);
    double_linked_list->iStack->implementor = double_linked_list;
    double_linked_list->iStack->Clear = _DoubleLinkedList_ClearStack;
    double_linked_list->iStack->Get = _DoubleLinkedList_GetTop;
    double_linked_list->iStack->Push = _DoubleLinkedList_Push;
    double_linked_list->iStack->Pop = _DoubleLinkedList_Pop;
    double_linked_list->iStack->Size = _DoubleLinkedList_Size;
    double_linked_list->iQueue = (IQueue*)(double_linked_list->iStack+1);
    double_linked_list->iQueue->implementor = double_linked_list;
    double_linked_list->iQueue->Clear = _DoubleLinkedList_ClearQueue;
    double_linked_list->iQueue->Get = _DoubleLinkedList_GetFront;
    double_linked_list->iQueue->EnQueue = _DoubleLinkedList_EnQueue;
    double_linked_list->iQueue->DeQueue = _DoubleLinkedList_DeQueue;
    double_linked_list->iQueue->Size = _DoubleLinkedList_Size;
    double_linked_list->next = NULL;
    double_linked_list->prior = NULL;

    return double_linked_list;
}

DoubleLinkedList* DoubleLinkedList_Del(DoubleLinkedList* this)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)this;
    LinkedList_Del(linked_list);
    
    return NULL;
}

IObject* DoubleLinkedList_GetIObject(DoubleLinkedList* this)
{
    return this->iObject;
}

IList* DoubleLinkedList_GetIList(DoubleLinkedList* this)
{
    return this->iList;
}

IQueue* DoubleLinkedList_GetIQueue(DoubleLinkedList* this)
{
    return this->iQueue;
}

DoubleLinkedList* DoubleLinkedList_Clear(DoubleLinkedList* this)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)this;
    LinkedList_Clear(linked_list);
    this->prior = NULL;
    
    return this;
}

void* DoubleLinkedList_Get(DoubleLinkedList* this, int index)
{
    int size, half;
    
    size = DoubleLinkedList_Size(this);
    half = size >> 1;
    if((0 <= index) && (index < half))
    {
        LinkedList* linked_list;
        
        linked_list = (LinkedList*)this;
        
        return LinkedList_Get(linked_list, index);
    }
    else if((half <= index) && (index < size))
    {
        register int i;
        LinkedNode* node;
        
        node = this->prior;
        for(i=index; i<(size-1); i++)
        {
            node = node->prior;
        }
        
        return node->item;
    }
    else
    {
        printf("index out of the range, index: %d, size: %d\n", index, size);
        
        return NULL;
    }
}

void* DoubleLinkedList_Last(DoubleLinkedList* this)
{
    return this->prior->item;
}

int DoubleLinkedList_Index(DoubleLinkedList* this, void* item)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)this;
    
    return LinkedList_Index(linked_list, item);
}

DoubleLinkedList* DoubleLinkedList_Insert(DoubleLinkedList* this, int index, void* item)
{
    register int i;
    int size, half;
    LinkedNode* node,* node_new;
    void* implementor_contained;
    
    size = DoubleLinkedList_Size(this);
    half = size >> 1;
    if((0<=index)&&(index<half))
    {
        if(index)
        {
            node = this->next;
            for(i=0;i<index;i++)
            {
                node = node->next;
            }
            node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
            node_new->next = node;
            node_new->next = node->prior;
            node_new->next->prior = node_new;
            node_new->prior->next = node_new;
        }
        else
        {
            node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
            node_new->next = this->next;
            node_new->prior = NULL;
            this->next->prior = node_new;
            this->next = node_new;
        }
        implementor_contained = this->iObjectContained->implementor;
        this->iObjectContained->implementor = node_new->item;
        IObject_Copy(this->iObjectContained, item);
        this->iObjectContained->implementor = implementor_contained;        
    }
    else if((half<=index)&&(index<size))
    {
        if(index == (size-1))
        {
            node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
            node_new->next = NULL;
            node_new->prior = this->prior;
            this->prior->next = node_new;
            this->prior = node_new;
        }
        else
        {
            node = this->prior;
            for(i=index;i<(size-1);i++)
            {
                node = node->prior;
            }
            node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
            node_new->next = node;
            node_new->prior = node->prior;
            node_new->prior->next = node_new;
            node_new->next->prior = node_new;
        }
        implementor_contained = this->iObjectContained->implementor;
        this->iObjectContained->implementor = node_new->item;
        IObject_Copy(this->iObjectContained, item);
        this->iObjectContained->implementor = implementor_contained;                
    }
    else
    {
        printf("index out of the range, index: %d, size: %d\n", index, size);
    }  
    
    return this;
}

DoubleLinkedList* DoubleLinkedList_InsertSorted(DoubleLinkedList* this, void* item, CompareFunc compare_func, void* user_data)
{
    int cmp;
    LinkedNode* node_new,* node_tmp;
    void* implementor_contained;

    node_tmp = this->next;
    node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
    node_new->item = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;  
    this->iObjectContained->implementor = node_new->item;
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;
    
    if(!node_tmp)
    {
        this->next = node_new;
        this->prior = node_new;
        node_new->prior = NULL;
        node_new->next = NULL;
    }

    cmp = (*compare_func)(item, node_tmp->item, user_data);
    while((node_tmp->next) && (cmp>0))
    {
        node_tmp = node_tmp->next;
        cmp = (*compare_func)(item, node_tmp->item, user_data);
    }

    if((!node_tmp->next) && (cmp>0))
    {
        node_tmp->next = node_new;
        node_new->prior = node_tmp;
        node_new->next = NULL;
        this->prior = node_new;

        return this;
    }
    
    if(node_tmp->prior)
    {
        node_tmp->prior->next = node_new;
        node_new->prior = node_tmp->prior;
    }
    else
    {
        this->next = node_new;
        node_new->prior = NULL;   
    }
    node_new->next = node_tmp;
    node_tmp->prior = node_new;

    return this;
}

DoubleLinkedList* DoubleLinkedList_Add(DoubleLinkedList* this, void* item)
{
    LinkedNode* node,* node_new;
    void* implementor_contained;

    node = this->prior;
    if(node)
    {
        node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
        node_new->next = NULL;
        node_new->prior = node;
        node->next = node_new;
        this->prior = node_new;
    }
    else
    {
        node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
        this->prior = node_new;
        this->next = node_new;
        node_new->next = NULL;
        node_new->prior = NULL;
    }
    node_new->item = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = node_new->item;            
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;        

    return this;    
}

DoubleLinkedList* DoubleLinkedList_AddFirst(DoubleLinkedList* this, void* item)
{
    LinkedNode* node_new;
    void* implementor_contained;

    node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
    node_new->item = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = node_new->item;
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;
    node_new->prior = NULL;
    node_new->next = this->next;
    this->next->prior = node_new;
    this->next = node_new;

    return this;
}

DoubleLinkedList* DoubleLinkedList_Remove(DoubleLinkedList* this, int index)
{
    register int i;
    int size, half;
    LinkedNode* node;
    void* implementor_contained;
    
    size = DoubleLinkedList_Size(this);
    half = size >> 1;
    if((0<=index)&&(index<half))
    {
        if(index)
        {
            node = this->next;
            for(i=0;i<index;i++)
            {
                node = node->next;
            }
            node->prior->next = node->next;
            node->next->prior = node->prior;
        }
        else
        {
            node = this->next;
            this->next = node->next;
            node->next->prior = NULL;
        }
        implementor_contained = this->iObjectContained->implementor;
        this->iObjectContained->implementor = node->item;
        IObject_Del(this->iObjectContained);
        free(node);
        this->iObjectContained->implementor = implementor_contained;        
    }
    else if((half<=index)&&(index<size))
    {
        if(index == (size-1))
        {
            node = this->prior;
            this->prior = node->prior;
            node->prior->next = NULL;
        }
        else
        {
            node = this->prior;
            for(i=index;i<(size-1);i++)
            {
                node = node->prior;
            }
            node->prior->next = node->next;
            node->next->prior = node->prior;
        }
        implementor_contained = this->iObjectContained->implementor;
        this->iObjectContained->implementor = node->item;
        IObject_Del(this->iObjectContained);
        free(node);
        this->iObjectContained->implementor = implementor_contained;                
    }
    else
    {
        printf("index out of the range, index: %d, size: %d\n", index, size);
    }  
    
    return this;
}

int DoubleLinkedList_Size(DoubleLinkedList* this)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)this;
    
    return LinkedList_Size(linked_list);
}

DoubleLinkedList* DoubleLinkedList_Reverse(DoubleLinkedList* this)
{
    LinkedNode* node_last,* node_next;
    
    node_last = NULL;
    node_next = this->next;
    this->next = this->prior;
    this->prior = node_next;
    while(node_next)
    {
        node_last = node_next;
        node_next = node_last->next;
        node_last->next = node_last->prior;
        node_last->prior = node_next;
    }    
    
    return this;
}

int DoubleLinkedList_Copy(DoubleLinkedList* this, void* object)
{
    register int i;
    int size1, size2;
    register DoubleLinkedList* list1,* list2;
    LinkedNode* node1,* node2;
    void* implementor_contained,* item;
    
    list1 = this;
    list2 = (DoubleLinkedList*)object;
    size1 = DoubleLinkedList_Size(list1);
    size2 = DoubleLinkedList_Size(list2);
    if(list1->iObjectContained->New == list2->iObjectContained->New)
    {
        if(size2>size1)
        {
            for(i=size1;i<size2;i++)
            {
                item = IObject_New(list1->iObjectContained);
                DoubleLinkedList_Add(list1, item);
            }
        }
        else
        {
            for(i=size2;i<size1;i++)
            {
                DoubleLinkedList_Remove(list1, 0);
            }
        }
        node1 = list1->next;
        node2 = list2->next;
        implementor_contained = list1->iObjectContained->implementor;
        for(i=0;i<size2;i++)
        {
            list1->iObjectContained->implementor = node1->item;
            IObject_Copy(list1->iObjectContained, node2->item);
            node1 = node1->next;
            node2 = node2->next;
        }
        list1->iObjectContained->implementor = implementor_contained;

        return 1;
    }
    else
    {
        printf("The DoubleLinkedList_Copy Failed.\n");

        return 0;
    }    
}

static void DoubleLinkedList_Swap(LinkedNode* a, LinkedNode* b)
{
    a->prior->next = b;
    a->next->prior = b;
    b->prior->next = a;
    b->next->prior = a;
    a = a->next;
    b = b->next;
    b->prior->next = b;
    a->prior->next = a;
    a = b->prior->prior;
    b = a->next->prior;
    b->next->prior = b;
    a->next->prior = a;
    a = a->next;
    b = b->next;
}

static LinkedNode* DoubleLinkedList_Partition(LinkedNode* low, LinkedNode* high, CompareFunc compare_func, void* user_data)
{
    LinkedNode* node_pivot;

    node_pivot = low;
    while(low!=high)
    {
        while((low!=high) && ((*compare_func)(high->item, node_pivot->item, user_data)>=0))
        {
            high--;
        }
        DoubleLinkedList_Swap(low, high);
        while((low!=high) && ((*compare_func)(low->item, node_pivot->item, user_data)>=0))
        {
            low++;
        }
        DoubleLinkedList_Swap(low, high);
    }

    return low;
}

static DoubleLinkedList* DoubleLinkedList_SortRecur(LinkedNode* low, LinkedNode* high, CompareFunc compare_func, void* user_data)
{
    LinkedNode* node_pivot;

    if(low!=high)
    {
        node_pivot = DoubleLinkedList_Partition(low, high, compare_func, user_data);
        DoubleLinkedList_SortRecur(low, node_pivot->prior, compare_func, user_data);
        DoubleLinkedList_SortRecur(node_pivot->next, high, compare_func, user_data);
    }
}

DoubleLinkedList* DoubleLinkedList_Sort(DoubleLinkedList* this, CompareFunc compare_func, void* user_data)
{
    LinkedNode node_tmp;
    LinkedNode* low,* high,* tmp;

    if(!this->next)
    {
        return this;
    }
    tmp = &node_tmp;
    low = this->next;
    high = this->prior;
    low->prior = tmp;
    high->next = tmp;
    tmp->next = low;
    tmp->prior = high;
    DoubleLinkedList_SortRecur(low, high, compare_func, user_data);
    this->next = tmp->next;
    this->prior = tmp->prior;
    this->next->prior = NULL;
    this->prior->next = NULL;

    return this;
}

static void* _DoubleLinkedList_New(void* implementor)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;

    return DoubleLinkedList_New(double_linked_list->iObjectContained);
}

static void* _DoubleLinkedList_Del(void* implementor)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;

    return DoubleLinkedList_Del(double_linked_list);
}

static int _DoubleLinkedList_Copy(void* implementor, void* object)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;

    return DoubleLinkedList_Copy(double_linked_list, object);
}

static int _DoubleLinkedList_Equal(void* implementor, void* object)
{
    LinkedList* linked_list;

    linked_list = (LinkedList*)implementor;

    return LinkedList_Equal(linked_list, object);
}


static IList* _DoubleLinkedList_Clear(void* implementor)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Clear(double_linked_list);

    return double_linked_list->iList;
}

static void* _DoubleLinkedList_Get(void* implementor, int index)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;

    return DoubleLinkedList_Get(double_linked_list, index);
}

static int _DoubleLinkedList_Index(void* implementor, void* item)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;

    return DoubleLinkedList_Index(double_linked_list, item);
}

static IList* _DoubleLinkedList_Insert(void* implementor, int index, void* item)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Insert(double_linked_list, index, item);

    return double_linked_list->iList;
}

static IList* _DoubleLinkedList_Add(void* implementor, void* item)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Add(double_linked_list, item);

    return double_linked_list->iList;
}

static IList* _DoubleLinkedList_Remove(void* implementor, int index)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Remove(double_linked_list, index);

    return double_linked_list->iList;
}

static int _DoubleLinkedList_Size(void* implementor)
{
    DoubleLinkedList* double_linked_list;

    double_linked_list = (DoubleLinkedList*)implementor;

    return DoubleLinkedList_Size(double_linked_list);
}

static IStack* _DoubleLinkedList_ClearStack(void* implementor)
{
    DoubleLinkedList* double_linked_list;
    
    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Clear(double_linked_list);
    
    return double_linked_list->iStack;    
}

static void* _DoubleLinkedList_GetTop(void* implementor)
{
    DoubleLinkedList* double_linked_list;
    
    double_linked_list = (DoubleLinkedList*)implementor;
    
    return DoubleLinkedList_Get(double_linked_list, 0);
}

static IStack* _DoubleLinkedList_Push(void* implementor, void* item)
{
    DoubleLinkedList* double_linked_list;
    
    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Insert(double_linked_list, 0, item);
    
    return double_linked_list->iStack;
}

static IStack* _DoubleLinkedList_Pop(void* implementor)
{
    DoubleLinkedList* double_linked_list;
    
    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Remove(double_linked_list, 0);
    
    return double_linked_list->iStack;
}

static IQueue* _DoubleLinkedList_ClearQueue(void* implementor)
{
    DoubleLinkedList* double_linked_list;
    
    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Clear(double_linked_list);
    
    return double_linked_list->iQueue;
}

static void* _DoubleLinkedList_GetFront(void* implementor)
{
    DoubleLinkedList* double_linked_list;
    
    double_linked_list = (DoubleLinkedList*)implementor;
    
    return DoubleLinkedList_Get(double_linked_list, 0);
}

static IQueue* _DoubleLinkedList_EnQueue(void* implementor, void* item)
{
    DoubleLinkedList* double_linked_list;
    
    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Add(double_linked_list, item);

    return double_linked_list->iQueue;
}

static IQueue* _DoubleLinkedList_DeQueue(void* implementor)
{
    DoubleLinkedList* double_linked_list;
    
    double_linked_list = (DoubleLinkedList*)implementor;
    DoubleLinkedList_Remove(double_linked_list, 0);

    return double_linked_list->iQueue;
}

