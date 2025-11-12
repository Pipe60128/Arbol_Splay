#ifndef SPLAY_TREE
#define SPLAY_TREE
#include <iostream>
#include "Node.h"

template <typename T>
class SplayTree {
private:
    Node<T>* root;
    void print(Node<T>* node, int nr, int nl) const;
    

    /* rotations */
    Node<T>* zig(Node<T>* node);
    Node<T>* zag(Node<T>* node);
    Node<T>* zigZig(Node<T>* node);
    Node<T>* zagZag(Node<T>* node);
    Node<T>* zigZag(Node<T>* node);
    Node<T>* zagZig(Node<T>* node);

    /*Operations*/
    void clear(Node<T>* node);
    Node<T>* splay(Node<T>* node, const T& value);
    int size(Node<T>* node) const;


public:
    SplayTree(): root(nullptr){}
    ~SplayTree();
    void clear();
    void print() const;
    void insert(const T& value);
    bool remove(const T& value);
    bool search(const T& value);
    int size() const;
    


};
#include "SplayTree.tpp"
#endif
