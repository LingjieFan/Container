#include "IList.h"

IList* IList_Clear(IList* this)
{
    return (*this->Clear)(this->implementor);
}

void* IList_Get(IList* this, int index)
{
    return (*this->Get)(this->implementor, index);
}

int IList_Index(IList* this, void* item)
{
    return (*this->Index)(this->implementor, item);
}

IList* IList_Insert(IList* this, int index, void* item)
{
    return (*this->Insert)(this->implementor, index, item);
}

IList* IList_Add(IList* this, void* item)
{
    return (*this->Add)(this->implementor, item);
}

IList* IList_Remove(IList* this, int index)
{
    return (*this->Remove)(this->implementor, index);
}

int IList_Size(IList* this)
{
    return (*this->Size)(this->implementor);
}
