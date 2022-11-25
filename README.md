# Container

![pureC](https://img.shields.io/github/languages/top/LingjieFan/Container)
![size](https://img.shields.io/github/languages/code-size/LingjieFan/Container)
![request](https://img.shields.io/github/issues-pr-closed-raw/LingjieFan/Container)
![license](https://img.shields.io/github/license/LingjieFan/Container)
![commit](https://img.shields.io/github/last-commit/LingjieFan/Container)
![star](https://img.shields.io/github/stars/LingjieFan/Container?style=social)
![star](https://img.shields.io/github/watchers/LingjieFan/Container?style=social)

Container is a library of some basic data structure: ArrayList, LinkedList, HashTable, Buffer(String) ... based on [ObjectC](https://github.com/LingjieFan/ObjectC). By using interface IObject in ObjectC. A generic arraylist, linkedlist, and hashtable is contructed.

Key features for generic data structures are included:

* Supporting basic data structure: arraylist, linkedlist, hashtable, buffer...
* Supporting generucs through IObject

## Installation

### Dependencies

* [ObjectC](https://github.com/LingjieFan/ObjectC): Add OOP object-oriented features to C! No macro definition! No new syntax! Only C. More like a coding standard for C.
* C compiler (gcc is used in the following examples)

### Linux

```cmd
gcc -c -fPIC -I ../include ArrayList.c -o ArrayList.o
gcc -c -fPIC -I ../include CircularArrayList.c -o CircularArrayList.o
gcc -c -fPIC -I ../include DoubleLinkedList.c -o DoubleLinkedList.o
gcc -c -fPIC -I ../include Buffer.c -o Buffer.o
gcc -c -fPIC -I ../include IList.c -o IList.o
gcc -c -fPIC -I ../include IQueue.c -o IQueue.o
gcc -c -fPIC -I ../include IStack.c -o IStack.o
gcc -c -fPIC -I ../include IString.c -o IString.o
gcc -c -fPIC -I ../include LinkedList.c -o LinkedList.o
gcc -c -fPIC -I ../include IHash.c -o IHash.o
gcc -c -fPIC -I ../include HashTable.c -o HashTable.o
gcc -shared -fPIC -L ../lib ArrayList.o CircularArrayList.o DoubleLinkedList.o Buffer.o IList.o IQueue.o IStack.o IString.o LinkedList.o IHash.o HashTable.o -lObjectC -o ../lib/libContainer.so
```

### Windows

```cmd
gcc -c -fPIC -I ../include ArrayList.c -o ArrayList.o
gcc -c -fPIC -I ../include CircularArrayList.c -o CircularArrayList.o
gcc -c -fPIC -I ../include DoubleLinkedList.c -o DoubleLinkedList.o
gcc -c -fPIC -I ../include Buffer.c -o Buffer.o
gcc -c -fPIC -I ../include IList.c -o IList.o
gcc -c -fPIC -I ../include IQueue.c -o IQueue.o
gcc -c -fPIC -I ../include IStack.c -o IStack.o
gcc -c -fPIC -I ../include IString.c -o IString.o
gcc -c -fPIC -I ../include LinkedList.c -o LinkedList.o
gcc -c -fPIC -I ../include IHash.c -o IHash.o
gcc -c -fPIC -I ../include HashTable.c -o HashTable.o
gcc -shared -fPIC -L ../lib ArrayList.o CircularArrayList.o DoubleLinkedList.o Buffer.o IList.o IQueue.o IStack.o IString.o LinkedList.o IHash.o HashTable.o -lObjectC -o ../lib/Container.dll
```
## Documentation

### Quick start

Here, we give a simple example of using ArrayList in Container.

1. Create an ArrayList object:

```C
ArrayList* array_list;

array_list = ArrayList_New(Double);
```

where Double is the IObject interface of c basic type double. Double is defined in [Basic.h](https://github.com/LingjieFan/ObjectC/blob/main/src/Basic.h) and [Basic.c](https://github.com/LingjieFan/ObjectC/blob/main/src/Basic.c).

2. Add items to the ArrayList:

```C
double item;

item = 5;
ArrayList_Add(array_list, &item);
item = 4;
ArrayList_Add(array_list, &item);
```

When a item is added into the ArrayList, ArrayList will create a deep copy in it.

3. Remove items to the ArrayList:

```C
ArrayList_Remove(array_list, 0);
```

4. Insert items to the ArrayList:

```C
item = 3;
ArrayList_Insert(array_list, 0, &item);
```

5. Get the size of ArrayList:

```C
int size;

size = ArrayList_Size(array_list);
```

6. Get the item in ArrayList:

```C
item = *(double*)ArrayList_Get(array_list, 1);
```

7. Delete ArrayList:

```C
ArrayList_Del(array_list);
```

### Generics

Thanks to IObject interface in ObjectC, the data structures in Containers can be used for object having IObject interface. For basic type in C, such as **double**, **float**, **int**, **double complex**, we give their IObject interface in [Basic.h](https://github.com/LingjieFan/ObjectC/blob/main/src/Basic.h) and [Basic.c](https://github.com/LingjieFan/ObjectC/blob/main/src/Basic.c).

If you want to create a new class, whose object could be added into data structures in Containers, the new class must inherit Object class, and implement IObject interface:

```C
typedef struct _NewClass NewClass;

struct _NewClass
{
    Class* class;
    IObject* iObject;
    //... other members in the structures
};
```

And a C function is used to expose its IObject interface

```C
IObject* NewClass_GetIObject(NewClass* this)
{
    return this->iObject;
}
```

Then ArrayList in Container accepts its IObject and create a ArrayList for NewClass

```C
ArrayList* array_list;

array_list = ArrayList_New(NewClass_GetIObject(new_class));
```

## Contact us

Author: Lingjie Fan (A student from Fudan University)

Email: 20210190044@fudan.edu.cn
