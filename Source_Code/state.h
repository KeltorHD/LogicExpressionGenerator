#ifndef STATE_H
#define STATE_H

#include "node.h"

#include <QFileInfo>
#include <QFile>
#include <QString>
#include <QTranslator>
#include <QApplication>

#define settingsFile "state.ini"

class State /*класс с настройками приложения*/
{
public:
    State(QTranslator& qtr);
    ~State();

    /*get and set*/
    void setVar(const varType& var);
    void setOper(const opType& oper);
    void setLang(const langType& lang);
    void setTheme(const themeType& theme);
    const varType &getVar();
    const opType &getOper();
    const langType &getLang();
    const themeType &getTheme();

    /*методы*/
    void save();   /*сохранение текущих настроек*/
    void setAll(const varType& var,
                const opType& oper,
                const langType& lang); /*установка всех настроек*/

private:
    /*переменные*/
    varType var;     /*тип отображения переменной*/
    opType oper;     /*тип отображения операции*/
    langType lang;   /*тип локализации*/
    themeType theme; /*тип темы*/

    QTranslator& qtLanguageTranslator; /*поле перевода*/

    /*методы*/
    void init();   /*инициализация из файла*/
};

#endif // STATE_H
