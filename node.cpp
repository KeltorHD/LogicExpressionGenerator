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

Node::Node(fieldNode field, Node* left, Node* right)
{
        this->field = field;
        this->left = left;
        this->right = right;
}

Node::~Node()
{
}

/*void Node::display(int n, std::ostream& os) const
{
        if (this->field.type != typeNode::VAR && this->field.type != typeNode::LOG_CONST
                && n != 0)
                os << "(";
        if (this->left)
        {
                this->left->display(1, os);
        }
        if (this->field.type == typeNode::OPERATION)
        {
                os << this->field.oper;
        }
        if (this->right)
        {
                this->right->display(1, os);
        }
        if (!this->left && !this->right)
        {
                if (this->field.type == typeNode::VAR)
                        os << this->field.var;
                else if (this->field.type == typeNode::LOG_CONST)
                        os << this->field.lConst;
        }
        if (this->field.type != typeNode::VAR && this->field.type != typeNode::LOG_CONST
                && n != 0)
            os << ")";
}*/

void Node::qStringDisplay(int n, QTextStream &os) const
{
    if (this->field.type != typeNode::VAR && this->field.type != typeNode::LOG_CONST
            && n != 0)
            os << "(";
    if (this->left)
    {
            this->left->qStringDisplay(1, os);
    }
    if (this->field.type == typeNode::OPERATION)
    {
            os << this->field.oper;
    }
    if (this->right)
    {
            this->right->qStringDisplay(1, os);
    }
    if (!this->left && !this->right)
    {
            if (this->field.type == typeNode::VAR)
                    os << this->field.var;
            else if (this->field.type == typeNode::LOG_CONST)
                    os << this->field.lConst;
    }
    if (this->field.type != typeNode::VAR && this->field.type != typeNode::LOG_CONST
            && n != 0)
        os << ")";
}

const fieldNode& Node::getField() const
{
        return this->field;
}

Node* Node::getLeft()
{
        return this->left;
}

Node* Node::getRight()
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
        }
        return false;
}

/*std::ostream& operator<<(std::ostream& os, const Node* n)
{
        os << n->field.type << ": ";
        switch (n->field.type)
        {
        case typeNode::VAR:
                os << n->field.var;
                break;
        case typeNode::LOG_CONST:
                os << n->field.lConst;
                break;
        case typeNode::OPERATION:
                os << n->field.oper;
                break;
        default:
                break;
        }
        return os;
}*/

void deleteNode(Node* n)
{
        if (n != nullptr)
        {
                deleteNode(n->left);
                deleteNode(n->right);
                delete n;
        }
}

Node* copy(Node* n)
{
        if (n == nullptr)
                return nullptr;

        Node* newNode = new Node(n->field);
        newNode->left = copy(n->left);
        newNode->right = copy(n->right);
        return newNode;
}
