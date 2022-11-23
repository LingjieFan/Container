#include "IQueue.h"

IQueue* IQueue_Clear(IQueue* this)
{
    return (*this->Clear)(this->implementor);
}

void* IQueue_Get(IQueue* this)
{
    return (*this->Get)(this->implementor);
}

IQueue* IQueue_EnQueue(IQueue* this, void* item)
{
    return (*this->EnQueue)(this->implementor, item);
}

IQueue* IQueue_DeQueue(IQueue* this)
{
    return (*this->DeQueue)(this->implementor);
}

int IQueue_Size(IQueue* this)
{
    return (*this->Size)(this->implementor);
}
