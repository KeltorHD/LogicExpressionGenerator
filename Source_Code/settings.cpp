#include "settings.h"
#include "ui_settings.h"

#include <QDebug>

Settings::Settings(State *state,
                   QStackedWidget *stWidget,
                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings), state(state), stWidget(stWidget)
{
    ui->setupUi(this);

    ui->save->setEnabled(false);
    for (int var = 0; var < COUNT_SETTINGS; ++var)
    {
        masSettings[var] = false;
    }

    this->init();

    connect(ui->backToMenu, &QPushButton::clicked, this, &Settings::backToMenu);

    /*изменение comboBox*/
    connect(ui->comboVar, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged), this, &Settings::varChanged);
    connect(ui->comboOper, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged), this, &Settings::operChanged);
    connect(ui->comboLang, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged), this, &Settings::langChanged);

    /*кнопка save*/
    connect(ui->save, &QPushButton::clicked, this, &Settings::save);
}
Settings::~Settings()
{
    delete ui;
}

void Settings::changeEvent(QEvent *event)
{
    //В случае получения события изменения языка приложения
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);    // перевод окна
    }
}

void Settings::init()
{
    QStringList listVar = {"X, Y, Z, ..", "X1, X2, X3, ..", "A, B, C, .."};
    QStringList listOper = {"~, +, *, (+)", "¬, ∧, ∨, ⊕, ⇔"};
    QStringList listLang = {"EN", "RU"};

    ui->comboVar->addItem(listVar[0]);
    ui->comboVar->addItem(listVar[1]);
    ui->comboVar->addItem(listVar[2]);
    ui->comboVar->setCurrentIndex(int(state->getVar()));

    ui->comboOper->addItem(listOper[0]);
    ui->comboOper->addItem(listOper[1]);
    ui->comboOper->setCurrentIndex(int(state->getOper()));

    ui->comboLang->addItem(listLang[0]);
    ui->comboLang->addItem(listLang[1]);
    ui->comboLang->setCurrentIndex(int(state->getLang()));
}

void Settings::restore()
{
    ui->save->setEnabled(false);
    for (int var = 0; var < COUNT_SETTINGS; ++var)
    {
        masSettings[var] = false;
    }
    ui->comboVar->setCurrentIndex(int(state->getVar()));
    ui->comboOper->setCurrentIndex(int(state->getOper()));
    ui->comboLang->setCurrentIndex(int(state->getLang()));
}

void Settings::backToMenu()
{
    restore();
    stWidget->setCurrentIndex(int(screen::MENU));
}

void Settings::checkSave()
{
    bool isSave = false;
    for (int var = 0; var < COUNT_SETTINGS; ++var)
    {
        if (masSettings[var])
            isSave = true;
    }
    ui->save->setEnabled(isSave);
}

void Settings::varChanged()
{
    if (ui->comboVar->currentIndex() != int(state->getVar()))
        masSettings[size_t(masType::VAR)] = true;
    else
        masSettings[size_t(masType::VAR)] = false;
    checkSave();
}

void Settings::operChanged()
{
    if (ui->comboOper->currentIndex() != int(state->getOper()))
        masSettings[size_t(masType::OPER)] = true;
    else
        masSettings[size_t(masType::OPER)] = false;
    checkSave();
}

void Settings::langChanged()
{
    if (ui->comboLang->currentIndex() != int(state->getLang()))
        masSettings[size_t(masType::LANG)] = true;
    else
        masSettings[size_t(masType::LANG)] = false;
    checkSave();
}

void Settings::save()
{
    if (masSettings[int(masType::VAR)])
    {
        state->setVar(varType(ui->comboVar->currentIndex()));
    }
    if (masSettings[int(masType::OPER)])
    {
        state->setOper(opType(ui->comboOper->currentIndex()));
    }
    if (masSettings[int(masType::LANG)])
    {
        state->setLang(langType(ui->comboLang->currentIndex()));
    }
    for (size_t i =0; i < COUNT_SETTINGS; i++)
    {
        masSettings[i] = false;
    }
    state->save();

    checkSave();
}
