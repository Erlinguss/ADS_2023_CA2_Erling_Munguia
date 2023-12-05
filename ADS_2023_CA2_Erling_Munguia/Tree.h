#pragma once
#include "DList.h"

template<class T>
class Tree
{
public:
    T data;
    Tree<T>* parent;
    DList<Tree<T>*> children;


    Tree(T item);
    int count();
    T getData() const;
    Tree<T>* getRoot(); 

};

template <class T>
T Tree<T>::getData() const
{
    return data;
}

template <class T>
Tree<T>::Tree( T item) : data(item), parent(nullptr)
{
}

template <class T>
Tree<T>* Tree<T>::getRoot()
{
    Tree<T>* currentNode = this;
    while (currentNode->parent != nullptr)
    {
        currentNode = currentNode->parent;
    }
    return currentNode;
}

// ==== task 2a Count number of items(File/Folder) ====

template <class T>
int Tree<T>::count()
{
    int totalCount = 1;
    DListIterator<Tree<T>*> childIter = children.getIterator();

    // === Debugging output ===
    std::cout << "Debug: Counting node with data " << data << std::endl;

    while (childIter.isValid())
    {
        totalCount += childIter.item()->count();
        childIter.advance();
    }

    // === Debugging output ===
    std::cout << "Debug: Total count for node " << data << " is " << totalCount << std::endl;

    return totalCount;
}


