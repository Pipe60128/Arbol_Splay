#include <iostream>
#include "SplayTree.h"
using namespace std;

int main() {
    SplayTree<int> arbol;
    arbol.insert(10);
    arbol.insert(20);
    arbol.insert(30);
    arbol.insert(40);
    arbol.print();
    cout<<"\n"<<endl;
    arbol.insert(50);
    arbol.print();
    cout<<"\n"<<endl;
    arbol.insert(25);
    arbol.print();
    cout<<"\n"<<endl;
    arbol.insert(5);
    arbol.print();
    cout<<"--remove--"<<endl;
    arbol.remove(25);
    arbol.print();
    cout<<"--search--"<<endl;
    arbol.search(20);
    arbol.print();
    cout<<"--size--"<<endl;
    cout<< arbol.size()<<endl;
    return 0;
}