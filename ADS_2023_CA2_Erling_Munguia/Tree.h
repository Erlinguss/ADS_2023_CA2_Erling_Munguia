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
    int count() const;
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

// ===  Number of items within a given folder directory ===
template <class T>
int Tree<T>::count() const
{
    int totalCount = 1; 
    DListIterator<Tree<T>*> childIter = children.getIterator();
    while (childIter.isValid())
    {
        totalCount += childIter.item()->count();
        childIter.advance();
    }
    return totalCount;
}
