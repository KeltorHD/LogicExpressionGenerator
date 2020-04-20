#ifndef FORMTREEGENERATE_H
#define FORMTREEGENERATE_H

#include "tree.h"

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class FormTreeGenerate;
}

class FormTreeGenerate : public QWidget
{
    Q_OBJECT

public:
    explicit FormTreeGenerate(
            std::vector<const Node*>& _his,
            std::vector<const Node*>& _head,
            QStackedWidget *stWidget,
            QWidget *parent = nullptr);
    ~FormTreeGenerate();

private:
    /*variable*/
    Ui::FormTreeGenerate *ui;
    int masX[VARIABLE_COUNT]; /*массив количества переменных*/
    bool masOp[8]; /*массив операций*/
    bool masLg[2]; /*массив логических констант*/
    QStackedWidget *stWidget; /*указатель на внешний виджет*/
    std::vector<const Node*>& his; /*указатель на переменные*/
    std::vector<const Node*>& head; /*указатель на корни деревьев*/

    /*methods*/
    void spinBoxChanged(int var); /*изменение значений переменных*/
    void checkBoxOPChanged(int state); /*изменение операций в генерации*/
    void checkBoxLgChanged(int state); /*изменение наличия логических констант*/
    void generateClick(); /*нажатие на кнопку генерация*/
    void spinBoxFormulaChanged(int var); /*изменение числа формул*/
    void checkGenerate(); /*проверка на возможность генерации*/

};

#endif // FORMTREEGENERATE_H
