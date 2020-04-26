#ifndef SETTINGS_H
#define SETTINGS_H

#include "state.h"
#include "node.h"

#include <QWidget>
#include <QStackedWidget>

#define COUNT_SETTINGS 4

enum class masType {LANG = 0, OPER, VAR, THEME};
/*0 - язык, 1 - операции, 2 - переменные, 3 - тема приложения*/

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

protected:
    // Метод получения событий в главном окне приложения
    // В нём будет производиться проверка события смены перевода приложения
    void changeEvent(QEvent * event) override;

private:
    Ui::Settings *ui;

    State *state; /*класс настроек*/
    QStackedWidget *stWidget; /*указатель на внешний виджет*/
    bool masSettings[COUNT_SETTINGS]; /*изменились ли поля настроек*/

    /*методы*/
    void init();
    void restore();
    void backToMenu();
    void checkSave();    /*возможность сохранить*/

    void varChanged();   /*изменение переменной*/
    void operChanged();  /*изменение операций*/
    void langChanged();  /*изменение языка*/
    void themeChanged(); /*изменение темы*/

    void save();         /*сохранение настроек*/
};

#endif // SETTINGS_H
