#include "tree.h"

#include <cmath>
#include <QtDebug>

template<typename T>
void inputConsole(T& variable)
{
    bool isCinbad = false;
    do
    {
        std::cin >> variable;
        if (std::cin.fail() || std::cin.get() != '\n')
        {
            std::cin.clear();
            while (std::cin.get() != '\n')
                continue;
            std::cout << "\aНеправильный ввод, введите корректное значение: \n(возможные причины: использование , вместо . или ввод дробного числа в целое)" << std::endl;
            isCinbad = true;
        }
        else
        {
            isCinbad = false;
        }
    } while (isCinbad);
}

void generateNode(std::vector<Node*>& his, std::vector<Node*>& head, std::vector<operation>& oper, bool isNot, size_t countNode)
{
    if (his.size() == 2)
    {
        if (head.size() >= countNode)
            return;
        for (auto& i : oper) /*проход по операция, участвующим в генерации*/
        {
            if (head.size() >= countNode)
                return;

            for (size_t k = 0; k < size_t(i == operation::IMPLICATION ? 2 : 1); k++) /*если импликация - цикл проходит 2 раза*/
            {
                if (head.size() >= countNode)
                    return;

                if (k == 1)
                {
                    Node* temporary = his[1];
                    his[1] = his[0];
                    his[0] = temporary;
                }

                if (isNot)
                {
                    for (size_t j = 0; j < 4; j++) /*проход по типам перемнных, которые войдут в новую операцию, могут быть: 00, 01, 10, 11*/
                    {
                        if (head.size() >= countNode)
                            break;

                        switch (j)
                        {
                        case 0:
                            his.push_back(
                                new Node
                                (
                                    fieldNode{ typeNode::OPERATION, i },
                                    his[0],
                                    his[1]
                                ));
                            break;
                        case 1:
                            his[0] = new Node
                            (
                                fieldNode{ typeNode::OPERATION, operation::NOT },
                                nullptr,
                                his[0]
                            );
                            his.push_back(
                                new Node
                                (
                                    fieldNode{ typeNode::OPERATION, i },
                                    his[0],
                                    his[1]
                                ));
                            break;
                        case 2:
                            his[1] = new Node
                            (
                                fieldNode{ typeNode::OPERATION, operation::NOT },
                                nullptr,
                                his[1]
                            );
                            his.push_back(
                                new Node
                                (
                                    fieldNode{ typeNode::OPERATION, i },
                                    his[0],
                                    his[1]
                                ));

                            break;
                        case 3:
                            his[0] = new Node
                            (
                                fieldNode{ typeNode::OPERATION, operation::NOT },
                                nullptr,
                                his[0]
                            );
                            his[1] = new Node
                            (
                                fieldNode{ typeNode::OPERATION, operation::NOT },
                                nullptr,
                                his[1]
                            );
                            his.push_back(
                                new Node
                                (
                                    fieldNode{ typeNode::OPERATION, i },
                                    his[0],
                                    his[1]
                                ));
                            break;
                        default:
                            break;
                        }

                        head.push_back(copy(his[his.size() - 1]));

                        //qDebug() << head.size() << ": ";
                        //head[head.size() - 1]->qStringDisplay();
                        //qDebug() << endl;

                        /*возвращаем массив в исходное состояние*/
                        if (his[0]->getField().type == typeNode::OPERATION
                            && his[0]->getField().oper == operation::NOT)
                        {
                            Node* tmp = his[0]->getRight();
                            delete his[0];
                            his[0] = tmp;
                        }
                        if (his[1]->getField().type == typeNode::OPERATION
                            && his[1]->getField().oper == operation::NOT)
                        {
                            Node* tmp = his[1]->getRight();
                            delete his[1];
                            his[1] = tmp;
                        }
                        delete his[his.size() - 1];
                        his.pop_back();

                    }
                }
                else
                {
                    his.push_back(
                        new Node
                        (
                            fieldNode{ typeNode::OPERATION, i },
                            his[0],
                            his[1]
                        ));
                    head.push_back(copy(his[his.size() - 1]));

                    //std::cout << head.size() << ": ";
                    //head[head.size() - 1]->display();
                   // std::cout << std::endl;

                    delete his[his.size() - 1];
                    his.pop_back();
                }

                if (k == 1)
                {
                    Node* temporary = his[0];
                    his[0] = his[1];
                    his[1] = temporary;
                }
            }
        }
    }
    else
    {
        for (auto& i : oper) /*проход по операция, участвующим в генерации*/
        {
            if (head.size() >= countNode)
                break;
            for (size_t m = 0; m < his.size() - 1; m++) /*рассмотрение всех пар элементов*/
            {
                if (head.size() >= countNode)
                    break;
                for (size_t n = m + 1; n < his.size(); n++)
                {
                    if (head.size() >= countNode)
                        break;
                    for (size_t k = 0; k < size_t(i == operation::IMPLICATION ? 2 : 1); k++) /*если импликация - цикл проходит 2 раза*/
                    {
                        if (head.size() >= countNode)
                            break;

                        if (k == 1)
                        {
                            Node* temporary = his[n];
                            his[n] = his[m];
                            his[m] = temporary;
                        }

                        if (isNot) /*если есть отрицание*/
                        {
                            for (size_t j = 0; j < 4; j++) /*проход по типам перемнных, которые войдут в новую операцию, могут быть: 00, 01, 10, 11*/
                            {
                                if (head.size() >= countNode)
                                    return;

                                switch (j)
                                {
                                case 0: /*без отрицаний*/
                                    his.push_back(
                                        new Node
                                        (
                                            fieldNode{ typeNode::OPERATION, i },
                                            his[m],
                                            his[n]
                                        ));
                                    his.erase(his.begin() + m); /*удаление левого поддерева из вектора*/
                                    his.erase(his.begin() + n - 1); /*удаление правого поддерева из вектора*/
                                    break;
                                case 1: /*отрицание левого поддерева*/
                                    his[m] = new Node
                                    (
                                        fieldNode{ typeNode::OPERATION, operation::NOT },
                                        nullptr,
                                        his[m]
                                    );
                                    his.push_back(
                                        new Node
                                        (
                                            fieldNode{ typeNode::OPERATION, i },
                                            his[m],
                                            his[n]
                                        ));
                                    his.erase(his.begin() + m); /*удаление левого поддерева из вектора*/
                                    his.erase(his.begin() + n - 1); /*удаление правого поддерева из вектора*/
                                    break;
                                case 2: /*отрицание правого поддерева*/
                                    his[n] = new Node
                                    (
                                        fieldNode{ typeNode::OPERATION, operation::NOT },
                                        nullptr,
                                        his[n]
                                    );
                                    his.push_back(
                                        new Node
                                        (
                                            fieldNode{ typeNode::OPERATION, i },
                                            his[m],
                                            his[n]
                                        ));
                                    his.erase(his.begin() + m); /*удаление левого поддерева из вектора*/
                                    his.erase(his.begin() + n - 1); /*удаление правого поддерева из вектора*/
                                    break;
                                case 3: /*отрицание левого и правого поддеревьев*/
                                    his[m] = new Node
                                    (
                                        fieldNode{ typeNode::OPERATION, operation::NOT },
                                        nullptr,
                                        his[m]
                                    );
                                    his[n] = new Node
                                    (
                                        fieldNode{ typeNode::OPERATION, operation::NOT },
                                        nullptr,
                                        his[n]
                                    );
                                    his.push_back(
                                        new Node
                                        (
                                            fieldNode{ typeNode::OPERATION, i },
                                            his[m],
                                            his[n]
                                        ));
                                    his.erase(his.begin() + m); /*удаление левого поддерева из вектора*/
                                    his.erase(his.begin() + n - 1); /*удаление правого поддерева из вектора*/
                                    break;
                                default:
                                    break;
                                }

                                generateNode(his, head, oper, isNot, countNode);

                                /*возвращаем массив his в исходное состояние*/
                                if (//his[his.size() - 1]->getLeft() &&
                                    his[his.size() - 1]->getLeft()->getField().type == typeNode::OPERATION
                                    && his[his.size() - 1]->getLeft()->getField().oper == operation::NOT)
                                {
                                    Node* tmp = his[his.size() - 1]->getLeft()->getRight();
                                    delete his[his.size() - 1]->getLeft();
                                    his.insert(his.begin() + m, tmp);
                                }
                                else
                                {
                                    Node* tmp = his[his.size() - 1]->getLeft();
                                    his.insert(his.begin() + m, tmp);
                                }

                                if (//his[his.size() - 1]->getRight() &&
                                    his[his.size() - 1]->getRight()->getField().type == typeNode::OPERATION
                                    && his[his.size() - 1]->getRight()->getField().oper == operation::NOT)
                                {
                                    Node* tmp = his[his.size() - 1]->getRight()->getRight();
                                    delete his[his.size() - 1]->getRight();
                                    his.insert(his.begin() + n, tmp);
                                }
                                else
                                {
                                    Node* tmp = his[his.size() - 1]->getRight();
                                    his.insert(his.begin() + n, tmp);
                                }

                                delete his[his.size() - 1];
                                his.pop_back();
                            }
                        }
                        else
                        {
                            his.push_back(
                                new Node
                                (
                                    fieldNode{ typeNode::OPERATION, i },
                                    his[m],
                                    his[n]
                                ));
                            his.erase(his.begin() + m); /*удаление левого поддерева из вектора*/
                            his.erase(his.begin() + n - 1); /*удаление правого поддерева из вектора*/

                            generateNode(his, head, oper, isNot, countNode);

                            /*возвращаем массив his в исходное состояние*/
                            Node* tmp = his[his.size() - 1]->getLeft();
                            his.insert(his.begin() + m, tmp);

                            tmp = his[his.size() - 1]->getRight();
                            his.insert(his.begin() + n, tmp);

                            delete his[his.size() - 1];
                            his.pop_back();
                        }

                        if (k == 1)
                        {
                            Node* temporary = his[m];
                            his[m] = his[n];
                            his[n] = temporary;
                        }
                    }
                }
            }
        }
    }
}

bool findLogicValue(std::vector<Node*>& his, Node* head, std::vector<bool>& xyz)
{
    if (head->getLeft() != nullptr && head->getRight() != nullptr && head->getField().type == typeNode::OPERATION)
        return searchBinaryResult(findLogicValue(his, head->getLeft(), xyz), findLogicValue(his, head->getRight(), xyz), head->getField().oper);

    if (head->getLeft() == nullptr && head->getRight() == nullptr)
    {
        if (head->getField().type != typeNode::LOG_CONST)
        {
            for (size_t i = 0; i < his.size(); i++)
            {
                if (head->getField().var == his[i]->getField().var)
                    return xyz[i];
            }
        }
        else
        {
            return bool(head->getField().lConst);
        }

        return findLogicValue(his, head->getRight(), xyz);
    }

    if (head->getLeft() == nullptr && head->getRight() != nullptr)
        return !findLogicValue(his, head->getRight(), xyz);

    return false; /*если ошибка, оно не падает*/
}

void outputSdnf(std::vector<Node *> &his, std::vector<Node *> &head, QTextStream& os)
{
    std::vector<Node*> hisTMP; /*хранение переменных без повторения*/
    hisTMP.push_back(his[0]);
    for (size_t i = 1; i < his.size(); i++) /*удаление дубдикатов переменных*/
    {
        bool isRepeat = false;
        for (size_t j = 0; j < hisTMP.size(); j++)
        {
            if (his[i]->getField() == hisTMP[j]->getField())
                isRepeat = true;
        }
        if (!isRepeat)
            hisTMP.push_back(his[i]);
    }

    for (size_t it = 0; it < head.size(); it++) /*проход по формулам*/
    {
        bool isFirst = true;
        std::stringstream ss;

        for (size_t j = 0; j < static_cast<size_t>(pow(2, hisTMP.size())); j++) /*проход по рахзным кодам*/
        {
            std::vector<bool> xyz; /*значения переменных по порядку*/


            size_t code = j;

            for (size_t i = 0; i < hisTMP.size(); i++)
            {
                if (hisTMP[i]->getField().type != typeNode::LOG_CONST)
                    xyz.insert(xyz.begin(), code % 2);
                code /= 2;
            }

            /*построение сднф и вывод*/
            if (findLogicValue(hisTMP, head[it], xyz) == 1)
            {
                if (isFirst)
                {
                    ss << it + 1 << "."; /*номер функции*/
                    isFirst = false;
                    for (size_t i = 0; i < hisTMP.size(); i++)
                    {
                        if (xyz[i] == 0)
                        {
                            if (i == hisTMP.size() - 1)
                                ss << "(~" << hisTMP[i]->getField().var << ")";
                            else
                                ss << "(~" << hisTMP[i]->getField().var << ")*";
                        }
                        else
                        {
                            if (i == hisTMP.size() - 1)
                                ss << hisTMP[i]->getField().var;
                            else
                                ss << hisTMP[i]->getField().var << "*";
                        }
                    }
                }
                else
                {
                    ss << "+";
                    for (size_t i = 0; i < hisTMP.size(); i++)
                    {
                        if (xyz[i] == 0)
                        {
                            if (i == hisTMP.size() - 1)
                                ss << "(~" << hisTMP[i]->getField().var << ")";
                            else
                                ss << "(~" << hisTMP[i]->getField().var << ")*";
                        }
                        else
                        {
                            if (i == hisTMP.size() - 1)
                                ss << hisTMP[i]->getField().var;
                            else
                                ss << hisTMP[i]->getField().var << "*";
                        }
                    }
                }
            }
        }
        if (!ss.str().empty())
            os << ss.str().c_str();
        if (!ss.str().empty())
            os << endl;
    }
}

void outputSknf(std::vector<Node *> &his, std::vector<Node *> &head, QTextStream &os)
{
    std::vector<Node*> hisTMP; /*хранение переменных без повторения*/
    hisTMP.push_back(his[0]);
    for (size_t i = 1; i < his.size(); i++) /*удаление дубдикатов переменных*/
    {
        bool isRepeat = false;
        for (size_t j = 0; j < hisTMP.size(); j++)
        {
            if (his[i]->getField() == hisTMP[j]->getField())
                isRepeat = true;
        }
        if (!isRepeat)
            hisTMP.push_back(his[i]);
    }


    for (size_t it = 0; it < head.size(); it++) /*проход по формулам*/
    {
        bool isFirst = true;
        std::stringstream ss;

        for (size_t j = 0; j < static_cast<size_t>(pow(2, hisTMP.size())); j++) /*проход по рахзным кодам*/
        {
            std::vector<bool> xyz; /*значения переменных по порядку*/


            size_t code = j;

            for (size_t i = 0; i < hisTMP.size(); i++)
            {
                if (hisTMP[i]->getField().type != typeNode::LOG_CONST)
                    xyz.insert(xyz.begin(), code % 2);
                code /= 2;
            }

            /*построение скнф и вывод*/
            if (findLogicValue(hisTMP, head[it], xyz) == 0)
            {
                if (isFirst)
                {
                    ss << it + 1 << "."; /*номер функции*/
                    isFirst = false;

                    ss << "(";
                    for (size_t i = 0; i < hisTMP.size(); i++)
                    {
                        if (xyz[i] == 1)
                        {
                            if (i == hisTMP.size() - 1)
                                ss << "(~" << hisTMP[i]->getField().var << ")";
                            else
                                ss << "(~" << hisTMP[i]->getField().var << ")+";
                        }
                        else
                        {
                            if (i == hisTMP.size() - 1)
                                ss << hisTMP[i]->getField().var;
                            else
                                ss << hisTMP[i]->getField().var << "+";
                        }
                    }
                    ss << ")";
                }
                else
                {
                    ss << "*";
                    ss << "(";
                    for (size_t i = 0; i < hisTMP.size(); i++)
                    {
                        if (xyz[i] == 1)
                        {
                            if (i == hisTMP.size() - 1)
                                ss << "(~" << hisTMP[i]->getField().var << ")";
                            else
                                ss << "(~" << hisTMP[i]->getField().var << ")+";
                        }
                        else
                        {
                            if (i == hisTMP.size() - 1)
                                ss << hisTMP[i]->getField().var;
                            else
                                ss << hisTMP[i]->getField().var << "+";
                        }
                    }
                    ss << ")";
                }
            }
        }
        if (!ss.str().empty())
            os << ss.str().c_str();
        if (!ss.str().empty())
            os << endl;
    }
}

void buildTableTruth(std::vector<Node *> &his, std::vector<Node *> &head, QTextStream &os)
{
    std::vector<Node*> hisTMP; /*хранение переменных без повторения*/
    hisTMP.push_back(his[0]);
    for (size_t i = 1; i < his.size(); i++) /*удаление дубдикатов переменных*/
    {
        bool isRepeat = false;
        for (size_t j = 0; j < hisTMP.size(); j++)
        {
            if (his[i]->getField() == hisTMP[j]->getField())
                isRepeat = true;
        }
        if (!isRepeat)
            hisTMP.push_back(his[i]);
    }

    for (size_t it = 0; it < head.size(); it++)
    {
        os << it + 1 << ": " << endl;

        for (size_t i = 0; i < hisTMP.size(); i++)
        {
            if (hisTMP[i]->getField().type != typeNode::LOG_CONST)
                os << hisTMP[i]->getField().var << '\t';
            else
                os << hisTMP[i]->getField().lConst << '\t';
        }

        head[it]->qStringDisplay(0, os);
        os << endl;

        for (size_t j = 0; j < static_cast<size_t>(pow(2, hisTMP.size())); j++)
        {
            std::vector<bool> xyz;

            size_t code = j;

            for (size_t i = 0; i < hisTMP.size(); i++)
            {
                if (hisTMP[i]->getField().type != typeNode::LOG_CONST)
                    xyz.insert(xyz.begin(), code % 2);
                code /= 2;
            }

            /*выражения*/
            for (size_t i = 0; i < hisTMP.size(); i++)
            {
                if (hisTMP[i]->getField().type != typeNode::LOG_CONST)
                    os << xyz[i] << '\t';
                else
                    os << int(hisTMP[i]->getField().lConst) << '\t';
            }
            os << findLogicValue(hisTMP, head[it], xyz);

            os << endl;
        }
        os << endl;
    }
}
