#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "IObject.h"
#include "IString.h"
#include "Class.h"
#include "Object.h"
#include "Buffer.h"

Class Buffer_Class = {OBJECT};

struct _Buffer
{
    Class* class;
    IObject* iObject;
    IString* iString;
    char* start;
    char* end;
    char* tail;
    int min_size;
    int max_size;
    int real_size;
};

static void* _Buffer_New(void* implementor);
static void* _Buffer_Del(void* implementor);
static int _Buffer_Copy(void* implementor, void* object);
static int _Buffer_Equal(void* implementor, void* object);
static char* _Buffer_GetStr(void* implementor);
static int _Buffer_CopyStr(void* implementor, char* string);
static IString* _Buffer_Clear(void* implementor);
static int _Buffer_Length(void* implementor);
static int _Buffer_Compare(void* implementor, char* string);
static IString* _Buffer_Concat(void* implementor, char* string);
static IString* _Buffer_SubStr(void* implementor, char* string, int pos, int len);
static int _Buffer_Index(void* implementor, char* string, int pos);
static IString* _Buffer_Replace(void* implementor, char* string1, char* string2);
static IString* _Buffer_Insert(void* implementor, int pos, char* string);
static IString* _Buffer_Delete(void* implementor, int pos, int len);
static IString* _Buffer_ToUpper(void* implementor);
static IString* _Buffer_ToLower(void* implementor);

Buffer* Buffer_New(int min_size, int max_size)
{
    Buffer* buffer;

    if(min_size == 0)
    {
        return NULL;
    }
    if(max_size!=0 && max_size<min_size)
    {
        return NULL;
    }

    buffer = (Buffer*)malloc(sizeof(Buffer)+sizeof(IObject)+sizeof(IString));
    buffer->class = BUFFER;
    buffer->iObject = (IObject*)(buffer+1);
    buffer->iObject->implementor = buffer;
    buffer->iObject->New = _Buffer_New;
    buffer->iObject->Del = _Buffer_Del;
    buffer->iObject->Copy = _Buffer_Copy;
    buffer->iObject->Equal = _Buffer_Equal;
    buffer->iString = (IString*)(buffer->iObject+1);
    buffer->iString->implementor = buffer;
    buffer->iString->GetStr = _Buffer_GetStr;
    buffer->iString->Copy = _Buffer_CopyStr;
    buffer->iString->Clear = _Buffer_Clear;
    buffer->iString->Length = _Buffer_Length;
    buffer->iString->Compare = _Buffer_Compare;
    buffer->iString->Concat = _Buffer_Concat;
    buffer->iString->SubStr = _Buffer_SubStr;
    buffer->iString->Index = _Buffer_Index;
    buffer->iString->Replace = _Buffer_Replace;
    buffer->iString->Insert = _Buffer_Insert;
    buffer->iString->Delete = _Buffer_Delete;
    buffer->iString->ToUpper = _Buffer_ToUpper;
    buffer->iString->ToLower = _Buffer_ToLower;
    buffer->min_size = min_size;
    buffer->max_size = max_size;
    buffer->real_size = min_size;
    buffer->start = (char*)malloc(sizeof(char)*min_size);
    *(buffer->start) = '\0';
    buffer->tail = buffer->start;
    buffer->end = buffer->start + min_size - 1;

    return buffer;
}

Buffer* Buffer_Del(Buffer* this)
{
    free(this->start);
    free(this);
    
    return NULL;
}

IObject* Buffer_GetIObject(Buffer* this)
{    
    return this->iObject;
}

IString* Buffer_GetIString(Buffer* this)
{   
    return this->iString;
}

char* Buffer_GetStr(Buffer* this)
{
    return this->start;
}

static int Buffer_ReSize(Buffer* this, int increment)
{
    int rc;
    int new_size;
    int len;
    char* p;

    rc = 0;
    new_size = 0;
    if(this->max_size != 0 && this->real_size >= this->max_size)
    {
        return 1;
    }

    if(this->max_size == 0)
    {
        new_size = this->real_size + 1.5 * increment;
    }
    else
    {
        if((this->real_size + increment) <= this->max_size)
        {
            new_size = this->real_size + increment;
        }
        else
        {
            new_size = this->max_size;
            rc = 1;
        }
    }

    len = this->tail - this->start;
    p = (char*)realloc(this->start, new_size);
    if(!p)
    {
        return -1;
    }
    else
    {
        this->start = p;
        this->tail = p + len;
        this->real_size = new_size;
        this->end = this->start + new_size - 1;
    }

    return rc;
}

int Buffer_Copy(Buffer* this, char* string)
{
    int rc;
    int len;
    char* p;
    
    len = strlen(string)+1;
    if(len > this->real_size)
    {
        rc = Buffer_ReSize(this, len-this->real_size);
        if(rc>0)
        {
            memcpy(this->start, string, this->real_size);
            *(this->end) = '\0';
            this->tail = this->end;

            return 0;
        }
        else if(rc < 0)
        {
            return 0;
        }
    }
    memcpy(p, string, len);
    this->tail = this->start + len - 1;
    
    return 1;
}

Buffer* Buffer_Clear(Buffer* this)
{
    *(this->start) = '\0';
    this->tail = this->start;
    
    return this;
}

int Buffer_Length(Buffer* this)
{
    return this->tail - this->start;
}

int Buffer_Compare(Buffer* this, char* string)
{
    return !strcmp(this->start, string);
}

Buffer* Buffer_Concat(Buffer* this, char* string)
{
    int len1, len2;
    int rc;

    len1 = this->tail - this->start;
    len2 = strlen(string) + 1;
    len1 += len2;
    
    if(len1>this->real_size)
    {
        rc = Buffer_ReSize(this, len1 - this->real_size);
        if(rc>0)
        {
            int left_len;

            left_len = this->end - this->tail;
            memcpy(this->tail, string, left_len);
            *(this->end) = '\0';
            this->tail = this->end;

            return this;
        }
        else if(rc<0)
        {
            return this;
        }
    }
    memcpy(this->tail, string, len2);
    this->tail = this->start + len1 - 1;
    
    return this;
}

Buffer* Buffer_SubStr(Buffer* this, char* string, int pos, int len)
{
    int rc;
    char* sub_string;
    
    sub_string = string + pos;
    if(len>=this->real_size)
    {
        rc = Buffer_ReSize(this, len - this->real_size + 1);
        if(rc>0)
        {
            int left_len;

            left_len = this->end - this->tail;
            memcpy(this->start, sub_string, left_len);
            *(this->end) = '\0';
            this->tail = this->end;

            return this;
        }
        else if(rc<0)
        {
            return this;
        }        
    }    
    memcpy(this->start, sub_string, len+1);
    this->tail = this->start + len;
    *(this->tail) = '\0';
    
    return this;
}

int Buffer_Index(Buffer* this, char* string, int pos)
{
    char* sub_string;
    
    sub_string = strstr(this->start+pos, string);
    if(sub_string)
    {
        return (int)(sub_string - this->start);
    }
    
    return -1;
}

Buffer* Buffer_Replace(Buffer* this, char* string1, char* string2)
{
    register int i;
    int var_len, len, string2_len, rc;
    char* now_string,* next_string;
    
    now_string = this->start;
    len = this->tail - this->start;
    string2_len = strlen(string2);
    var_len = strlen(string1) - string2_len;
    next_string = strstr(now_string, string1);
    while(next_string != NULL)
    {
        int index;
        
        index = (int)(next_string - now_string);
        
        if((len+var_len)>=this->real_size)
        {
            rc = Buffer_ReSize(this, var_len+1);
            if(rc!=0)
            {
                return this;
            }
        }
        
        for(i=len+1;i>index;i++)
        {
            *(now_string+i+var_len) = *(now_string+i);
        }
        strncpy(next_string, string2, string2_len);
        this->tail += var_len;
        next_string = strstr(now_string, string1);
    }
    
    return this;
}

Buffer* Buffer_Insert(Buffer* this, int pos, char* string)
{
    register int i;
    int len, len1, len2;
    
    len2 = strlen(string);
    len1 = this->tail - this->start;
    len = len1 + len2;
    if(len>=this->real_size)
    {
        Buffer_ReSize(this, len - this->real_size+1);       
    }
    for(i=len1+1;i>pos;i++)
    {
        *(this->start+i+len2) = *(this->start+i);
    }
    strncpy(this->start+pos, string, len2);
    this->tail += len1;
    
    return this;
}

Buffer* Buffer_Delete(Buffer* this, int pos, int len)
{
    register int i;
    int len_string;
    
    len_string = this->tail - this->start;
    for(i=pos;i<=len_string;i++)
    {
       *(this->start+pos)=*(this->start+pos+len);
    }
    this->tail -= len;
}

Buffer* Buffer_ToUpper(Buffer* this)
{
    register int i;
    int len;

    len = this->tail-this->start;
    for(i=0;i<len;i++)
    {
        if((*(this->start+i)>='a')&&(*(this->start+i)<='z'))
        {
            *(this->start+i) -= 32;
        }
    }

    return this;    
}

Buffer* Buffer_ToLower(Buffer* this)
{
    register int i;
    int len;

    len = this->tail - this->start;
    for(i=0;i<len;i++)
    {
        if((*(this->start+i)>='A')&&(*(this->start+i)<='Z'))
        {
            *(this->start+i) += 32;
        }
    }

    return this;    
}

int Buffer_Equal(Buffer* this, Buffer* object)
{
    register int i;
    int len1, len2;
    Buffer* string1,* string2;

    string1 = this;
    string2 = object;
    len1 = string1->tail - string1->start;
    len2 = string2->tail - string2->start;
    if(len1 == len2)
    {
        for(i=0;i<len1;i++)
        {
            if(*(string1->start+i)!=*(string2->start+i))
            {
                return 0;
            }
        }
        
        return 1;
    }

    return 0;
}

static void* _Buffer_New(void* implementor)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;

    return Buffer_New(buffer->min_size, buffer->max_size);
}

static void* _Buffer_Del(void* implementor)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;

    return Buffer_Del(buffer);
}

static int _Buffer_Copy(void* implementor, void* object)
{
    Buffer* string1,* string2;

    string1 = (Buffer*)implementor;
    string2 = (Buffer*)object;

    return Buffer_Copy(string1, string2->start);
}

static int _Buffer_Equal(void* implementor, void* object)
{
    register int i;
    int len1, len2;
    Buffer* string1,* string2;

    string1 = (Buffer*)implementor;
    string2 = (Buffer*)object;
    
    return Buffer_Equal(string1, string2);
}

static char* _Buffer_GetStr(void* implementor)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;

    return Buffer_GetStr(buffer);
}

static int _Buffer_CopyStr(void* implementor, char* string)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;

    return Buffer_Copy(buffer, string);
}

static IString* _Buffer_Clear(void* implementor)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;
    Buffer_Clear(buffer);

    return buffer->iString;
}

static int _Buffer_Length(void* implementor)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;

    return Buffer_Length(buffer);
}

static int _Buffer_Compare(void* implementor, char* string)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;

    return Buffer_Compare(buffer, string);
}

static IString* _Buffer_Concat(void* implementor, char* string)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;
    Buffer_Concat(buffer, string);

    return buffer->iString;
}

static IString* _Buffer_SubStr(void* implementor, char* string, int pos, int len)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;
    Buffer_SubStr(buffer, string, pos, len);

    return buffer->iString;
}

static int _Buffer_Index(void* implementor, char* string, int pos)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;

    return Buffer_Index(buffer, string, pos);
}

static IString* _Buffer_Replace(void* implementor, char* string1, char* string2)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;
    Buffer_Replace(buffer, string1, string2);

    return buffer->iString;
}

static IString* _Buffer_Insert(void* implementor, int pos, char* string)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;
    Buffer_Insert(buffer, pos, string);

    return buffer->iString;
}

static IString* _Buffer_Delete(void* implementor, int pos, int len)
{
    Buffer* buffer;

    buffer = (Buffer*)implementor;
    Buffer_Delete(buffer, pos, len);

    return buffer->iString;
}

static IString* _Buffer_ToUpper(void* implementor)
{
    Buffer* buffer;
    
    buffer = (Buffer*)implementor;
    Buffer_ToUpper(buffer);
    
    return buffer->iString;
}

static IString* _Buffer_ToLower(void* implementor)
{
    Buffer* buffer;
    
    buffer = (Buffer*)implementor;
    Buffer_ToLower(buffer);

    return buffer->iString;
}
