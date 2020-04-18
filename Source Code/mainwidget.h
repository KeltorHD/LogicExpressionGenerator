#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "formtreegenerate.h"
#include "fromtreemanipulation.h"
#include "node.h"

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void update();

private:
    /*variable*/
    Ui::MainWidget *ui;
    FormTreeGenerate *formTreeGenerate;
    FromTreeManipulation *fromTreeManipulation;
    std::vector<const Node*> his;
    std::vector<const Node*> head;

    /*methods*/
};

#endif // MAINWIDGET_H
