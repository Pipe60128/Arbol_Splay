#include <iostream>
#include "SplayTree.h"
using namespace std;

int main() {
    SplayTree<int> arbol;
    arbol.insert(403);
    arbol.print();
    arbol.insert(430);
    arbol.print();
    cout<<"\n"<<endl;
    arbol.insert(555);
    arbol.print();
    cout<<"\n"<<endl;
    arbol.insert(1252);
    arbol.print();
    cout<<"\n"<<endl;
    arbol.insert(152);
    arbol.print();
    cout<<"--remove--"<<endl;
    arbol.remove(152);
    arbol.print();
    cout<<"--search--"<<endl;
    arbol.search(205);
    arbol.print();
    cout<<"--size--"<<endl;
    cout<< arbol.size()<<endl;
    return 0;
}