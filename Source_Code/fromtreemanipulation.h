#ifndef FROMTREEMANIPULATION_H
#define FROMTREEMANIPULATION_H

#include "state.h"
#include "tree.h"

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class FromTreeManipulation;
}

class FromTreeManipulation : public QWidget
{
    Q_OBJECT

public:
    explicit FromTreeManipulation(
            std::vector<const Node*>& _his,
            std::vector<const Node*>& _head,
            State *state,
            QStackedWidget *stWidget,
            QWidget *parent = nullptr);
    ~FromTreeManipulation();
    void updateTree();

private:
    /*variable*/
    Ui::FromTreeManipulation *ui;
    QStackedWidget *stWidget; /*указатель на внешний виджет*/
    State *state; /*класс настроек*/

    std::vector<const Node*>& his; /*указатель на переменные*/
    std::vector<const Node*>& head; /*указатель на корни деревьев*/

    /*methods*/
    void itemChanged();
    void deleteItem();
    void deleteAllItem();
    void saveItem();
    void saveAllItem();
    void sdnfItem();
    void sdnfAllItem();
    void sknfItem();
    void sknfAllItem();
    void tableItem();
    void tableAllItem();
    void generateAnother(); /*нажатие на кнопку сгенерировать другие*/
};

#endif // FROMTREEMANIPULATION_H
