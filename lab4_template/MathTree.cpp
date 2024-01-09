#include "MathTree.h"

#include <cmath>
#include <sstream>
#include <utility>

void mt_test() {
    MathTree<int> tree;
    MathTree<int> tree2;
    tree.enter("* 7 8");
    tree2.enter("+ + sin 3 4 8");
    MathTree<int> tree3 = tree + std::move(tree2);
//    std::cout<<tree3.root<<std::endl;
    tree = tree3;
    std::cout << tree.root << " " << &tree3;

}

template<typename T>
std::string MathTree<T>::sGetKnownType() {
    return "Unknown";
}

template<>
std::string MathTree<int>::sGetKnownType() {
    return "int";
}

template<>
std::string MathTree<float>::sGetKnownType() {
    return "float";
}

template<>
std::string MathTree<std::string>::sGetKnownType() {
    return "string";
}

template<typename T>
typename MathTree<T>::Node *MathTree<T>::copyTree(const MathTree::Node *root) {
    if (root == nullptr) return nullptr;

    Node *newNode = new Node(*root);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

template<typename T>
MathTree<T> MathTree<T>::operator+(const MathTree<T> &&other) {
    Node *newRoot = new Node(PLUS);
    newRoot->left = copyTree(root);
    newRoot->right = copyTree(other.root);
    MathTree<T> tree;
//    std::cout<<tree.root <<" HI "<<newRoot<<std::endl;
    tree.root = newRoot;
//    std::cout<<tree.root<<std::endl;
    newRoot = nullptr;
    return std::move(tree);
}

template<typename T>
MathTree<T> &MathTree<T>::operator=(MathTree<T> &&other) noexcept {
    if (this != &other) {
        delete root;
        vars.clear();

        root = other.root;
        vars = other.vars;

        other.root = nullptr;
    }
    return *this;
}

template<typename T>
MathTree<T> &MathTree<T>::operator=(const MathTree<T> &other) noexcept {
    if (this != &other) {
        delete root;
        vars.clear();
        root = copyTree(other.root);
        for (int i = 0; i < other.vars.size(); ++i) {
            vars.push_back(new Node(*other.vars.at(i)));
        }
    }
    return *this;
}

template<typename T>
void MathTree<T>::printResult()  {
    precompile("comp");
}

template<typename T>
void MathTree<T>::print() {
    std::cout << getFormula(root) + "\n";
}
template<typename T>
void MathTree<T>::enter(std::string string) {
    create(string);
}

template<>
bool MathTree<float>::isStringANumber(std::string string) {
    for (int i = 0; i < string.size(); ++i) {
        if (string.at(i) > '9' || string.at(i) < '0' && string.at(i) != '.')
            return false;
    }
    return true;
}

template<>
bool MathTree<int>::isStringANumber(std::string string) {
    for (int i = 0; i < string.size(); ++i) {
        if (string.at(i) > '9' || string.at(i) < '0')
            return false;
    }
    return true;
}

template<typename T>
void MathTree<T>::printVars() {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return;
    }

    if (vars.empty()) {
        std::cout << "Tree dont have variables.\n";
        return;
    }

    std::cout << "Variables: ";
    for (int i = 0; i < vars.size(); ++i) {
        std::cout << vars.at(i)->name << " ";
    }
    std::cout << std::endl;
}

template<>
float MathTree<float>::compile(Node *root, std::vector<float> *values) {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return 0;
    }

    if (root->op != NIL) {
        switch (root->op) {
            case PLUS:
                return compile(root->left, values) + compile(root->right, values);
            case MINUS:
                return compile(root->left, values) - compile(root->right, values);
            case DIV: {
                float num = compile(root->right, values);
                if (num == 0) {
                    std::cout << "Division by 0 is not allowed!\n";
                    num = 1;
                }
                return compile(root->left, values) / num;
            }
            case MULT:
                return compile(root->left, values) * compile(root->right, values);
            case SIN:
                return std::sin(compile(root->left, values));
            case COS:
                return std::cos(compile(root->left, values));
            case NIL:
                break;
        }
    } else if (root->variable) {
        float currVal = values->front();
        values->erase(values->begin());
        return currVal;
    } else {
        return root->value;
    }
    return 0;
}

template<>
int MathTree<int>::compile(Node *root, std::vector<int> *values) {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return 0;
    }

    if (root->op != NIL) {
        switch (root->op) {
            case PLUS:
                return compile(root->left, values) + compile(root->right, values);
            case MINUS:
                return compile(root->left, values) - compile(root->right, values);
            case DIV: {
                float num = compile(root->right, values);
                if (num == 0) {
                    std::cout << "Division by 0 is not allowed!\n";
                    num = 1;
                }
                return compile(root->left, values) / num;
            }
            case MULT:
                return compile(root->left, values) * compile(root->right, values);
            case SIN:
                return std::sin(compile(root->left, values));
            case COS:
                return std::cos(compile(root->left, values));
            case NIL:
                break;
        }
    } else if (root->variable) {
        int currVal = values->front();
        values->erase(values->begin());
        return currVal;
    } else {
        return root->value;
    }
    return 0;
}

template<>
std::string MathTree<std::string>::compile(Node *root, std::vector<std::string> *values) {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return "";
    }

    if (root->op != NIL) {
        switch (root->op) {
            case PLUS: {
                return compile(root->left, values) + compile(root->right, values);
            }
            case MINUS: {
                std::string leftstr = compile(root->left, values);
                std::string rightstr = compile(root->right, values);

                for (int i = leftstr.length() - rightstr.length(); i >= 0; --i) {
                    if (leftstr.substr(i, rightstr.length()) == rightstr) {
                        leftstr.erase(i, rightstr.length());
                        i = -1;
                    }
                }
                return leftstr;
            }
            case DIV: {
                std::string leftstr = compile(root->left, values);
                std::string rightstr = compile(root->right, values);

                for (int i = leftstr.length() - rightstr.length(); i >= 0 ; --i) {
                    if (leftstr.substr(i, rightstr.length()) == rightstr) {
                        leftstr.erase(i, rightstr.length());
                    }
                }
                return leftstr;
            }
            case MULT: {
                std::string leftstr = compile(root->left, values);
                std::string rightstr = compile(root->right, values);

                for (int i = 0; i < leftstr.length(); ++i) {
                    if (leftstr.at(i) == rightstr.at(0)) {
                        leftstr.insert(i + 1, rightstr.substr(1, rightstr.length() - 1));
                        i += rightstr.length() - 1;
                    }
                }
                return leftstr;
            }
            case NIL:
                break;
        }
    } else
        return root->value;
    return "";
}

template<typename T>
void MathTree<T>::join(std::string formula) {
    printVars();

    if (empty() || vars.empty())
        return;

    std::cout << "Choose one of the variables to replace (1-" << vars.size() << ")\n";

    int option;
    std::cin >> option;

    if (option > vars.size() || option < 1) {
        std::cout << "Incorrect number\n";
        return;
    }

    std::vector<std::string> elements = splitString(std::move(formula));
    if (elements.empty()) {
        std::cout << "Formula wasn't provided\n";
        return;
    }

    delete vars.at(option - 1);
    *vars.at(option - 1) = *createHelper(&elements);
    vars.erase(vars.begin() + option - 1);

    std::cout << "New tree: " + getFormula(root);
    std::cout << std::endl;
}

template<typename T>
std::string MathTree<T>::getFormula(Node *root) {
    if (root == nullptr) {
        return "";
    }

    std::string formula;
    if (root->op != NIL) {
        switch (root->op) {
            case PLUS:
                formula+= "+ ";
                break;
            case MINUS:
                formula+= "- ";
                break;
            case DIV:
                formula+= "/ ";
                break;
            case MULT:
                formula+= "* ";
                break;
            case SIN:
                formula+= "sin ";
                break;
            case COS:
                formula+= "cos ";
                break;
            case NIL:
                break;
        }
    } else if (root->variable) {
        formula+= root->name + " ";
    } else {
        formula+= std::to_string(root->value) + " ";
    }
    if (root->left != nullptr)
        formula+= getFormula(root->left);
    if (root->right != nullptr)
        formula+= getFormula(root->right);
    return formula;
}

template<typename T>
void MathTree<T>::create(std::string formula) {
    if (!empty()) {
        std::cout << "Delete current tree before creating new.\n";
        return;
    }

    std::vector<std::string> elements = splitString(std::move(formula));
    if (elements.empty()) {
        std::cout << "Formula wasn't provided\n";
        return;
    }

    root = createHelper(&elements);

    std::cout << "Created tree: ";
    std::cout << getFormula(root);
    std::cout << std::endl;

    if (!elements.empty()) {
        std::cout << "Warning! Redundant elements was skipped: ";
        for (const auto &element: elements) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

template<>
typename MathTree<float>::Node *MathTree<float>::createHelper(std::vector<std::string> *elements) {
    std::string current = elements->front();
    elements->erase(elements->begin());
    Node *node;
    if (current == "+" || current == "-" || current == "*" || current == "/" || current == "sin" || current == "cos") {
        if (current == "+") node = new Node(Operations(PLUS));
        if (current == "-") node = new Node(Operations(MINUS));
        if (current == "*") node = new Node(Operations(MULT));
        if (current == "/") node = new Node(Operations(DIV));
        if (current == "sin") node = new Node(Operations(SIN));
        if (current == "cos") node = new Node(Operations(COS));

        if (elements->empty()) {
            elements->emplace_back("1");
            std::cout << "Missing variable replaced with 1\n";
        }
        node->left = createHelper(elements);

        if (current == "+" || current == "-" || current == "*" || current == "/") {
            if (elements->empty()) {
                elements->emplace_back("1");
                std::cout << "Missing variable replaced with 1\n";
            }
            node->right = createHelper(elements);
        }

    } else if (isStringANumber(current)) {
        node = new Node(std::stof(current));
    } else {
        node = findNodeInVectorByName(&vars, current);
        if (node == nullptr) {
            node = new Node(current, true);
            vars.push_back(node);
        }
    }
    return node;
}

template<>
typename MathTree<int>::Node *MathTree<int>::createHelper(std::vector<std::string> *elements) {
    std::string current = elements->front();
    elements->erase(elements->begin());
    Node *node;
    if (current == "+" || current == "-" || current == "*" || current == "/" || current == "sin" || current == "cos") {
        if (current == "+") node = new Node(Operations(PLUS));
        if (current == "-") node = new Node(Operations(MINUS));
        if (current == "*") node = new Node(Operations(MULT));
        if (current == "/") node = new Node(Operations(DIV));
        if (current == "sin") node = new Node(Operations(SIN));
        if (current == "cos") node = new Node(Operations(COS));

        if (elements->empty()) {
            elements->emplace_back("1");
            std::cout << "Missing variable replaced with 1\n";
        }
        node->left = createHelper(elements);

        if (current == "+" || current == "-" || current == "*" || current == "/") {
            if (elements->empty()) {
                elements->emplace_back("1");
                std::cout << "Missing variable replaced with 1\n";
            }
            node->right = createHelper(elements);
        }

    } else if (isStringANumber(current)) {
        node = new Node(std::stoi(current));
    } else {
        node = findNodeInVectorByName(&vars, current);
        if (node == nullptr) {
            node = new Node(current, true);
            vars.push_back(node);
        }
    }
    return node;
}

template<>
typename MathTree<std::string>::Node *MathTree<std::string>::createHelper(std::vector<std::string> *elements) {
    std::string current = elements->front();
    elements->erase(elements->begin());
    Node *node;
    if (current == "+" || current == "-" || current == "*" || current == "/") {
        if (current == "+") node = new Node(Operations(PLUS));
        if (current == "-") node = new Node(Operations(MINUS));
        if (current == "*") node = new Node(Operations(MULT));
        if (current == "/") node = new Node(Operations(DIV));


        if (elements->empty()) {
            elements->emplace_back("a");
            std::cout << "Missing variable replaced with \"a\"\n";
        }
        node->left = createHelper(elements);

        if (current == "+" || current == "-" || current == "*" || current == "/") {
            if (elements->empty()) {
                elements->emplace_back("a");
                std::cout << "Missing variable replaced with \"a\"\n";
            }
            node->right = createHelper(elements);
        }

    } else {
        node = new Node(current);
    }
    return node;
}

template<typename T>
typename MathTree<T>::Node *MathTree<T>::findNodeInVectorByName(std::vector<Node *> *vector, std::string string) {
    for (int i = 0; i < vector->size(); ++i) {
        if (vector->at(i)->name == string)
            return vector->at(i);
    }
    return nullptr;
}

template<>
void MathTree<float>::precompile(std::string str) {
    std::vector<std::string> elements = splitString(str.substr(4));
    std::vector<float> values;

    int errors = 0;
    if (elements.size() < vars.size())
        errors++;
    else {
        for (int i = 0; i < elements.size(); ++i) {
            if (!isStringANumber(elements.at(i))) {
                errors++;
            } else {
                values.push_back(std::stof(elements.at(i)));
            }
        }
    }

    if (errors != 0) {
        std::cout << "Provided incorrect numbers\n";
    } else {
        if (!empty())
            std::cout << "Result: " << compile(root, &values) << std::endl;
        else
            std::cout << "Tree is empty\n";
    }
}

template<>
void MathTree<int>::precompile(std::string str) {
    std::vector<std::string> elements = splitString(str.substr(4));
    std::vector<int> values;

    int errors = 0;
    if (elements.size() < vars.size())
        errors++;
    else {
        for (int i = 0; i < elements.size(); ++i) {
            if (!isStringANumber(elements.at(i))) {
                errors++;
            } else {
                values.push_back(std::stoi(elements.at(i)));
            }
        }
    }

    if (errors != 0) {
        std::cout << "Provided incorrect numbers\n";
    } else {
        if (!empty())
            std::cout << "Result: " << compile(root, &values) << std::endl;
        else
            std::cout << "Tree is empty\n";
    }
}

template<>
void MathTree<std::string>::precompile(std::string str) {
    if (!empty())
        std::cout << "Result: " << compile(root, nullptr) << std::endl;
    else
        std::cout << "Tree is empty\n";
}

template<typename T>
void MathTree<T>::menu() {
    bool exit = false;

    while (!exit) {
        std::string str;
        std::getline(std::cin, str);
        std::string command = str.substr(0, str.find(' '));
        if (command == "enter") {
            create(str.substr(5));
        } else if (command == "vars") {
            printVars();
        } else if (command == "getFormula") {
            std::cout << getFormula(root) << std::endl;
        } else if (command == "comp") {
            precompile(str);
        } else if (command == "join") {
            join(str.substr(4));
        } else if (command == "clear") {
            clear();
        } else if (command == "exit") {
            exit = true;
            delete root;
            std::cout << "Stopping program...\n";
        } else if (command == "help") {
            std::cout
                    << "Commands: \nenter <formula> \nvars \ngetFormula \ncomp <var0> <var1> ... <varN> \njoin <formula> \nclear \nexit\nhelp\n";
        }
    }
}

template<typename T>
void MathTree<T>::clear() {
    if (empty()) {
        std::cout << "Tree is empty.\n";
        return;
    }

    delete root;
    root = nullptr;
    vars.clear();
    std::cout << "Tree cleared.\n";
}

template<typename T>
std::vector<std::string> MathTree<T>::splitString(std::string formula) {
    std::string token;
    std::stringstream ss(formula);
    std::vector<std::string> v;
    while (getline(ss, token, ' ')) {
        if (!token.empty())
            v.push_back(token);
    }
    return v;
}

template<typename T>
bool MathTree<T>::empty() {
    return root == nullptr;
}