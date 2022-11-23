#include "IStack.h"

IStack* IStack_Clear(IStack* this)
{
    return (*this->Clear)(this->implementor);
}

void* IStack_Get(IStack* this)
{
    return (*this->Get)(this->implementor);
}

IStack* IStack_Push(IStack* this, void* item)
{
    return (*this->Push)(this->implementor, item);
}

IStack* IStack_Pop(IStack* this)
{
    return (*this->Pop)(this->implementor);
}

int IStack_Size(IStack* this)
{
    return (*this->Size)(this->implementor);
}
