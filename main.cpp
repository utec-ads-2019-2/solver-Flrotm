#include <iostream>
#include "tree.h"

using namespace std;

int main(){
    Tree<string> ex;

    auto resultado=ex.Resolver("54+7-9");

    cout<<"Resultado:"<<resultado<<endl;

}