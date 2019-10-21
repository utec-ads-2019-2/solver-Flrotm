#include <iostream>
#include "tree.h"

using namespace std;

int main(){
    Tree<string> ex;

    string equation;
    cin >> equation;
    auto resultado=ex.Resolver(equation);

    cout<<"Resultado:"<<resultado<<endl;

}