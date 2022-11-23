#include "IHash.h"

unsigned int IHash_HashFunc(IHash* this)
{
    return (*this->HashFunc)(this->implementor);
}
