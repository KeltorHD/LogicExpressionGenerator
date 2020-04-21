#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "formtreegenerate.h"
#include "fromtreemanipulation.h"
#include "state.h"
#include "menu.h"
#include "settings.h"
#include "node.h"

#include <QWidget>
#include <QEvent>
#include <QTranslator>

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

protected:
    // Метод получения событий в главном окне приложения
    // В нём будет производиться проверка события смены перевода приложения
    void changeEvent(QEvent * event) override;

private:
    /*variable*/
    Ui::MainWidget *ui;
    QTranslator qtLanguageTranslator; /*поле перевода*/
    State* state; /*класс настроек*/

    FormTreeGenerate *formTreeGenerate;        /*экран генерации*/
    FromTreeManipulation *fromTreeManipulation;/*экран взаимодействия с формулами*/
    Menu *menu;                                /*экран меню*/
    Settings *settings;                        /*экран настроек*/

    std::vector<const Node*> his;
    std::vector<const Node*> head;

    /*methods*/
    void init();
};

#endif // MAINWIDGET_H
