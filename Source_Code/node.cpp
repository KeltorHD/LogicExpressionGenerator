#include "node.h"

QTextStream& operator<<(QTextStream& os, const variable& v)
{
        switch (v)
        {
        case variable::X:
                os << "X";
                break;
        case variable::Y:
                os << "Y";
                break;
        case variable::Z:
                os << "Z";
                break;
        case variable::T:
                os << "T";
                break;
        case variable::K:
                os << "K";
                break;
        case variable::L:
                os << "L";
                break;
        case variable::M:
                os << "M";
                break;
        case variable::N:
                os << "N";
                break;
        case variable::P:
                os << "P";
                break;
        case variable::S:
                os << "S";
                break;
        default:
                break;
        }
        return os;
}

QTextStream& displayTextStream(QTextStream& os, const variable& v, const QStringList* listVar, int var)
{
    switch (v)
    {
    case variable::X:
            os << listVar[var][0];
            break;
    case variable::Y:
            os << listVar[var][1];
            break;
    case variable::Z:
            os << listVar[var][2];
            break;
    case variable::T:
            os << listVar[var][3];
            break;
    case variable::K:
            os << listVar[var][4];
            break;
    case variable::L:
            os << listVar[var][5];
            break;
    case variable::M:
            os << listVar[var][6];
            break;
    case variable::N:
            os << listVar[var][7];
            break;
    case variable::P:
            os << listVar[var][8];
            break;
    case variable::S:
            os << listVar[var][9];
            break;
    default:
            break;
    }
    return os;
}

QTextStream& operator<<(QTextStream& os, const log_const& l)
{
        switch (l)
        {
        case log_const::FALSE:
                os << "0";
                break;
        case log_const::TRUE:
                os << "1";
                break;
        default:
                break;
        }
        return os;
}

QTextStream& operator<<(QTextStream& os, const operation& op)
{
        switch (op)
        {
        case operation::AND:
                os << "*";
                break;
        case operation::OR:
                os << "+";
                break;
        case operation::NOT:
                os << "~";
                break;
        case operation::IMPLICATION:
                os << "->";
                break;
        case operation::XOR:
                os << "(+)";
                break;
        case operation::EQUIVALENCE:
                os << "<=>";
                break;
        case operation::SHEFFER_STROKE: /*изменить*/
                os << "|";
                break;
        case operation::PEIRCES_ARROW:
                os << "||";
                break;
        default:
                break;
        }
        return os;
}

QTextStream& operator<<(QTextStream& os, const typeNode& tn)
{
        switch (tn)
        {
        case typeNode::VAR:
                os << "Переменная";
                break;
        case typeNode::LOG_CONST:
                os << "Логическая константа";
                break;
        case typeNode::OPERATION:
                os << "Операция";
                break;
        default:
                break;
        }
        return os;
}

void displayOperationHint(const operation& op)
{
        switch (op)
        {
        case operation::AND:
                std::cout << "*" << "    (Логическое И)";
                break;
        case operation::OR:
                std::cout << "+" << "    (Логическое ИЛИ)";
                break;
        case operation::NOT:
                std::cout << "~" << "    (Отрицание)";
                break;
        case operation::IMPLICATION:
                std::cout << "->" << "   (Следование, импликация)";
                break;
        case operation::XOR:
                std::cout << "(+)" << "  (Сложение по модулю 2, исключающее или)";
                break;
        case operation::EQUIVALENCE:
                std::cout << "<=>" << "  (Эквиваленция)";
                break;
        case operation::SHEFFER_STROKE: /*изменить*/
                std::cout << "|" << "    (Штрих Шеффера)";
                break;
        case operation::PEIRCES_ARROW:
                std::cout << "||" << "   (Стрелка Пирса)";
                break;
        default:
                break;
        }
}

std::ostream& operator<<(std::ostream& os, const variable& v)
{
    switch (v)
    {
    case variable::X:
        os << "X";
        break;
    case variable::Y:
        os << "Y";
        break;
    case variable::Z:
        os << "Z";
        break;
    case variable::T:
        os << "T";
        break;
    case variable::K:
        os << "K";
        break;
    case variable::L:
        os << "L";
        break;
    case variable::M:
        os << "M";
        break;
    case variable::N:
        os << "N";
        break;
    case variable::P:
        os << "P";
        break;
    case variable::S:
        os << "S";
        break;
    default:
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const log_const& l)
{
    switch (l)
    {
    case log_const::FALSE:
        os << "0";
        break;
    case log_const::TRUE:
        os << "1";
        break;
    default:
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const operation& op)
{
    switch (op)
    {
    case operation::AND:
        os << "*";
        break;
    case operation::OR:
        os << "+";
        break;
    case operation::NOT:
        os << "~";
        break;
    case operation::IMPLICATION:
        os << "->";
        break;
    case operation::XOR:
        os << "(+)";
        break;
    case operation::EQUIVALENCE:
        os << "<=>";
        break;
    case operation::SHEFFER_STROKE: /*изменить*/
        os << "|";
        break;
    case operation::PEIRCES_ARROW:
        os << "||";
        break;
    default:
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const typeNode& tn)
{
    switch (tn)
    {
    case typeNode::VAR:
        os << "Переменная";
        break;
    case typeNode::LOG_CONST:
        os << "Логическая константа";
        break;
    case typeNode::OPERATION:
        os << "Операция";
        break;
    default:
        break;
    }
    return os;
}

bool operator==(const fieldNode& f1, const fieldNode& f2)
{
        if (f1.type == f1.type)
        {
                if (f1.type == typeNode::VAR && f1.var == f2.var)
                        return true;
                else if (f1.type == typeNode::LOG_CONST && f1.lConst == f2.lConst)
                        return true;
                else if (f1.type == typeNode::OPERATION && f1.oper == f2.oper)
                        return true;
                return false;
        }

        return false;
}

Node::Node(fieldNode field)
{
        this->field = field;
        this->left = nullptr;
        this->right = nullptr;
}

Node::Node(fieldNode field, const Node* left, const Node* right)
{
        this->field = field;
        this->left = left;
        this->right = right;
}

Node::~Node()
{
}

void Node::qStringDisplay(int n, QTextStream &os, const QStringList* varList, int var) const
{
    if (this->field.type != typeNode::VAR && this->field.type != typeNode::LOG_CONST
            && n != 0)
            os << "(";
    if (this->left)
    {
            this->left->qStringDisplay(1, os, varList, var);
    }
    if (this->field.type == typeNode::OPERATION)
    {
            os << this->field.oper;
    }
    if (this->right)
    {
            this->right->qStringDisplay(1, os, varList, var);
    }
    if (!this->left && !this->right)
    {
            if (this->field.type == typeNode::VAR)
                    displayTextStream(os, this->field.var, varList, var);
            else if (this->field.type == typeNode::LOG_CONST)
                    os << this->field.lConst;
    }
    if (this->field.type != typeNode::VAR && this->field.type != typeNode::LOG_CONST
            && n != 0)
        os << ")";
}

bool compareTree(const Node* n1, const Node* n2)
{

    OrdinaryTree* ord1 = new OrdinaryTree();
    createOrdinaryTree(ord1, n1, n1, true);
    OrdinaryTree* ord2 = new OrdinaryTree();
    createOrdinaryTree(ord2, n2, n2, true);

    bool isEqual = equalOrdinaryTree(ord1, ord2);

    deleteOrdinaryTree(ord1);
    deleteOrdinaryTree(ord2);

    return isEqual;
}

const fieldNode& Node::getField() const
{
        return this->field;
}

const Node* Node::getLeft() const
{
        return this->left;
}

const Node* Node::getRight() const
{
        return this->right;
}


bool searchBinaryResult(bool l1, bool l2, operation oper)
{
        switch (oper)
        {
        case operation::AND:
                return l1 & l2;
        case operation::OR:
                return l1 | l2;
        case operation::IMPLICATION:
                return (!l1) | l2;
        case operation::XOR:
                return l1 ^ l2;
        case operation::EQUIVALENCE:
                return (l1 & l2) | (!l1 & !l2);
        case operation::SHEFFER_STROKE:
                return !(l1 & l2);
        case operation::PEIRCES_ARROW:
                return !(l1 | l2);
        case operation::NOT:
            return false;
        }
        return false;
}

void deleteNode(const Node* n)
{
        if (n != nullptr)
        {
                deleteNode(n->left);
                deleteNode(n->right);
                delete n;
        }
}

Node* copy(const Node* n)
{
        if (n == nullptr)
                return nullptr;

        Node* newNode = new Node(n->field);
        newNode->left = copy(n->left);
        newNode->right = copy(n->right);
        return newNode;
}

void OrdinaryTree::addChild(OrdinaryTree* ord)
{
    this->child.push_back(ord);
}

void OrdinaryTree::addField(const fieldNode& field)
{
    this->field = field;
}

OrdinaryTree::OrdinaryTree()
    :field()
{
}

OrdinaryTree::OrdinaryTree(const fieldNode& field)
    : field(field)
{
}

OrdinaryTree::OrdinaryTree(const fieldNode& field, const std::vector<const OrdinaryTree*>& child)
    : field(field), child(child)
{
}

bool equalOrdinaryTree(const OrdinaryTree* f, const OrdinaryTree* s)
{
    if (f->field == s->field) /*если узлы равны*/
    {
        if (f->child.size() == s->child.size()) /*если количество потомков равно*/
        {
            for (size_t i = 0; i < f->child.size(); i++) /*цикл сравнения всех потомков потомков дерева f и s*/
            {
                if (!equalOrdinaryTree(f->child[i], s->child[i])) /*если хоть одна пара не равна, то false*/
                    return false;
            }
            return true;
        }
        else /*если количество потомков не равно*/
        {
            return false;
        }
    }
    else /*если узлы не равны*/
    {
        return false;
    }
}

void deleteOrdinaryTree(const OrdinaryTree* n)
{
    if (n != nullptr)
    {
        for (size_t i = 0; i < n->child.size(); i++)
        {
            deleteOrdinaryTree(n->child[i]);
        }
        delete n;
    }
}

bool compareOrdinaryTree(const OrdinaryTree* f, const OrdinaryTree* s)
{
    if (f->field.type == s->field.type) /*если типы узлов равны*/
    {
        if (f->field.type == typeNode::VAR) /*если тип узла - переменная*/
        {
            return f->field.var < s->field.var;
        }
        else if (f->field.type == typeNode::LOG_CONST) /*если тип узла - логическая константа*/
        {
            return f->field.lConst < s->field.lConst;
        }
        else /*если тип узла - операция*/
        {
            return f->field.oper < s->field.oper;
        }
    }
    else /*если типы узлов не равны*/
    {
        return f->field.type < s->field.type; /*сначала переменные, потом логические константы, потом операции*/
    }
}

void createOrdinaryTree(OrdinaryTree* ord, const Node* n, const Node* previous, bool isFirst)
{
    if (isFirst) /*если вызов первый, то добавить узел в дерево*/
        ord->addField(n->getField());

    if (n->getField().type == typeNode::OPERATION) /*если в текущем узле копируемого дерева - операция*/
    {
        if (n->getField().oper == previous->getField().oper) /*если операции в текущем и прошлом узле копируемого дерева равны*/
        {
            if (n->getField().oper == operation::IMPLICATION) /*если импликация*/
            {
                if (!isFirst) /*если не первый вызов, то создать новый узел, в него добавить 2 потомка*/
                {
                    OrdinaryTree* tmp = new OrdinaryTree(n->getField());
                    createOrdinaryTree(tmp, n->getLeft(), n, false);
                    createOrdinaryTree(tmp, n->getRight(), n, false);
                    ord->addChild(tmp);
                }
                else /*если первый вызов, то добавить в текущий узел 2 потомка*/
                {
                    createOrdinaryTree(ord, n->getLeft(), n, false);
                    createOrdinaryTree(ord, n->getRight(), n, false);
                }
            }
            else if (n->getField().oper == operation::NOT) /*если отрицание*/
            {
                OrdinaryTree* tmp = new OrdinaryTree(n->getField());
                createOrdinaryTree(tmp, n->getRight(), n->getRight(), false); /*операция отрицание имеет только одного потомка - правого*/
                ord->addChild(tmp);
            }
            else /*если не отрицание и не импликация, добавляем в текущий узел левый и правый потомок копируемого дерева*/
            {
                createOrdinaryTree(ord, n->getLeft(), n, false);

                createOrdinaryTree(ord, n->getRight(), n, false);
            }
        }
        else /*если операции в текущем и прошлом узле копируемого дерева не равны*/
        {
            OrdinaryTree* tmp = new OrdinaryTree(n->getField()); /*создаем узел, добавляем в него два(если есть) потомка*/
            if (n->getLeft())
            {
                createOrdinaryTree(tmp, n->getLeft(), n, false); /*где-то тут проблема*/
            }
            if (n->getRight())
            {
                createOrdinaryTree(tmp, n->getRight(), n, false);
            }
            if (tmp->child.size()) /*добавляем созданный узел в потомки текущего дерева*/
            {
                ord->addChild(tmp);
            }
        }
    }
    else /*если тип узла копируемого дерева - переменная или логическая константа*/
    {
        OrdinaryTree* tmp = new OrdinaryTree(n->getField()); /*создаем узел, доавляем в потомки текущему дереву*/
        ord->addChild(tmp);
    }

    /*если тип узла не операция - сортировка не нужна, т.к. потомков у операции нет*/
    if (ord->child.size()) /*сортировка потомков текущего узла*/
    {
        /*если тип узла операция испликация, сортировать не нужно, т.к. порядок операндов в операции важен*/
        if (ord->field.type == typeNode::OPERATION && ord->field.oper != operation::IMPLICATION)
        {
            std::sort(ord->child.begin(), ord->child.end(), compareOrdinaryTree);
        }
    }
}
