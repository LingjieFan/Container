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

typedef struct _LinkedNode LinkedNode;

Class LinkedList_Class = {OBJECT};

struct _LinkedList
{
    Class* class;
    IObject* iObject;
    IObject* iObjectContained;
    IList* iList;
    IStack* iStack;
    IQueue* iQueue;
    LinkedNode* next;
};

struct _LinkedNode
{
    LinkedNode* next;
    void* item;
};

static void* _LinkedList_New(void* implementor);
static void* _LinkedList_Del(void* implementor);
static int _LinkedList_Copy(void* implementor, void* object);
static int _LinkedList_Equal(void* implementor, void* object);
static IList* _LinkedList_Clear(void* implementor);
static void* _LinkedList_Get(void* implementor, int index);
static int _LinkedList_Index(void* implementor, void* object);
static IList* _LinkedList_Insert(void* implementor, int index, void* object);
static IList* _LinkedList_Add(void* implementor, void* object);
static IList* _LinkedList_Remove(void* implementor, int index);
static int _LinkedList_Size(void* implementor);
static IStack* _LinkedList_ClearStack(void* implementor);
static void* _LinkedList_GetTop(void* implementor);
static IStack* _LinkedList_Push(void* implementor, void* item);
static IStack* _LinkedList_Pop(void* implementor);
static IQueue* _LinkedList_ClearQueue(void* implementor);
static void* _LinkedList_GetFront(void* implementor);
static IQueue* _LinkedList_EnQueue(void* implementor, void* item);
static IQueue* _LinkedList_DeQueue(void* implementor);

LinkedList* LinkedList_New(IObject* iObjectContained)
{
    LinkedList* linked_list;

    linked_list = (LinkedList*)malloc(sizeof(LinkedList)+sizeof(IObject)+\
        sizeof(IList)+sizeof(IStack)+sizeof(IQueue));
    linked_list->class = LINKEDLIST;
    linked_list->iObject = (IObject*)(linked_list+1);
    linked_list->iObject->implementor = linked_list;
    linked_list->iObject->New = _LinkedList_New;
    linked_list->iObject->Del = _LinkedList_Del;
    linked_list->iObject->Copy = _LinkedList_Copy;
    linked_list->iObject->Equal = _LinkedList_Equal;
    linked_list->iObjectContained = iObjectContained;
    linked_list->iList = (IList*)(linked_list->iObject);
    linked_list->iList->implementor = linked_list;
    linked_list->iList->Clear = _LinkedList_Clear;
    linked_list->iList->Get = _LinkedList_Get;
    linked_list->iList->Index = _LinkedList_Index;
    linked_list->iList->Insert = _LinkedList_Insert;
    linked_list->iList->Add = _LinkedList_Add;
    linked_list->iList->Remove = _LinkedList_Remove;
    linked_list->iList->Size = _LinkedList_Size;
    linked_list->iStack = (IStack*)(linked_list->iList);
    linked_list->iStack->Clear = _LinkedList_ClearStack;
    linked_list->iStack->Get = _LinkedList_GetTop;
    linked_list->iStack->Push = _LinkedList_Push;
    linked_list->iStack->Pop = _LinkedList_Pop;
    linked_list->iStack->Size = _LinkedList_Size;
    linked_list->iQueue = (IQueue*)(linked_list->iStack);
    linked_list->iQueue->implementor = linked_list;
    linked_list->iQueue->Clear = _LinkedList_ClearQueue;
    linked_list->iQueue->Get = _LinkedList_GetFront;
    linked_list->iQueue->EnQueue = _LinkedList_EnQueue;
    linked_list->iQueue->DeQueue = _LinkedList_DeQueue;
    linked_list->iQueue->Size = _LinkedList_Size;
    linked_list->next = NULL;

    return linked_list;
}

LinkedList* LinkedList_Del(LinkedList* this)
{
    LinkedList_Clear(this);
    free(this);
    
    return NULL;
}

int LinkedList_Copy(LinkedList* this, void* object)
{
    register int i;
    int size1, size2;
    LinkedList* list1,* list2;
    LinkedNode* node1,* node2;
    void* implementor_contained,* item;
    
    list1 = this;
    list2 = (LinkedList*)object;
    size1 = LinkedList_Size(list1);
    size2 = LinkedList_Size(list2);
    if(list1->iObjectContained->New == list2->iObjectContained->New)
    {
        if(size2>size1)
        {
            for(i=size1;i<size2;i++)
            {
                item = IObject_New(list1->iObjectContained);
                LinkedList_Add(list1, item);
            }
        }
        else
        {
            for(i=size2;i<size1;i++)
            {
                LinkedList_Remove(list1, 0);
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
        return 0;
    }
}

int LinkedList_Equal(LinkedList* this, void* object)
{
    register int i, equal;
    int size1, size2;
    LinkedList* list1,* list2;
    LinkedNode* node1,* node2;
    void* implementor_contained;

    list1 = this;
    list2 = (LinkedList*)object;
    size1 = LinkedList_Size(list1);
    size2 = LinkedList_Size(list2);
    node1 = list1->next;
    node2 = list2->next;
    if((size1==size2) || (list1->iObjectContained->New == list2->iObjectContained->New))
    {
        implementor_contained = list1->iObjectContained->implementor;
        for(i=0;i<size1;i++)
        {
            list1->iObjectContained->implementor = node1->item;
            equal = IObject_Equal(list1->iObjectContained, node2->item);
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

IObject* LinkedList_GetIObject(LinkedList* this)
{
    return this->iObject;
}

IList* LinkedList_GetIList(LinkedList* this)
{
    return this->iList;
}

IStack* LinkedList_GetIStack(LinkedList* this)
{
    return this->iStack;
}

IQueue* LinkedList_GetIQueue(LinkedList* this)
{
    return this->iQueue;
}

LinkedList* LinkedList_Clear(LinkedList* this)
{
    register LinkedNode* node_prev,* node_now;
    void* implementor_contained;
    
    implementor_contained = this->iObjectContained->implementor;
    node_prev = this->next;
    while(node_prev)
    {
        node_now = node_prev->next;
        this->iObjectContained->implementor = node_prev->item;
        IObject_Del(this->iObjectContained);
        free(node_prev);
        node_prev = node_now;
    }
    this->iObjectContained->implementor = implementor_contained;
    this->next = NULL;
    
    return this;
}

void* LinkedList_Get(LinkedList* this, int index)
{
    register int i;
    register LinkedNode* node;

    node = this->next;
    for(i=0; i<index; i++)
    {
        node = node->next;
    }
    
    return node->item;
}

void* LinkedList_Last(LinkedList* this)
{
    register LinkedNode* node;

    node = this->next;
    if(!node)
    {
        return NULL;
    }
    if(!node->next)
    {
        return node->item;
    }

    while(node->next)
    {
        node = node->next;
    }

    return node->item;
}

int LinkedList_Index(LinkedList* this, void* item)
{
    register int i;
    register LinkedNode* node;
    void* implementor_contained;
    
    i = 0;
    node = this->next;
    implementor_contained = this->iObjectContained->implementor;
    while(node)
    {
        this->iObjectContained->implementor = node->item;
        if(IObject_Equal(this->iObjectContained, item))
        {
            this->iObjectContained->implementor = implementor_contained;
        
            return i;
        }
        node = node->next;
        i++;
    }
    this->iObjectContained->implementor = implementor_contained;
    
    return -1;
}

LinkedList* LinkedList_Insert(LinkedList* this, int index, void* item)
{
    register int i;
    int size;
    register LinkedNode* node,* node_new;
    void* implementor_contained;

    if((index < 0) || (this->next == NULL))
    {
        return LinkedList_Add(this, item);
    }
    else if(index == 0)
    {
        return LinkedList_AddFirst(this, item);
    }
    node = this->next;
    index--;

    while((index-- > 0)&& node->next)
    {
        node = node->next;
    }
    node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
    node_new->next = node->next;
    node_new->item = IObject_New(this->iObjectContained);
    node->next = node_new;
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = node_new->item;
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;
    
    return this;
}

LinkedList* LinkedList_InsertSorted(LinkedList* this, void* item, CompareFunc compare_func, void* user_data)
{
    int cmp;
    LinkedNode* node_prev,* node_tmp,* node_new;
    void* implementor_contained;

    node_tmp = this->next;
    node_prev = NULL;
    node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
    node_new->item = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = node_new->item;
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;
    if(!node_tmp)
    {
        node_new->next = NULL;
        this->next = node_new;

        return this;
    }

    cmp = (*compare_func)(item, node_tmp->item, user_data);

    while((node_tmp->next) && (cmp>0))
    {
        node_prev = node_tmp;
        node_tmp = node_tmp->next;
        cmp = (*compare_func)(item, node_tmp->item, user_data);
    }

    if((!node_tmp->next) && (cmp>0))
    {
        node_tmp->next = node_new;
        node_new->next = NULL;

        return this;
    }

    if(node_prev)
    {
        node_prev->next = node_new;
        node_new->next = node_tmp;

        return this;
    }
    else
    {
        node_new->next = this->next;
        this->next = node_new;

        return this;
    }
}

LinkedList* LinkedList_Add(LinkedList* this, void* item)
{
    LinkedNode* node,* node_new;
    void* implementor_contained;

    node = this->next;
    if(node)
    {
        while(node->next)
        {
            node = node->next;
        }
        node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
        node_new->next = NULL;
        node->next = node_new;
    }
    else
    {
        node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
        node_new->next = NULL;            
        this->next = node_new;
    }
    node_new->item = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = node_new->item;
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;    

    return this;
}

LinkedList* LinkedList_AddFirst(LinkedList* this, void* item)
{
    LinkedNode* node_new;
    void* implementor_contained;

    node_new = (LinkedNode*)malloc(sizeof(LinkedNode));
    node_new->next = this->next;
    this->next = node_new;
    node_new->item = IObject_New(this->iObjectContained);
    implementor_contained = this->iObjectContained->implementor;
    this->iObjectContained->implementor = node_new->item;
    IObject_Copy(this->iObjectContained, item);
    this->iObjectContained->implementor = implementor_contained;

    return this;
}

LinkedList* LinkedList_Remove(LinkedList* this, int index)
{
    register int i;
    int size;
    LinkedNode* node_now,* node_prev;
    void* implementor_contained;

    node_prev = this->next;
    node_now = this->next;
    if(index)
    {
        node_now = node_prev->next;
        for(i=1; i<index; i++)
        {
            node_prev = node_now;
            node_now = node_now->next;
        }
    }
    else
    {
        this->next = node_now->next;            
    }
    this->iObjectContained->implementor = node_now->item;
    IObject_Del(this->iObjectContained);
    free(node_now);
    this->iObjectContained->implementor = implementor_contained;        

    return this;
}

int LinkedList_Size(LinkedList* this)
{
    register int size;
    register LinkedNode* node;

    size = 0;
    node = NULL;
    while(node)
    {
        size += 1;
        node = node->next;
    }

    return size;
}

LinkedList* LinkedList_Reverse(LinkedList* this)
{
    register LinkedNode* node_now,*node_pre,* node_next;

    node_now = this->next;
    node_pre = NULL;
    while(node_now)
    {
        node_next = node_now->next;
        node_now->next = node_pre;
        node_pre = node_now;
        node_now = node_next;
    }
    this->next = node_pre;

    return this;
}

LinkedList* LinkedList_ForEach(LinkedList* this, Func func, void* user_data)
{
    LinkedNode* node;

    node = this->next;
    while(node)
    {
        (*func)(node->item, user_data);
        node = node->next;
    }

    return this;
}

static LinkedNode* LinkedList_MergeRecur(LinkedNode* l1, LinkedNode* l2, CompareFunc compare_func, void* user_data)
{
    LinkedNode list,* l;
    int cmp;

    l = &list;
    while(l1 && l2)
    {
        cmp = (*compare_func)(l1->item, l2->item, user_data);

        if(cmp <= 0)
        {
            l = l->next = l1;
            l1 = l1->next;
        }
        else
        {
            l = l->next = l2;
            l2 = l2->next;
        }
    }
    l->next = l1 ? l1 : l2;

    return list.next;
}

static LinkedNode* LinkedList_PartRecur(LinkedNode* list, CompareFunc compare_func, void* user_data)
{
    LinkedNode* l1,* l2;

    if(!list)
    {
        return NULL;
    }
    if(!list->next)
    {
        return list;
    }

    l1 = list;
    l2 = list->next;

    while((l2 = l2->next) != NULL)
    {
        if((l2 = l2->next) == NULL)
        {
            break;
        }
        l1 = l1->next;
    }
    l2 = l1->next;
    l1->next = NULL;

    return LinkedList_MergeRecur(LinkedList_PartRecur(list, compare_func, user_data), LinkedList_PartRecur(list, compare_func, user_data), compare_func, user_data);
}

LinkedList* LinkedList_Sort(LinkedList* this, CompareFunc compare_func, void* user_data)
{
    this->next = LinkedList_PartRecur(this->next, compare_func, user_data);

    return this;
}

static void* _LinkedList_New(void* implementor)
{
    LinkedList* linked_list;

    linked_list = (LinkedList*)implementor;

    return LinkedList_New(linked_list->iObjectContained);
}

static void* _LinkedList_Del(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    
    return LinkedList_Del(linked_list);
}

static int _LinkedList_Copy(void* implementor, void* object)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    
    return LinkedList_Copy(linked_list, object);
}

static int _LinkedList_Equal(void* implementor, void* object)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    
    return LinkedList_Equal(linked_list, object);
}

static IList* _LinkedList_Clear(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Clear(linked_list);
    
    return linked_list->iList;
}

static void* _LinkedList_Get(void* implementor, int index)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    
    return LinkedList_Get(linked_list, index);    
}

static int _LinkedList_Index(void* implementor, void* item)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    
    return LinkedList_Index(linked_list, item);
}

static IList* _LinkedList_Insert(void* implementor, int index, void* item)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Insert(linked_list, index, item);
    
    return linked_list->iList;
}

static IList* _LinkedList_Add(void* implementor, void* item)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Add(linked_list, item);
    
    return linked_list->iList;
}

static IList* _LinkedList_Remove(void* implementor, int index)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Remove(linked_list, index);
    
    return linked_list->iList;
}

static int _LinkedList_Size(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    return LinkedList_Size(linked_list);
}

static IStack* _LinkedList_ClearStack(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Clear(linked_list);
    
    return linked_list->iStack;
}

static void* _LinkedList_GetTop(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    
    return LinkedList_Get(implementor, 0);
}

static IStack* _LinkedList_Push(void* implementor, void* item)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Insert(linked_list, 0, item);
    
    return linked_list->iStack;
}

static IStack* _LinkedList_Pop(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Remove(linked_list, 0);
    
    return linked_list->iStack;
}

static IQueue* _LinkedList_ClearQueue(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Clear(linked_list);
    
    return linked_list->iQueue;
}

static void* _LinkedList_GetFront(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    
    return LinkedList_Get(linked_list, 0);
}

static IQueue* _LinkedList_EnQueue(void* implementor, void* item)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Add(linked_list, item);
    
    return linked_list->iQueue;
}

static IQueue* _LinkedList_DeQueue(void* implementor)
{
    LinkedList* linked_list;
    
    linked_list = (LinkedList*)implementor;
    LinkedList_Remove(linked_list, 0);
    
    return linked_list->iQueue;
}
