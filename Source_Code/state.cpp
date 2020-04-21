#include "state.h"

State::State(QTranslator& qtr)
    :qtLanguageTranslator(qtr)
{
    this->init();

    switch (lang)
    {
    case langType::RU:
        qtLanguageTranslator.load(QString("TreeApp_ru"));
        break;
    case langType::EN:
        qtLanguageTranslator.load(QString("TreeApp_en"));
        break;
    case langType::DE:
        qtLanguageTranslator.load(QString("TreeApp_de"));
        break;
    }
    qApp->installTranslator(&qtLanguageTranslator);
}

State::~State()
{
    save();
}

void State::setVar(const varType &var)
{
    this->var = var;
}

void State::setOper(const opType &oper)
{
    this->oper = oper;
}

void State::setLang(const langType &lang)
{
    this->lang = lang;
    switch (lang)
    {
    case langType::RU:
        qtLanguageTranslator.load(QString("TreeApp_ru"));
        break;
    case langType::EN:
        qtLanguageTranslator.load(QString("TreeApp_en"));
        break;
    case langType::DE:
        qtLanguageTranslator.load(QString("TreeApp_de"));
        break;
    }
    qApp->installTranslator(&qtLanguageTranslator);
}

const varType &State::getVar()
{
    return this->var;
}

const opType &State::getOper()
{
    return this->oper;
}

const langType &State::getLang()
{
    return this->lang;
}

void State::save()
{
    QFile file("state.ini");
    QTextStream out;

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        out << int(this->var) << endl;
        out << int(this->oper) << endl;
        out << int(this->lang);
        file.close();
    }
    else
    {
        qWarning("Could not save file, state.ini");
    }
}

void State::setAll(const varType &var, const opType &oper, const langType &lang)
{
    this->var = var;
    this->oper = oper;
    this->lang = lang;
}

void State::init()
{
    QString filename("state.ini");

    if (QFile(filename).exists())
    {
        QFile file(settingsFile);

        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);
            this->var = varType(in.readLine().toInt());
            this->oper = opType(in.readLine().toInt());
            this->lang = langType(in.readLine().toInt());
            file.close();
        }
        else
        {
            qWarning("Could not open file, state.ini");
            this->var = varType::XYZ;
            this->oper = opType::MATH;
            this->lang = langType::RU;
        }
    }
    else
    {
        qWarning("Could not exist file, state.ini");
        this->var = varType::XYZ;
        this->oper = opType::MATH;
        this->lang = langType::RU;
    }
}
