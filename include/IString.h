#ifndef _ISTRING_H_
#define _ISTRING_H_

typedef struct _IString IString;

struct _IString
{
    void* implementor;
    char* (*GetStr)(void* implementor);
    int (*Copy)(void* implementor, char* string);
    IString* (*Clear)(void* implementor);
    int (*Length)(void* implementor);
    int (*Compare)(void* implementor, char* string);
    IString* (*Concat)(void* implementor, char* string);
    IString* (*SubStr)(void* implementor, char* string, int pos, int len);
    int (*Index)(void* implementor, char* string, int pos);
    IString* (*Replace)(void* implementor, char* string1, char* string2);
    IString* (*Insert)(void* implementor, int pos, char* string);
    IString* (*Delete)(void* implementor, int pos, int len);
    IString* (*ToUpper)(void* implementor);
    IString* (*ToLower)(void* implementor);
};

extern char* IString_GetStr(IString* this);

extern int IString_Copy(IString* this, char* string);

extern IString* IString_Clear(IString* this);

extern int IString_Length(IString* this);

extern int IString_Compare(IString* this, char* string);

extern IString* IString_Concat(IString* this, char* string);

extern IString* IString_SubStr(IString* this, char* string, int pos, int len);

extern int IString_Index(IString* this, char* string, int pos);

extern IString* IString_Replace(IString* this, char* string1, char* string2);

extern IString* IString_Insert(IString* this, int pos, char* string);

extern IString* IString_Delete(IString* this, int pos, int len);

extern IString* IString_ToUpper(IString* this);

extern IString* IString_ToLower(IString* this);

#endif /*_ISTRING_H_*/
