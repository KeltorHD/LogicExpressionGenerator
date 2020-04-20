#ifndef SETTINGS_H
#define SETTINGS_H

#include "state.h"
#include "node.h"

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(State *state,
                      QStackedWidget *stWidget,
                      QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;

    State *state; /*класс настроек*/
    QStackedWidget *stWidget; /*указатель на внешний виджет*/
};

#endif // SETTINGS_H
