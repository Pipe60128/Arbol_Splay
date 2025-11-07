#ifndef SPLAY_TREE
#define SPLAY_TREE
#include <iostream>
#include "Node.h"

template <typename T>
class SplayTree {
private:
    Node<T>* root;
    void print(Node<T>* node, int nr, int nl) const;
    
    /* util */
    int height(Node<T>* n) const;
    int maxValue(int a, int b) const;

    /* rotations */
    Node<T>* zig(Node<T>* node);
    Node<T>* zag(Node<T>* node);
    Node<T>* zigZig(Node<T>* node);
    Node<T>* zagZag(Node<T>* node);
    Node<T>* zigZag(Node<T>* node);
    Node<T>* zagZig(Node<T>* node);

    /*Operations*/
    Node<T>* insert(Node<T>* node, const T& value);
    Node<T>* remove(Node<T>* node, const T& value);
    void destroy(Node<T>* node);
    bool search(Node<T>* node, const T& value) const;


public:
    SplayTree(): root(nullptr){}
    ~SplayTree();
    void clear();
    void print() const;
    void insert(const T& value);
    void remove(const T& value);
    void search(const T& value) const;
    


};
#include "SplayTree.tpp"
#endif
