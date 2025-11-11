#pragma once
#include "SplayTree.h"
#include <iostream>
using namespace std;

/* util */
template <typename T>
int SplayTree<T>::height(Node<T>* n) const {
    return n ? n->getHeight() : 0;
}

template <typename T>
int SplayTree<T>::maxValue(int a, int b) const {
    return (a>b) ? a : b;
}

/* rotations */
template <typename T>
Node<T>* SplayTree<T>::zig(Node<T>* node) {
    Node<T>* temp= node->getLeft();
    Node<T>* temp2= temp->getRight();
    temp->setRight(node);
    node->setLeft(temp2);
    node->setHeight(1+ maxValue(height(node->getLeft()), height(node->getRight())));
    temp->setHeight(1+ maxValue(height(temp->getRight()), height(temp->getLeft())));
    return temp;
}
template <typename T>
Node<T>* SplayTree<T>::zag(Node<T>* node) {
    Node<T>* temp= node->getRight();
    Node<T>* temp2= temp->getLeft();
    temp->setLeft(node);
    node->setRight(temp2);
    node->setHeight(1+ maxValue(height(node->getLeft()), height(node->getRight())));
    temp->setHeight(1+ maxValue(height(temp->getRight()), height(temp->getLeft())));
    return temp;
}

template <typename T>
Node<T>* SplayTree<T>::zigZig(Node<T>* node) {
    node = zag(node->getLeft());
    return zag(node);
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

    // Valor está en el subárbol izquierdo
    if (value < node->getData()) {
        if (!node->getLeft()) return node;
        
        // Zig-Zig (Left Left)
        if (value < node->getLeft()->getData()) {
            if (node->getLeft()->getLeft()) {
                node->getLeft()->setLeft(splay(node->getLeft()->getLeft(), value));
                return zigZig(node);
            }
        }
        // Zig-Zag (Left Right)
        else if (value > node->getLeft()->getData()) {
            if (node->getLeft()->getRight()) {
                node->getLeft()->setRight(splay(node->getLeft()->getRight(), value));
                return zigZag(node);
            }
        }
        
        // Zig simple
        return node->getLeft() ? zig(node) : node;
    }
    // Valor está en el subárbol derecho
    else {
        if (!node->getRight()) return node;
        
        // Zag-Zag (Right Right)
        if (value > node->getRight()->getData()) {
            if (node->getRight()->getRight()) {
                node->getRight()->setRight(splay(node->getRight()->getRight(), value));
                return zagZag(node);
            }
        }
        // Zag-Zig (Right Left)
        else if (value < node->getRight()->getData()) {
            if (node->getRight()->getLeft()) {
                node->getRight()->setLeft(splay(node->getRight()->getLeft(), value));
                return zagZig(node);
            }
        }
        
        // Zag simple
        return node->getRight() ? zag(node) : node;
    }
}
 


template <typename T>
Node<T>* SplayTree<T>::insert(Node<T>* node, const T& value) {
    if (!node) {
        return new Node<T>(value);
    }
    node = splay(node, value);
    
    if (node->getData() == value) {
        return node;
    }

    Node<T>* newNode = new Node<T>(value);

    if (value < node->getData()) {
        newNode->setRight(node);
        newNode->setLeft(node->getLeft());
        node->setLeft(nullptr);
    } else {
        newNode->setLeft(node);
        newNode->setRight(node->getRight());
        node->setRight(nullptr);
    }
    
    
    node->setHeight(1 + maxValue(height(node->getLeft()), height(node->getRight())));
    newNode->setHeight(1 + maxValue(height(newNode->getLeft()), height(newNode->getRight())));
    
    return newNode;
}
template <typename T>
Node<T>* SplayTree<T>::remove(Node<T>* node, const T& value) {
     if (node == nullptr) return node; 

    if (value < node->getData()) {
        node->setLeft(remove(node->getLeft(), value));
    } else if (value > node->getData()) {
        node->setRight(remove(node->getRight(), value));
    } else {
        if (node->getLeft()==nullptr && node->getRight()==nullptr) {
            delete node;
            return nullptr;
        } else if (node->getRight() == nullptr) {
            Node<T>* temp = node->getLeft();
            delete node;
            return temp;

        } else if (node->getLeft() == nullptr) {
            Node<T>* temp = node->getRight();
            delete node;
            return temp;
        } else {
            Node<T>* temp = node->getLeft();
            while(temp && temp->getRight() != nullptr) {
                temp = temp->getRight();
            }
            T newData = temp->getData();
            node->setData(newData);
            node->setLeft(remove(node->getLeft(), node->getData()));
        }
    } 

    if (node == nullptr) return nullptr;

    node->setHeight(1 + maxValue(height(node->getLeft()),height(node->getRight())));
    
    if ( node-> getLeft() && node->getLeft()->getLeft() && value < node->getLeft()->getData()) {
        return zigzig(node); //check zigzig
    }
    if (  node-> getRight() && node->getRight()->getRight() && value > node->getRight()->getData()) {
        return zagzag(node); // check zagzag
    }
    if (  node-> getRight() && node->getRight()->getLeft() && value < node->getRight()->getData()) {
        return zigZig(node); // check zagzig
    }
    if ( node-> getLeft() && node->getLeft()->getRight() && value > node->getLeft()->getData()) {
        return zigZag(node); // check zigzag
    }
    if (node->getLeft() && value > node->getLeft()->getData()) {
        return zig(node);
    }
    if (node->getRight() && value < node->getData()) {
        return zag(node);
    }
    return node;
}

template <typename T>
void SplayTree<T>::destroy(Node<T>* node) {
    delete node;
    node = nullptr;
}

template <typename T>
SplayTree<T>::~SplayTree() {
    
}
template <typename T>
void SplayTree<T>::clear() {
    destroy(root);

}
template <typename T>
void SplayTree<T>::remove(const T& value) {
    remove(root, value);

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
template <typename T>
void SplayTree<T>::insert(const T& value) {
    root= insert(root, value);
}


template<typename T>
bool SplayTree<T>::search(Node<T>* node, const T& value) const {
    if (node == nullptr) {
        return false;
    }
    if (value > node->getData()){
        cout<<node->getData()<<"-> ";
    } else if(value == node->getData()) {
        cout<<node->getData();
    } else if (!node) {
        cout<<"->";
        return false;
    }
    
    if (value==node->getData()) {
        return true;
    }
    if (value < node->getData()) {
        return search(node->getLeft(), value);
    }
    return search(node->getRight(), value);
}

template<typename T>
void SplayTree<T>::search(const T& v) const {
    cout<<"_________________________"<<"\n|       BUSCANDO        |"<<"\n|___________________s____|"<<endl;
    bool result = search(root, v);
    if (result != true){
        cout<<" NO SE HA ENCONTRADO EL ELEMENTO"<<endl;
    }
    
}


