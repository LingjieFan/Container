#include "IString.h"

char* IString_GetStr(IString* this)
{
    return (*this->GetStr)(this->implementor);
}

int IString_Copy(IString* this, char* string)
{
    return (*this->Copy)(this->implementor, string);
}

IString* IString_Clear(IString* this)
{
    return (*this->Clear)(this->implementor);
}

int IString_Length(IString* this)
{
    return (*this->Length)(this->implementor);
}

int IString_Compare(IString* this, char* string)
{
    return (*this->Compare)(this->implementor, string);
}

IString* IString_Concat(IString* this, char* string)
{
    return (*this->Concat)(this->implementor, string);
}

IString* IString_SubStr(IString* this, char* string, int pos, int len)
{
    return (*this->SubStr)(this->implementor, string, pos, len);
}

int IString_Index(IString* this, char* string, int pos)
{
    return (*this->Index)(this->implementor, string, pos);
}

IString* IString_Replace(IString* this, char* string1, char* string2)
{
    return (*this->Replace)(this->implementor, string1, string2);
}

IString* IString_Insert(IString* this, int pos, char* string)
{
    return (*this->Insert)(this->implementor, pos, string);
}

IString* IString_Delete(IString* this, int pos, int len)
{
    return (*this->Delete)(this->implementor, pos, len);
}

IString* IString_ToUpper(IString* this)
{
    return (*this->ToUpper)(this->implementor);
}

IString* IString_ToLower(IString* this)
{
    return (*this->ToLower)(this->implementor);
}
