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
        T value ;
        char name;
        bool variable = false;
        Operations op = NIL;
        explicit Node(char name)
        {
            this->name = (name);
            variable = true;
        }
        explicit Node(float val)
        {
            value = val;
        }
        explicit Node(std::string val)
        {
            value = val;
        }
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
    T compile(Node *root, std::vector<T> *values);
    void join(std::string formula);
    void clear();
    void print(Node *root);
    void create(std::string formula);
    bool empty();

    std::vector<std::string> splitString(std::string formula);
    Node *createHelper(std::vector<std::string> *elements);
    bool isStringANumber(std::string string);
    Node *findNodeInVectorByName(std::vector<Node *> *vector, std::string string);

    std::string removeSubstring(const std::string& str, const std::string& substr);
    std::string multiplyStrings(const std::string& str1, const std::string& str2);
    std::string divideStrings(const std::string& dividend, const std::string& divisor);
public:
    void menuF();
    void menuS();
};

void mt_test();




#endif //LAB4_TEMPLATE_MATHTREE_H