#ifndef FORMTREEGENERATE_H
#define FORMTREEGENERATE_H

#include "state.h"
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
            State *state,
            QStackedWidget *stWidget,
            QWidget *parent = nullptr);
    ~FormTreeGenerate();

    /*методы*/
    void setVarText(); /*задание текста переменным*/

private:
    /*variable*/
    Ui::FormTreeGenerate *ui;

    int masX[VARIABLE_COUNT]; /*массив количества переменных*/
    bool masOp[8]; /*массив операций*/
    bool masLg[2]; /*массив логических констант*/

    QStackedWidget *stWidget; /*указатель на внешний виджет*/
    State *state; /*класс настроек*/
    std::vector<const Node*>& his; /*указатель на переменные*/
    std::vector<const Node*>& head; /*указатель на корни деревьев*/

    QStringList varList[3] =
    {
        {"X", "Y", "Z", "T", "K", "L", "M", "N", "P", "S"},
        {"X1", "X2", "X3", "X4", "X5", "X6", "X7", "X8", "X9", "X10"},
        {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"}
    };

    /*methods*/
    void init();
    void restore(); /*восстановление исходного состояния виджета*/
    void backToMenu(); /*выход в меню*/
    void spinBoxChanged(int var); /*изменение значений переменных*/
    void checkBoxOPChanged(int state); /*изменение операций в генерации*/
    void checkBoxLgChanged(int state); /*изменение наличия логических констант*/
    void generateClick(); /*нажатие на кнопку генерация*/
    void spinBoxFormulaChanged(int var); /*изменение числа формул*/
    void checkGenerate(); /*проверка на возможность генерации*/

};

#endif // FORMTREEGENERATE_H
