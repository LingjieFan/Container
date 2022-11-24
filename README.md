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



## Contact us

Author: Lingjie Fan (A student from Fudan University)

Email: 20210190044@fudan.edu.cn
