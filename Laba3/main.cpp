
#include "tree.h"
#include <iostream>
#include "Complex.h"

using namespace std;

int plus0(int n) {
    return n + 1;
}

Compl plus1(Compl numb){
    return {numb.Getre()+1, numb.Getim()+1};
}

Compl getCompl(int i) {
    int a,b;
        a = i;
        b = i+ 1;
     return Compl(a,b);
    }

bool func(int n) {
    return n > 3;
}

int main(){
    auto* NewTree = new Tree<int>;
    for (int i=0; i<8;++i){
        NewTree->insert(i);
    }
     cout << NewTree->getStr("NLR") << endl;
    auto* NewTree2 = new Tree<int>;
    for (int i=0; i<8;++i){
        NewTree2->insert(i);
    }
    
    NewTree2=NewTree2->where(func);
     cout << NewTree2->getStr("NLR") << endl;
    cout <<endl;
   // printt(NewTree->get_root());
    if ( NewTree->check(5)){
        cout<< "есть узел"<<endl;
    }
    else{
        cout<<"нет узла"<<endl;
    }
    if (NewTree->Equal(NewTree2)){
        cout<< "равны"<<endl;
    }
    else{
        cout<<"не равны"<<endl;
    }
    cout<<"высота дерева: "<< endl;
    cout<< NewTree2->height()<<endl;
    cout<<"сумма всех узлов дерева: "<<endl;
    cout<<NewTree2->reduce(plus0)<<endl;
    NewTree2->map(plus0);
    cout << NewTree2->getStr("NLR") << endl;
    NewTree2->deleteTree();
    auto* NewTree3 = new Tree<int>;
    for (int i=0; i<3;++i){
        NewTree3->insert(i);
    }
    auto* Sub = new Tree<int>;
    cout << NewTree3->getStr("NLR") << endl;
    if (NewTree->ContainSub(NewTree3)){
        cout<< "содержит"<<endl;
         Sub = NewTree->SubTree(NewTree3->get_root()->key);
         cout << Sub->getStr("NLR") << endl;
        }
        else{
            cout<<"не содержит"<<endl;
        }
    NewTree->remove( 2);
    cout << (NewTree)->getStr("NLR") << endl;
    auto* NewTreeComp = new Tree<Compl>;
    for (int i=0; i<8;++i){
        Compl com1 = getCompl(i);
        NewTreeComp->insert(com1);
    }
    cout << NewTreeComp->getStr("NLR") << endl;
    auto SubTre = new Tree<Compl>;
    for (int i=0; i<3;++i){
        Compl com1 = getCompl(i);
        SubTre->insert(com1);
    }
    
    if (NewTreeComp->ContainSub(SubTre)){
    cout<< "содержит"<<endl;
    }
    else{
        cout<<"не содержит"<<endl;
    }
    
    cout<<NewTreeComp->reduce(plus1);
    
    return 0;
    
}
