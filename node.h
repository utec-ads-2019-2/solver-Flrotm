
#include <string>
#include <utility>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>


using namespace std;

template <typename T>
class Node {
    T data;
    Node<T> *left;
    Node<T> *right;
    bool isoperator;
    int prioridad;

    template<class>
    friend class Tree;
    explicit Node(T data): data(data), left(nullptr),right(nullptr){
        isoperator = true;
        if (data == "+" or data == "-"){
            prioridad = 1; }
        else if (data == "*" or data=="/"){
            prioridad = 2; }
        else if(data == "^"   ){
            prioridad = 3; }
        else{
            isoperator = false;
            prioridad = 0;
        }
    }
    double Operar(){
        return e2(this);
    }
private:

    bool Ihoja(){
        return (!this->left and !this->right);
    }

    double e(Node* root, vector<double> &resultados){

        if (!root) {
            resultados.push_back(0);
            return 0;
        }

        if (root->Ihoja()) {
            resultados.push_back(stod(root->data));
            return stod(root->data);
        }
        double izq = e(root->left,resultados);
        double der = e(root->right,resultados);

        if (root->data=="+"){
            resultados.push_back(izq+der);
            return (izq+der);
        }
        else if (root->data=="-"){
            resultados.push_back(izq-der);
            return (izq-der);
        }

        else if (root->data=="*"){
            resultados.push_back(izq*der);
            return (izq*der);
        }

        else if (root->data=="/"){
            resultados.push_back(izq/der);
            return (izq/der);
        }
        else{
            resultados.push_back(pow(izq,der));
            return pow(izq,der);
        }
    }

    double e2(Node* root){
        vector<double> resultados1;
        e(root, resultados1);
        return resultados1.back();
    }


};
