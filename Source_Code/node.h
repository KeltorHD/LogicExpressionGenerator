#pragma once
/*
Заголовочный файл с основными перечислениями и классами в проекте
Перечисления: переменная, лог. константа, операции, тип узла, поле узла
Классы: узел бинарного дерева, узел n-мерного дерева
*/

#include <iostream>
#include <QTextStream>
#include <QStringList>
#include <algorithm>
#include <vector>

#define OPERATION_COUNT 7 /*без отрицания*/
#define VARIABLE_COUNT 10 /*количество переменных*/
#define VARIABLE_TYPE_COUNT 3 /*количество типов вида переменных*/
#define OPERATION_TYPE_COUNT 2 /*количество типов вида операций*/

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

enum class varType /*тип того, как выглядят переменные*/
{
    XYZ = 0, /*переменные называются X, Y, Z, Y..*/
    X1X2X3,  /*переменные называются X1, X2, X3, X4..*/
    ABC      /*переменные называются A, B, C, D..*/
};

enum class opType /*тип того, как выглядят операции*/
{
    MATH = 0, /* операции имеют вид +, *, (+) */
    LOG       /* операции имеют вид крышечек */
};

enum class langType /*тип локализации*/
{
    EN = 0,
    RU,
    DE
};

enum class themeType /*тип темы приложения*/
{
    WHITE = 0,
    BLACK
};

enum class screen /*тип экрана*/
{
    MENU = 0,
    SETTINGS,
    GENERATE,
    MANIPULATION
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

bool operator==(const fieldNode& f1, const fieldNode& f2);

/*отображение переменной и операции в зависимости от настроек*/
QTextStream& displayVarTextStream(QTextStream& os, const variable& v, const QStringList* listVar, int var);
QTextStream& displayOperTextStream(QTextStream& os, const operation& op, const QStringList* listOper, int oper);

class Node
{
private:
    fieldNode field;    /*поле, что хранится в узле*/
    const Node* left;         /*левый потомок*/
    const Node* right;        /*правый потомок*/

public:
    Node() { this->left = nullptr; this->right = nullptr; };
    Node(fieldNode field);
    Node(fieldNode field, const Node* left, const Node* right);
    ~Node();

    /*перегруженные операции*/
    friend std::ostream& operator<<(std::ostream& os, const Node* n); /*отображение текущей операции/переменной/константы в узле*/

    /*методы*/
    void display(int n = 0, std::ostream& os = std::cout) const;   /*вывод дерева на экран*/
    void qStringDisplay(int n, QTextStream& os, const QStringList* varList, int var, const QStringList* operList, int oper) const;
    //void tableDisplay(int n = 0) const;   /*вывод дерева для таблицы истинности*/
    friend bool compareTree(const Node* n1, const Node* n2);
    friend void deleteNode(const Node* n); /*удаление дерева, применять для вершины, удаляется и вершина!*/
    friend Node* copy(const Node* n);      /*копирование узла и всех его потомков и выделение памяти*/

    /*get AND set*/
    const fieldNode& getField() const;
    const Node* getLeft() const;
    const Node* getRight() const;
};

class OrdinaryTree   /*класс n-мерного дерева*/
{
private:
    fieldNode field; /*то, что зранится в узле*/
    std::vector<const OrdinaryTree*> child; /*вектор указателей на потомков*/

    OrdinaryTree(const OrdinaryTree&); /*конструктор копирования*/
    OrdinaryTree& operator=(const OrdinaryTree&) { return *this;}; /*оператор присваивания*/

    /*методы*/
    void addChild(OrdinaryTree* ord); /*добавление потомка*/
    void addField(const fieldNode& field);

public:
    OrdinaryTree();
    OrdinaryTree(const fieldNode& field);
    OrdinaryTree(const fieldNode& field, const std::vector<const OrdinaryTree*>& child);

    /*методы*/

    /*дружественные функции*/
    friend bool equalOrdinaryTree(const OrdinaryTree* f, const OrdinaryTree* s);
    /*сравнение двух деревьев, true - если равны, false - не равны*/
    friend void deleteOrdinaryTree(const OrdinaryTree* n);
    /*удаление дерева, применять для вершины, удаляется и вершина!*/
    friend bool compareOrdinaryTree(const OrdinaryTree* f, const OrdinaryTree* s);
    /*сравнение узлов, сравнение происходит по положению перечислениях!*/
    friend void createOrdinaryTree(OrdinaryTree* ord, const Node* n, const Node* previous, bool isFirst);
    /*Создание дерева из вершины бинарного дерева, должна быть выделена память на prd, выделяется память, необходимо ее очистить!*/
};
