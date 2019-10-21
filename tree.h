#include "node.h"
#include <iostream>
#include <vector>
#include <map>
#include<stack>
#include <string>
#include <algorithm>
using namespace std;

template <typename T>
class Tree {
    Node<T> *root;
    stack<Node<T>*> operators;
    vector<Node<T>*> numbers;
    map<string,string> variables;

public:
    Tree() : root(nullptr){};

    double Resolver(const string& expresion){
        cout<<"Experesion:  "<<expresion<<endl;
        posfix(expresion);
        input_variables();
        Gen_tree();
        return root->Operar();
    }
    static bool notoperator(char x){
        return x != '+' and x != '-' and x != '/'
        and x != '*' and x != '^' and x != '(' and x != ')';
    }
    static bool parentesis(const string& x){
        return x == "(" or x == ")" ;
    }

    static string remove_space(string &str){
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }
    void actualizar_stack(){
        if(operators.size() == 1 or operators.top()->data == "(")
            return;

        else if(operators.top()->data == ")"){
            operators.pop();

            if(operators.empty()){
                return;
            }

            while(operators.top()->data != "("){

                if(operators.top()->data != ")"){
                    numbers.push_back(operators.top());
                }

                operators.pop();

                if(operators.empty()){
                    return;
                }
            }
            operators.pop();
        }

        else{
            auto operador=operators.top();
            operators.pop();
            while(operators.top()->prioridad >= operador->prioridad){
                numbers.push_back(operators.top());
                operators.pop();
                if(operators.empty())
                    break;
            }
            operators.push(operador);}
    }



    void input_variables(){
        for(auto i:numbers){
            if(isalpha(i->data[0])){

                auto iterador = variables.find(i->data);

                if(iterador == variables.end()){

                    cout<<"Ingrese el valor de "<<i->data<<": ";
                    cin>>variables[i->data];
                    cout<<endl;
                }
                i->data=variables[i->data];
            }
        }
    }
    void Gen_tree(){
        stack<Node<T>*> stack2;
        for(auto numero : numbers){
            stack2.push(numero);
            if(stack2.top()->isoperator){
                auto temporal = stack2.top();
                stack2.pop();
                temporal->right = stack2.top();
                stack2.pop();
                temporal->left=stack2.top();
                stack2.pop();
                stack2.push(temporal);
            }}
        root=stack2.top(); }



    void fill_in(){
        while(!operators.empty()){
            if(!parentesis(operators.top()->data))
                numbers.push_back(operators.top());
            operators.pop();
        }
    }
    void posfix(string expresion){
        string temporal;
        remove_space(expresion);
        for (char i : expresion) {
            if (notoperator(i)){
                temporal = temporal+i; }
            else {
                auto node = new Node<T>(temporal);
                auto operador = new Node<T>(string(1,i));
                if(!temporal.empty())
                    numbers.push_back(node);
                operators.push(operador);
                actualizar_stack();
                temporal = "";
            }
        }
        if(notoperator(expresion[expresion.length() - 1])){
            numbers.push_back(new Node<T>(temporal));
        }

        fill_in();
    }


    // Falta liberar la memoria (destructor)
};

