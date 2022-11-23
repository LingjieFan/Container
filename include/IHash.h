#ifndef _IHASH_H_
#define _IHASH_H_

typedef struct _IHash IHash;

struct _IHash
{
    void* implementor;
    unsigned int (*HashFunc)(void* implementor);
};

extern unsigned int IHash_HashFunc(IHash* this);

#endif /*_IHASH_H_*/
