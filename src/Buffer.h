#ifndef _BUFFER_H_
#define _BUFFER_H_

#define BUFFER &Buffer_Class

typedef struct _Class Class;
typedef struct _IObject IObject;
typedef struct _IString IString;
typedef struct _Buffer Buffer;

extern Class Buffer_Class;

extern Buffer* Buffer_New(int min_size, int max_size);

extern Buffer* Buffer_Del(Buffer* this);

extern IObject* Buffer_GetIObject(Buffer* this);

extern IString* Buffer_GetIString(Buffer* this);

extern char* Buffer_GetStr(Buffer* this);

extern int Buffer_Copy(Buffer* this, char* string);

extern Buffer* Buffer_Clear(Buffer* this);

extern int Buffer_Length(Buffer* this);

extern int Buffer_Compare(Buffer* this, char* string);

extern Buffer* Buffer_Concat(Buffer* this, char* string);

extern Buffer* Buffer_SubStr(Buffer* this, char* string, int pos, int len);

extern int Buffer_Index(Buffer* this, char* string, int pos);

extern Buffer* Buffer_Replace(Buffer* this, char* string1, char* string2);

extern Buffer* Buffer_Insert(Buffer* this, int pos, char* string);

extern Buffer* Buffer_Delete(Buffer* this, int pos, int len);

extern Buffer* Buffer_ToUpper(Buffer* this);

extern Buffer* Buffer_ToLower(Buffer* this);

#endif /*_DYNAMICSTRING_H_*/
