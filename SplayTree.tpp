#pragma once
#include "SplayTree.h"
#include <iostream>
using namespace std;


/* rotations */
template <typename T>
Node<T>* SplayTree<T>::zig(Node<T>* node) {
    Node<T>* temp= node->getLeft();
    Node<T>* temp2= temp->getRight();
    temp->setRight(node);
    node->setLeft(temp2);
    return temp;
}
template <typename T>
Node<T>* SplayTree<T>::zag(Node<T>* node) {
    Node<T>* temp= node->getRight();
    Node<T>* temp2= temp->getLeft();
    temp->setLeft(node);
    node->setRight(temp2);
    return temp;
}

template <typename T>
Node<T>* SplayTree<T>::zigZig(Node<T>* node) {
    node = zig(node->getLeft());
    return zig(node);
}

template <typename T>
Node<T>* SplayTree<T>::zagZag(Node<T>* node) {
    node = zag(node->getRight());
    return zag(node);
}

template <typename T>
Node<T>* SplayTree<T>:: zigZag(Node<T>* node) {
    node->setLeft(zag(node->getLeft()));
    return zig(node);
}

template <typename T>
Node<T>* SplayTree<T>:: zagZig(Node<T>* node) {
    node->setRight(zig(node->getRight()));
    return zag(node);
}

template <typename T>
Node<T>* SplayTree<T>::splay(Node<T>* node, const T& value) {
    if (!node || node->getData() == value) {
        return node;
    }
    //subárbol izquierdo
    if (value < node->getData()) {
        if (!node->getLeft()) return node;
        
        // Zig-Zig
        if (value < node->getLeft()->getData()) {
            if (node->getLeft()->getLeft()) {
                node->getLeft()->setLeft(splay(node->getLeft()->getLeft(), value));
                node = zig(node);
            }
        }
        // Zig-Zag 
        else if (value > node->getLeft()->getData()) {
            if (node->getLeft()->getRight()) {
                node->getLeft()->setRight(splay(node->getLeft()->getRight(), value));
                if (node->getLeft()->getRight() != nullptr) {
                    node->setLeft(zag(node->getLeft()));
                }
            }
        }
        
        // Zig 
        return (node->getLeft() == nullptr) ? node : zig(node) ;
    }
    //subárbol derecho
    else {
        if (!node->getRight()) return node;
        
        // Zag-Zag 
        if (value > node->getRight()->getData()) {
            if (node->getRight()->getRight()) {
                node->getRight()->setRight(splay(node->getRight()->getRight(), value));
                node = zag(node);
            }
        }
        // Zag-Zig
        else if (value < node->getRight()->getData()) {
            if (node->getRight()->getLeft()) {
                node->getRight()->setLeft(splay(node->getRight()->getLeft(), value));
                if (node->getRight()->getLeft() != nullptr) {
                    node->setRight(zag(node->getRight()));
                }
            }
        }
        
        // Zag 
        return (node->getRight() == nullptr)  ? node : zag(node) ;;
    }
}

template <typename T>
void SplayTree<T>::insert(const T& value) {
    if (!root) {
        root = new Node<T>(value);
        return;
    }
    root = splay(root, value);
    
    if (root->getData() == value) {
        return;
    }

    Node<T>* newNode = new Node<T>(value);

    if (value < root->getData()) {
        newNode->setRight(root);
        newNode->setLeft(root->getLeft());
        root->setLeft(nullptr);
    } else {
        newNode->setLeft(root);
        newNode->setRight(root->getRight());
        root->setRight(nullptr);
    }
    root = newNode;
}



template <typename T>
bool SplayTree<T>::remove(const T& value) {
    if (!root) return false;

    root = splay(root, value);

    if (root->getData() != value) {
        return false; 
    }

    Node<T>* Lbranch = root->getLeft();
    Node<T>* Rbranch = root->getRight();

    delete root;

    if (!Lbranch) {
        root = Rbranch;
        return true;
    }

    root = splay(Lbranch, value);
    root->setRight(Rbranch);

    return true;
}




template <typename T>
SplayTree<T>::~SplayTree() {
    clear();
    
}
template <typename T>
void SplayTree<T>::clear(Node<T>* node) {
    if (!node) return;
    clear(node->getLeft());
    clear(node->getRight());
    delete node;

}

template <typename T>
void SplayTree<T>::clear() {
    clear(root);
    root = nullptr;
}

 /*Print*/
template <typename T>
void SplayTree<T>::print(Node<T>* node, int nr, int nl) const {
    if (node == nullptr) return ;
    print(node->getRight(), nr + 1, nl);
    for (int i = 0; i < nr + nl; i++){
        cout<<"  ";
        for (int j = 0; j < nr + nl; j++){
        cout<<" "; 
        }
    }
    if (nr < nl ){
        cout<<node->getData()<<"-<"<<endl;
    } else if ( nr > nl ){
        cout<<node->getData()<<"-<"<<endl;
    } else {
        cout<<node->getData()<<endl;
    }
    print(node->getLeft(), nr, nl + 1);
}
template <typename T>
void SplayTree<T>::print() const {
    print(root,0,0);
}

template<typename T>
int SplayTree<T>::size(Node<T>* node) const {
    if (!node) {
        return 0;
    }
    return 1 + size(node->getLeft()) + size(node->getRight());
}

template<typename T>
int SplayTree<T>::size() const {
    return size(root);
}




template<typename T>
bool SplayTree<T>::search(const T& v)  {
    root = splay(root, v);
    if (root == nullptr) return false;
    if (root->getData() == v) return true;
    return false;
    
}


