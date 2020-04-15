#pragma once

#include <QTextStream>
#include <iostream>

#define OPERATION_COUNT 7 /*без отрицания*/
#define VARIABLE_COUNT 10


enum class variable  /*переменные, используещиеся в генераторе*/
{
    X = 0, Y, Z, T, K, L, M, N, P, S
};


enum class log_const /*логические константы*/
{
    FALSE = 0, TRUE
};


enum class operation /*логические операции*/
{
    AND, OR, IMPLICATION, XOR, EQUIVALENCE, SHEFFER_STROKE, PEIRCES_ARROW, NOT
};


enum class typeNode /*тип того, что хранится в узле*/
{
    VAR = 0,   /*обычная переменная, X, Y, Z, T*/
    LOG_CONST, /*константа, 1, 0*/
    OPERATION  /*операция, +, *, -> и тд*/
};

struct fieldNode    /*поле узла*/
{
    typeNode type;
    union
    {
        variable var;
        log_const lConst;
        operation oper;
    };

    /*инициализации*/
    fieldNode(typeNode _type, variable _var) { type = _type; var = _var; }
    fieldNode(typeNode _type, log_const _lConst) { type = _type; lConst = _lConst; }
    fieldNode(typeNode _type, operation _oper) { type = _type; oper = _oper; }
    fieldNode() { type = typeNode::VAR, var = variable::X; }
};

/*
перегрузки операций
*/
QTextStream& operator<<(QTextStream& os, const variable& v);

QTextStream& operator<<(QTextStream& os, const log_const& l);

QTextStream& operator<<(QTextStream& os, const log_const& l);

QTextStream& operator<<(QTextStream& os, const operation& op);

QTextStream& operator<<(QTextStream& os, const typeNode& tn);

/*
перегрузки операций
*/
std::ostream& operator<<(std::ostream& os, const variable& v);

std::ostream& operator<<(std::ostream& os, const log_const& l);

std::ostream& operator<<(std::ostream& os, const operation& op);

std::ostream& operator<<(std::ostream& os, const typeNode& tn);

/*
Вывод операции с подсказкой*/
void displayOperationHint(const operation& op);

bool operator==(const fieldNode& f1, const fieldNode& f2);

class Node
{
private:
    fieldNode field;    /*поле, что хранится в узле*/
    Node* left;         /*левый потомок*/
    Node* right;        /*правый потомок*/

public:
    Node() { this->left = nullptr; this->right = nullptr; };
    Node(fieldNode field);
    Node(fieldNode field, Node* left, Node* right);
    ~Node();

    /*перегруженные операции*/
    friend std::ostream& operator<<(std::ostream& os, const Node* n); /*отображение текущей операции/переменной/константы в узле*/

    /*методы*/
    void display(int n = 0, std::ostream& os = std::cout) const;   /*вывод дерева на экран*/
    void qStringDisplay(int n, QTextStream& os) const;
    //void tableDisplay(int n = 0) const;   /*вывод дерева для таблицы истинности*/
    friend void deleteNode(Node* n); /*удаление дерева, применять для вершины, удаляется и вершина!*/
    friend Node* copy(Node* n);      /*копирование узла и всех его потомков и выделение памяти*/

    /*get AND set*/
    const fieldNode& getField() const;
    Node* getLeft();
    Node* getRight();
};
