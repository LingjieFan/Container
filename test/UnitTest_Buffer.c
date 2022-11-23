#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Class.h"
#include "IUnitTest.h"
#include "IObject.h"
#include "IString.h"
#include "Buffer.h"
#include "UnitTest_Buffer.h"

Class UnitTest_Buffer_Class = {CLASS};

struct _UnitTest_Buffer
{
    Class* class;
    IUnitTest* iUnitTest;
};

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

static void _UnitTest_Buffer_TestAll(void* implementor);

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
        if(this->real_size + increment <= this->max_size)
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

static Buffer* _Stub_Buffer_Replace(Buffer* this, char* string1, char* string2)
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

static void Test_Buffer_New()
{
    Buffer* buffer;

    buffer = Buffer_New(1, 5);
    assert(buffer->class == BUFFER);
    assert(buffer->iObject->implementor == buffer);
    assert(buffer->iString->implementor == buffer);
    assert(buffer->min_size == 1);
    assert(buffer->max_size == 5);
    assert(buffer->real_size == 1);
    assert(*(buffer->start) == '\0');
    assert(buffer->tail == buffer->start);
    assert(buffer->end == buffer->start);
    Buffer_Del(buffer);
    printf("Test_Buffer_New Success.\n");
}

static void Test_Buffer_Concat_FullSpace()
{
    Buffer* buffer;
    char* string;

    buffer = Buffer_New(1, 10);
    Buffer_Concat(buffer, "123");
    string = Buffer_GetStr(buffer);
    assert(strcmp(string,"123") == 0);
    assert(buffer->tail == (buffer->start + 3));
    assert(buffer->end == (buffer->start + 3));
    assert(buffer->real_size == 4);
    Buffer_Del(buffer);
    printf("Test_Buffer_Concat_FullSpace Success.\n");
}

static void Test_Buffer_Concat_NotFullSpace()
{
    Buffer* buffer;
    char* string;

    buffer = Buffer_New(1, 3);
    Buffer_Concat(buffer, "123");
    string = Buffer_GetStr(buffer);
    assert(strcmp(string, "12") == 0);
    assert(buffer->tail == (buffer->start + 2));
    assert(buffer->end == (buffer->start + 2));
    assert(buffer->real_size == 3);
    Buffer_Del(buffer);
    printf("Test_Buffer_Concat_NotFullSpace Success.\n");
}

static void Test_Buffer_Concat_InfiniteSpace()
{
    Buffer* buffer;
    char* string;

    buffer = Buffer_New(1, 0);
    Buffer_Concat(buffer, "123");
    string = Buffer_GetStr(buffer);
    assert(strcmp(string, "123")==0);
    assert(buffer->tail == (buffer->start+3));
    assert(buffer->end == (buffer->start+4));
    assert(buffer->real_size == 5);
    Buffer_Del(buffer);
    printf("Test_Buffer_Concat_InfiniteSpace Success.\n");
}

static void Test_Buffer_SubStr()
{
    Buffer* buffer;
    char* string;
    
    buffer = Buffer_New(1, 10);
    Buffer_SubStr(buffer, "123", 1, 1);
    string = Buffer_GetStr(buffer);
    assert(strcmp(string, "2")==0);
    assert(buffer->tail == (buffer->start+1));
    assert(buffer->end == (buffer->start+1));
    assert(buffer->real_size == 2);
    Buffer_Del(buffer);
    printf("Test_Buffer_SubStr Success.\n");
}

static void Test_Buffer_Index()
{
    Buffer* buffer;
    int index;

    buffer = Buffer_New(1, 10);
    Buffer_Concat(buffer, "123456789");
    index = Buffer_Index(buffer, "789", 2);
    assert(index == 6);
    Buffer_Del(buffer);
    printf("Test_Buffer_Index Success.\n");
}

static void Test_Buffer_Replace()
{
    Buffer* buffer;
    char* string;

    buffer = Buffer_New(1, 30);
    Buffer_Concat(buffer, "123451239");
    _Stub_Buffer_Replace(buffer, "123", "*");
    string = Buffer_GetStr(buffer);
    printf("%s", string);
    printf("Test_Buffer_GetStr Success.\n");
}

UnitTest_Buffer* UnitTest_Buffer_New()
{
    UnitTest_Buffer* unit_test;

    unit_test = (UnitTest_Buffer*)malloc(sizeof(UnitTest_Buffer)+sizeof(IUnitTest));
    unit_test->class = UNITTEST_BUFFER;
    unit_test->iUnitTest = (IUnitTest*)(unit_test+1);
    unit_test->iUnitTest->implementor = unit_test;
    unit_test->iUnitTest->TestAll = _UnitTest_Buffer_TestAll;
    
    return unit_test;
}

UnitTest_Buffer* UnitTest_Buffer_Del(UnitTest_Buffer* this)
{
    free(this);

    return NULL;
}

IUnitTest* UnitTest_Buffer_GetIUnitTest(UnitTest_Buffer* this)
{
    return this->iUnitTest;
}

void UnitTest_Buffer_TestAll(UnitTest_Buffer* this)
{
    Test_Buffer_New();
    Test_Buffer_Concat_FullSpace();
    Test_Buffer_Concat_NotFullSpace();
    Test_Buffer_Concat_InfiniteSpace();
    Test_Buffer_SubStr();
    Test_Buffer_Index();
    Test_Buffer_Replace();
}

static void _UnitTest_Buffer_TestAll(void* implementor)
{
    UnitTest_Buffer* unit_test;

    unit_test = (UnitTest_Buffer*)implementor;
    UnitTest_Buffer_TestAll(unit_test);
}

