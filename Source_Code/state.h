#ifndef STATE_H
#define STATE_H

#include "node.h"

#include <QFileInfo>
#include <QFile>
#include <QString>

#define settingsFile "settings.ini"

class State /*класс с настройками приложения*/
{
public:
    State();
    ~State();

    /*get and set*/
    void setVar(const varType& var);
    void setOper(const opType& oper);
    void setLang(const langType& lang);
    const varType &getVar();
    const opType& getOper();
    const langType &getLang();

    /*методы*/
    void save();   /*сохранение текущих настроек*/
    void setAll(const varType& var,
                const opType& oper,
                const langType& lang); /*установка всех настроек*/

private:
    /*переменные*/
    varType var;   /*тип отображения переменной*/
    opType oper;   /*тип отображения операции*/
    langType lang; /*тип локализации*/

    /*методы*/
    void init();   /*инициализация из файла*/
};

#endif // STATE_H