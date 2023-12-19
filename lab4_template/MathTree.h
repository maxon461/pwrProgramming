//
// Created by Maksym Selishchev on 18/12/2023.
//

#ifndef LAB4_TEMPLATE_MATHTREE_H
#define LAB4_TEMPLATE_MATHTREE_H



#include <iostream>
#include <utility>
#include <vector>

template <typename  T> class MathTree
{
private:
    enum Operations
    {
        PLUS,
        MINUS,
        DIV,
        MULT,
        SIN,
        COS,
        NIL
    };
    class Node
    {
    public:
        Node *left = nullptr;
        Node *right = nullptr;
        T value = 0;
        std::string name;
        bool variable = false;
        Operations op = NIL;
        explicit Node(std::string name)
        {
            this->name = std::move(name);
            variable = true;
        }
        explicit Node(float val)
        {
            value = val;
        }
//        explicit Node(std::string val)
//        {
//            value = val;
//        }
        explicit Node(Operations op)
        {
            this->op = op;
        }
        ~Node()
        {
            delete left;
            delete right;
        }
    };
    Node *root = nullptr;
    std::vector<Node *> vars;

    void printVars();
    float compile(Node *root, std::vector<float> *values);
    void join(std::string formula);
    void clear();
    void print(Node *root);
    void create(std::string formula);
    bool empty();

    std::vector<std::string> splitString(std::string formula);
    Node *createHelper(std::vector<std::string> *elements);
    bool isStringANumber(std::string string);
    Node *findNodeInVectorByName(std::vector<Node *> *vector, std::string string);

public:
    void menu();
};

void mt_test();




#endif //LAB4_TEMPLATE_MATHTREE_H
