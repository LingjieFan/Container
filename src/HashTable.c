#include <stdlib.h>
#include "IObject.h"
#include "IHash.h"
#include "Class.h"
#include "HashTable.h"

typedef struct _HashNode HashNode;

Class HashTable_Class = {CLASS};

struct _HashTable
{
    Class* class;
    IHash* iHash;   
    IObject* iObjectKey;
    IObject* iObjectValue;
    HashNode** tab;
    int size;
    int tab_size;
};

struct _HashNode
{
    unsigned int hash_key;
    void* key;
    void* value;
    HashNode* next;
};

static unsigned int _HashTable_HashFunc(void* implementor);

HashTable* HashTable_New(IObject* iObjectKey, IObject* iObjectValue)
{
    HashTable* hash_table;

    hash_table = (HashTable*)malloc(sizeof(HashTable)+sizeof(IHash));
    hash_table->class = HASHTABLE;
    hash_table->iHash = (IHash*)(hash_table+1);
    hash_table->iHash->implementor = NULL;
    hash_table->iHash->HashFunc = _HashTable_HashFunc;
    hash_table->iObjectKey = iObjectKey;
    hash_table->iObjectValue = iObjectValue;
    hash_table->tab = (HashNode**)calloc(21, sizeof(HashNode*));
    hash_table->size = 0;
    hash_table->tab_size = 21;

    return hash_table;
}

HashTable* HashTable_Del(HashTable* this)
{
    HashTable_Clear(this);
    free(this);

    return NULL;
}

HashTable* HashTable_SetIHash(HashTable* this, IHash* iHash)
{
    this->iHash = iHash;

    return this;
}

HashTable* HashTable_Clear(HashTable* this)
{
    register int i;
    int tab_size;
    register HashNode* node1,* node2;
    void* implementor_key,* implementor_value;

    tab_size = this->tab_size;
    implementor_key = this->iObjectKey->implementor;
    implementor_value = this->iObjectValue->implementor;
    for(i=0;i<tab_size;i++)
    {
        node1 = (this->tab)[i];
        while(node1)
        {
            node2 = node1->next;
            this->iObjectKey->implementor = node1->key;
            this->iObjectValue->implementor = node1->value;
            IObject_Del(this->iObjectKey);
            IObject_Del(this->iObjectValue);
            free(node1);
            node1 = node2;
        }
        (this->tab)[i] = NULL;
    }
    this->iObjectKey->implementor = implementor_key;
    this->iObjectValue->implementor = implementor_value;
    this->size = 0;

    return this;
}

void* HashTable_Get(HashTable* this, void* key)
{
    unsigned int index;
    HashNode* node;
    void* implementor_hash;

    implementor_hash = this->iHash->implementor;
    this->iHash->implementor = key;
    index = IHash_HashFunc(this->iHash) % this->tab_size;
    this->iHash->implementor = implementor_hash;
    implementor_hash = this->iObjectKey->implementor;
    node = (this->tab)[index];
    while(node)
    {
        this->iObjectKey->implementor = node->key;
        if(IObject_Equal(this->iObjectKey, key))
        {
            this->iObjectKey->implementor = implementor_hash;
            return node->value;
        }
        node = node->next;
    }
    this->iObjectKey->implementor = implementor_hash;

    return NULL;
}

static int HashTable_ReHash(HashTable* this)
{
    register int i, index;
    int tab_size;
    HashNode** tab;
    HashNode* node1,* node2;

    tab_size = 2 * this->tab_size;
    tab = (HashNode**)calloc(tab_size, sizeof(HashNode*));

    for(i=0;i<this->tab_size;i++)
    {
        node1 = (this->tab)[i];
        while(node1)
        {
            node2 = node1->next;
            node1->next = NULL;
            index = node1->hash_key % tab_size;
            if(tab[index])
            {
                node1->next = tab[index];
            }
            tab[index] = node1;
        }
    }
    free(this->tab);
    this->tab = tab;
    this->tab_size = tab_size;

    return 0;
}

HashTable* HashTable_Add(HashTable* this, void* key, void* value)
{
    unsigned int index;
    HashNode* node;
    void* implementor_hash,* implementor_value;

    implementor_hash = this->iHash->implementor;
    this->iHash->implementor = key;
    index = IHash_HashFunc(this->iHash) % this->tab_size;
    this->iHash->implementor = implementor_hash;
    implementor_hash = this->iObjectKey->implementor;
    node = (this->tab)[index];
    while(node)
    {
        this->iObjectKey->implementor = node->key;
        if(IObject_Equal(this->iObjectKey, key))
        {
            break;
        }
        node = node->next;
    }
    this->iObjectKey->implementor = implementor_hash;

    if(node)
    {
        implementor_value = this->iObjectValue->implementor;
        this->iObjectValue->implementor = node->value;
        IObject_Del(this->iObjectValue);
        node->value = IObject_New(this->iObjectValue);
        this->iObjectValue->implementor = node->value;
        IObject_Copy(this->iObjectValue, value);
        this->iObjectValue->implementor = implementor_value;
    }
    else
    {
        if(this->size > this->tab_size * 1.3)
        {
            HashTable_ReHash(this);
        }
        node = (HashNode*)malloc(sizeof(HashNode));
        implementor_hash = this->iHash->implementor;
        this->iHash->implementor = key;
        node->hash_key = IHash_HashFunc(this->iHash);
        this->iHash->implementor = implementor_hash;
        node->value = IObject_New(this->iObjectValue);
        implementor_value = this->iObjectValue->implementor;       
        this->iObjectValue->implementor = node->value;       
        IObject_Copy(this->iObjectValue, value);
        this->iObjectValue->implementor = implementor_value;
        node->key = IObject_New(this->iObjectKey);
        implementor_value = this->iObjectKey->implementor;
        this->iObjectKey->implementor = node->key;
        IObject_Copy(this->iObjectKey, key);
        this->iObjectKey->implementor = implementor_value;
        node->next = NULL;
        index = node->hash_key % this->tab_size;
        if(this->tab[index])
        {
            node->next = (this->tab)[index];
        }
        (this->tab)[index] = node;
        this->size++;
    }

    return 0;
}

HashTable* HashTable_Remove(HashTable* this, void* key)
{
    HashNode* node;
    unsigned int index;
    void* implementor_hash,* implementor_value;
    
    implementor_hash = this->iHash->implementor;
    this->iHash->implementor = key;
    index = IHash_HashFunc(this->iHash) % this->tab_size;
    this->iHash->implementor = implementor_hash;
    implementor_hash = this->iObjectKey->implementor;
    implementor_value = this->iObjectValue->implementor;
    node = (this->tab)[index];
    while(node)
    {
        this->iObjectKey->implementor = implementor_hash;
        if(IObject_Equal(this->iObjectKey, key))
        {
            break;
        }
    }

    if(node)
    {
        this->iObjectValue->implementor = node->value;
        IObject_Del(this->iObjectKey);
        IObject_Del(this->iObjectValue);
    }
    free(node);
    this->iObjectKey->implementor = implementor_hash;
    this->iObjectValue->implementor = implementor_value;

    return this;
}

static unsigned int _HashTable_HashFunc(void* implementor)
{
    unsigned int* hash_value;

    hash_value = (unsigned int*)implementor;

    return *hash_value;
}

