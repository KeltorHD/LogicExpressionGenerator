#ifndef MENU_H
#define MENU_H

#include "node.h"

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QStackedWidget *stWidget, QWidget *parent = nullptr);
    ~Menu();

private:
    Ui::Menu *ui;

    QStackedWidget *stWidget; /*указатель на внешний виджет*/

    /*методы*/
    void generate();
    void settings();
};

#endif // MENU_H
