#include "state.h"

State::State()
{
    this->init();
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
    QFile file(settingsFile);
    QTextStream out;

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        out << int(this->var) << endl;
        out << int(this->oper) << endl;
        out << int(this->lang);
    }
    else
    {
        qWarning("Could not open file, settings.ini");
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
    QString filename(settingsFile);

    if (QFile(filename).exists())
    {
        QFile file(filename);
        QTextStream in(&file);
        this->var = varType(in.readLine().toInt());
        this->oper = opType(in.readLine().toInt());
        this->lang = langType(in.readLine().toInt());
    }
    else
    {
        qWarning("No such file");
        this->var = varType::XYZ;
        this->oper = opType::MATH;
        this->lang = langType::RU;
    }
}
