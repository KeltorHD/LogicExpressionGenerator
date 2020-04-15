#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "node.h"

/*
Результат бинарной операции
*/
bool searchBinaryResult(bool l1, bool l2, operation oper);

/*
Генерация всех деревьев
Генерация происходит без конечного отрицания всего выражения!
Принимает:
-ссылку на вектор указателей на узлы деревьев, в которых хранятся переменные или логические константы
-ссылку на вектор указателей на узлы деревьев, в который будут записываться вершины сгенерированных деревьев
-вектор операций, на основе которых создаются формулы
-логическая переменная, участвует ли отрицание? По умолчанию да
-количество деревьев, которые нужно сгенерировать, -1(значение по-умолчанию) означает получить все.
Если деревьев меньше, чем нужное количество, то записываются все деревья
*/
void generateNode(std::vector<Node*>& his, std::vector<Node*>& head, std::vector<operation>& oper, bool isNot = true, size_t countNode = -1);

bool findLogicValue(std::vector<Node*>& his, Node* head, std::vector<bool>& xyz);

void outputSdnf(std::vector<Node*>& his, std::vector<Node*>& head, QTextStream& os);

void outputSknf(std::vector<Node*>& his, std::vector<Node*>& head, QTextStream& os);

void buildTableTruth(std::vector<Node*>& his, std::vector<Node*>& head, QTextStream& os);
