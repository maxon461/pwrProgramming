#ifndef TEPLABY_MATHTREE_H
#define TEPLABY_MATHTREE_H

#include <iostream>
#include <vector>

template<typename T>
class MathTree {
private:
    enum Operations {
        PLUS, MINUS, DIV, MULT, SIN, COS, NIL
    };

    class Node {
    public:
        Node *left = nullptr;
        Node *right = nullptr;
        T value;
        std::string name;
        bool variable = false;
        Operations op = NIL;

        Node() = default;

        Node(const Node &other) : value(other.value), name(other.name), variable(other.variable), op(other.op) {
            if (other.left)
                left = new Node(*other.left);
            if (other.right)
                right = new Node(*other.right);
        }

        explicit Node(T val) {
            value = val;
        }

        explicit Node(std::string name, bool isVar) {
            this->name = std::move(name);
            variable = isVar;
        }

        explicit Node(Operations op) {
            this->op = op;
        }

        ~Node() {
            if (left)
                delete left;
            if (right)
                delete right;
        }
    };

    std::vector<Node *> vars;

    T compile(Node *root, std::vector<T> *values);

    std::string getFormula(Node *root);

    void create(std::string formula);

    std::vector<std::string> splitString(std::string formula);

    Node *createHelper(std::vector<std::string> *elements);

    bool isStringANumber(std::string string);

    Node *findNodeInVectorByName(std::vector<Node *> *vector, std::string string);

    void precompile(std::string str);

    static std::string sGetKnownType();

    Node *copyTree(const Node *root);

public:
    void menu();

    void printVars();

    void clear();

    bool empty();

    void join(std::string formula);

    void enter(std::string string);

    void print();

    void printResult();

    MathTree() = default;

    MathTree(const MathTree<T> &other) {
        std::cout << "\nTREE COPY\n";

        if (other.root)
            root = copyTree(other.root);

        for (int i = 0; i < other.vars.size(); ++i) {
            vars.push_back(new Node(*other.vars.at(i)));
        }
    }

    MathTree(MathTree<T> &&other) noexcept {
        root = other.root;
        vars = other.vars;
        other.root = nullptr;
    }

    ~MathTree() {
        delete root;
        vars.clear();
    }


    MathTree &operator=(const MathTree<T> &other) noexcept;

    MathTree &operator=(MathTree<T> &&other) noexcept;

    MathTree operator+(const MathTree<T> &&other);


    Node *root = nullptr;
};

void mt_test();

#endif //TEPLABY_MATHTREE_H